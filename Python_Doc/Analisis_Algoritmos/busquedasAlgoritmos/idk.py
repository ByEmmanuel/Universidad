# -*- coding: utf-8 -*-
import cv2
import numpy as np
import os, sys

os.environ.setdefault('QT_QPA_PLATFORM', 'xcb')

BASE_DIR   = os.path.dirname(os.path.abspath(__file__))
nombreMapa = "2"
map_path   = os.path.join(BASE_DIR, f"mapa{nombreMapa}.png")

mapa = cv2.imread(map_path)
gray = cv2.cvtColor(mapa, cv2.COLOR_BGR2GRAY)

# ── Opción 1: CLAHE ──────────────────────────────────────────────────────────
clahe    = cv2.createCLAHE(clipLimit=3.0, tileGridSize=(8, 8))
gray_cl  = clahe.apply(gray)

# ── Opción 2: Normalización lineal ───────────────────────────────────────────
gray_nm  = cv2.normalize(gray, None, 0, 255, cv2.NORM_MINMAX)

# ── Opción 3: Alpha/Beta manual ──────────────────────────────────────────────
gray_ab  = cv2.convertScaleAbs(gray, alpha=1.0, beta=-40)

# ── Umbralización sobre cada una ─────────────────────────────────────────────
def pipeline(g, nombre):
    kernel    = np.ones((11, 11), np.uint8)
    _, th     = cv2.threshold(g, 200, 255, cv2.THRESH_BINARY_INV)
    th        = cv2.morphologyEx(th, cv2.MORPH_CLOSE, kernel)
    th        = cv2.dilate(th, np.ones((7, 7), np.uint8), iterations=1)
    zona_libre = cv2.bitwise_not(th)
    cv2.imshow(f'zona libre [{nombre}]', zona_libre)
    return zona_libre

cv2.imshow('original', gray)
th_clahe = pipeline(gray_cl, 'CLAHE')
th_norm  = pipeline(gray_nm, 'Normalize')
th_ab    = pipeline(gray_ab, 'Alpha-Beta')

print("Presiona cualquier tecla para cerrar.")
cv2.waitKey(0)
cv2.destroyAllWindows()