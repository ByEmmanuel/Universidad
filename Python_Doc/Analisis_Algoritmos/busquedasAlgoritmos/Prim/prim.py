# -*- coding: utf-8 -*-
import cv2
import numpy as np
import heapq
import os, sys

# ── Setup ────────────────────────────────────────────────────────────────────
BASE_DIR    = os.path.dirname("/home/byemmanuel/Escritorio/Workspace/Universidad/Python_Doc/Analisis_Algoritmos/busquedasAlgoritmos/")
nombreMapa  = "2"
map_path    = os.path.join(BASE_DIR, f"mapa{nombreMapa}.png")
vertex_path = os.path.join(BASE_DIR, f"verticeMapa{nombreMapa}.npy")

if not os.path.exists(map_path):
    print(f"[ERROR] No se encontró: {map_path}", file=sys.stderr);
    sys.exit(1)
if not os.path.exists(vertex_path):
    print(f"[ERROR] No se encontró: {vertex_path}", file=sys.stderr);
    sys.exit(1)

mapa    = cv2.imread(map_path)
vertices = np.load(vertex_path)

# ── Pipeline de imagen (igual que antes) ────────────────────────────────────
gray = cv2.cvtColor(mapa, cv2.COLOR_BGR2GRAY)
cv2.imshow('mapa original', gray)

ret, th1 = cv2.threshold(gray, 249, 255, cv2.THRESH_BINARY)
kernel   = np.ones((11, 11), np.uint8)
th1      = cv2.dilate(th1, kernel, 1)
th1      = cv2.erode(th1, kernel, 1)
th1      = cv2.GaussianBlur(th1, (5, 5), cv2.BORDER_DEFAULT)
ret, th2 = cv2.threshold(th1, 235, 255, cv2.THRESH_BINARY)
th2      = cv2.dilate(th2, kernel, 1)
th2_bgr  = cv2.cvtColor(th2, cv2.COLOR_GRAY2BGR)

for v in vertices:
    cv2.circle(th2_bgr, (v[1], v[0]), 3, (255, 0, 0), -1)
cv2.imshow('vertices', th2_bgr)

# ── camino_libre ─────────────────────────────────────────────────────────────
def camino_libre(th2_gray, v1, v2, muestras=20):
    #Separa las coordenadas del vértice 1 (v1) en f1 (fila / eje Y) y c1 (columna / eje X).
    f1, c1 = v1
    f2, c2 = v2
    h, w   = th2_gray.shape
    # Formula matematica parametrica
    for t in np.linspace(0, 1, muestras):
        #se redondea porque en una pantalla no puedes mostrar medio pixel
        f = int(round(f1 + t * (f2 - f1)))
        c = int(round(c1 + t * (c2 - c1)))

        # Evitar salir de la imagen (Clipping)
        f = np.clip(f, 0, h - 1)
        c = np.clip(c, 0, w - 1)
        #Los píxeles blancos (espacio libre) tienen un valor
        # cercano a 255. Los negros (obstáculos) tienen un valor cercano a 0.
        if th2_gray[f, c] < 200:
            return False
    return True

# ── Construcción de lista de adyacencia ─────────────────────────────────────
# adj[u] = lista de (peso, v)  con u < v ya cubierto simétricamente
n   = len(vertices)
adj = [[] for _ in range(n)]          # lista de listas, índice = vértice

for i in range(n):
    for j in range(i + 1, n):         # i < j evita duplicados
        if camino_libre(th2, vertices[i], vertices[j]):
            w = float(np.linalg.norm(vertices[i] - vertices[j]))
            adj[i].append((w, j))
            adj[j].append((w, i))     # grafo no dirigido → ambos sentidos

print(f"[ADJ] Vértices: {n}")

# ── Prim con min-heap ─────────────────────────────────────────────────────────
# Invariante: key[v] = peso mínimo de arista que conecta v al árbol actual
# Complejidad: O((V + E) log V) con heap binario
#
# heap entry: (key[v], v)
# parent[v]  = u  →  arista MST es (u, v) con peso key[v]

INF    = float('inf')
key    = [INF] * n          # peso mínimo conocido para entrar al MST
parent = [-1]  * n          # predecesor en el MST
inMST  = [False] * n        # ¿ya está en el árbol?

key[0] = 0.0
heap   = [(0.0, 0)]         # (key[v], v)

mst_edges  = []             # aristas del MST: (peso, u, v)
mst_weight = 0.0

while heap:
    k_u, u = heapq.heappop(heap)

    if inMST[u]:             # (lazy deletion)
        continue

    inMST[u]    = True
    mst_weight += k_u

    if parent[u] != -1:      # u != raíz
        mst_edges.append((k_u, parent[u], u))

    # por cada w estas recorriendo cada v en la lista adj posicion u
    for w, v in adj[u]:
        if not inMST[v] and w < key[v]:
            key[v]    = w
            parent[v] = u
            heapq.heappush(heap, (w, v))   # lazy: entradas viejas se descartan arriba

print(f"[MST-Prim] Aristas: {len(mst_edges)}  |  Peso total: {mst_weight:.2f} px")

# ── Visualización ─────────────────────────────────────────────────────────────
mst_img = th2_bgr.copy()

for peso, i, j in mst_edges:
    p1 = (int(vertices[i][1]), int(vertices[i][0]))
    p2 = (int(vertices[j][1]), int(vertices[j][0]))
    cv2.line(mst_img, p1, p2, (0, 255, 0), 1)

for v in vertices:
    cv2.circle(gray, (v[1], v[0]), 6, (0, 0, 255), -1)

cv2.imshow('MST - Prim', mst_img)
cv2.waitKey(0)
cv2.destroyAllWindows()