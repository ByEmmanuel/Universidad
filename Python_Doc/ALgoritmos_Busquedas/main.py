# -*- coding: utf-8 -*-
import cv2
import numpy as np
import os
import sys

# ── Setup ────────────────────────────────────────────────────────────────────
BASE_DIR    = os.path.dirname(os.path.abspath(__file__))
nombreMapa  = "2"
map_path    = os.path.join(BASE_DIR, f"mapa{nombreMapa}.jpg")
vertex_path = os.path.join(BASE_DIR, f"verticeMapa{nombreMapa}.npy")

if not os.path.exists(map_path):
    print(f"[ERROR] No se encontró: {map_path}", file=sys.stderr); sys.exit(1)
if not os.path.exists(vertex_path):
    print(f"[ERROR] No se encontró: {vertex_path}", file=sys.stderr); sys.exit(1)

mapa     = cv2.imread(map_path)
vertices = np.load(vertex_path)   # shape (n, 2) → cada fila es (row, col)

# ── Pipeline de imagen ───────────────────────────────────────────────────────
gray       = cv2.cvtColor(mapa, cv2.COLOR_BGR2GRAY)
cv2.imshow('mapa original', gray)

ret, th1   = cv2.threshold(gray, 254, 255, cv2.THRESH_BINARY)
kernel     = np.ones((11, 11), np.uint8)
th1        = cv2.dilate(th1, kernel, 1)
th1        = cv2.erode(th1, kernel, 1)
th1        = cv2.GaussianBlur(th1, (5, 5), cv2.BORDER_DEFAULT)
ret, th2   = cv2.threshold(th1, 235, 255, cv2.THRESH_BINARY)
th2        = cv2.dilate(th2, kernel, 1)
th2_bgr    = cv2.cvtColor(th2, cv2.COLOR_GRAY2BGR)

# Pintar vértices en azul
for v in vertices:
    cv2.circle(th2_bgr, (v[1], v[0]), 3, (255, 0, 0), -1)
cv2.imshow('vertices', th2_bgr)

# ── Union-Find ───────────────────────────────────────────────────────────────
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank   = [0] * n

    def find(self, x):
        # Compresión de camino
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px == py:
            return False          # mismo componente → ciclo
        # Unión por rango
        if self.rank[px] < self.rank[py]:
            px, py = py, px
        self.parent[py] = px
        if self.rank[px] == self.rank[py]:
            self.rank[px] += 1
        return True

# ── Verificador de camino libre en th2 (Bresenham) ──────────────────────────
def camino_libre(th2_gray, v1, v2, muestras=20):
    """
    Muestrea `muestras` puntos en la línea recta v1→v2.
    Retorna True si todos los píxeles son blancos (255) en th2.
    th2_gray debe ser la imagen binaria en escala de grises (1 canal).
    """
    r1, c1 = v1
    r2, c2 = v2
    h, w   = th2_gray.shape
    for t in np.linspace(0, 1, muestras):
        r = int(round(r1 + t * (r2 - r1)))
        c = int(round(c1 + t * (c2 - c1)))
        r = np.clip(r, 0, h - 1)
        c = np.clip(c, 0, w - 1)
        if th2_gray[r, c] < 200:   # píxel oscuro → obstáculo
            return False
    return True

# ── Construcción de aristas ───────────────────────────────────────────────────
# th2 sigue siendo binario 1-canal; usarlo para la verificación
n      = len(vertices)
aristas = []   # lista de (peso, i, j)

for i in range(n):
    for j in range(i + 1, n):
        if camino_libre(th2, vertices[i], vertices[j]):
            w = np.linalg.norm(vertices[i] - vertices[j])
            aristas.append((w, i, j))

# Ordenar por peso ascendente → O(|E| log |E|)
aristas.sort(key=lambda e: e[0])

# ── Kruskal ──────────────────────────────────────────────────────────────────
uf  = UnionFind(n)
mst = []   # aristas del MST: (peso, i, j)

for peso, i, j in aristas:
    if uf.union(i, j):
        mst.append((peso, i, j))
    if len(mst) == n - 1:
        break           # MST completo

peso_total = sum(p for p, _, _ in mst)
print(f"[MST] Aristas: {len(mst)}  |  Peso total: {peso_total:.2f} px")

# ── Visualización del MST ────────────────────────────────────────────────────
mst_img = th2_bgr.copy()

for peso, i, j in mst:
    p1 = (int(vertices[i][1]), int(vertices[i][0]))   # (col, row) para OpenCV
    p2 = (int(vertices[j][1]), int(vertices[j][0]))
    cv2.line(mst_img, p1, p2, (0, 255, 0), 1)         # arista MST en verde

# Re-pintar vértices encima para que sean visibles
for v in vertices:
    cv2.circle(mst_img, (v[1], v[0]), 4, (0, 0, 255), -1)   # rojo

cv2.imshow('MST - Kruskal', mst_img)
cv2.waitKey(0)
cv2.destroyAllWindows()