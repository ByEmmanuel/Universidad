
import cv2 as cv
import numpy as np
import random as rd

# ──  suma gaussiano 5x5 y su suma normalizadora 
K = [
    [1,  4,  7,  4,  1],
    [4, 16, 26, 16,  4],
    [7, 26, 41, 26,  7],
    [4, 16, 26, 16,  4],
    [1,  4,  7,  4,  1]
]
S_K = 273

img = cv.imread('imagenesgris/1.png', 0)

if img is None:
    print("No tienes cargada la imagen")
else:
    # ── Redimensionar ─────────────────────────────────────────────────────────
    img = cv.resize(img, (480, 640), interpolation=cv.INTER_NEAREST)
    alto, ancho = img.shape

    # ── Agregar ruido sal y pimienta ──────────────────────────────────────────
    for _ in range(5000):
        img[rd.randint(0, alto - 1)][rd.randint(0, ancho - 1)] = rd.randint(0, 255)

    cv.imshow('Imagen con Ruido', img)

    # ── Filtro Gaussiano manual ───────────────────────────────────────────────
    resultado = img.copy()

    for f in range(2, alto - 2):
        for c in range(2, ancho - 2):

            acumulado = 0
            for kf in range(5):
                for kc in range(5):
                    acumulado += int(img[f + kf - 2, c + kc - 2]) * K[kf][kc]

            resultado[f, c] = acumulado // S_K

    cv.imshow('Imagen Filtro Gaussiano', resultado)

    cv.waitKey(0)
    cv.destroyAllWindows()
