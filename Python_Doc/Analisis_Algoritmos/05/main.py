import cv2 as cv
import numpy as np
import os


spiderman = cv.imread("si.png", cv.IMREAD_UNCHANGED)

if spiderman is None:
    print(f"Error: no se encontró la imagen en ")
    exit(1)

if spiderman.shape[2] == 3:
    print("Ajustando canales de la imagen...")
    canal_b, canal_g, canal_r = cv.split(spiderman)
    canal_alpha = np.ones(canal_b.shape, dtype=canal_b.dtype) * 255
    spiderman = cv.merge((canal_b, canal_g, canal_r, canal_alpha))

ruta_xml = os.path.join(cv.data.haarcascades, "haarcascade_frontalface_default.xml")
detector_caras = cv.CascadeClassifier(ruta_xml)

if detector_caras.empty():
    print(f"Error: no se pudo cargar el clasificador")
    exit(1)

camara = cv.VideoCapture(0)

if not camara.isOpened():
    print('No se pudo acceder a la camara')
else:
    while True:
        ret, fotograma = camara.read()
        if not ret: break

        fotograma = cv.flip(fotograma, 1)
        fotograma_bgra = cv.cvtColor(fotograma, cv.COLOR_BGR2BGRA)
        fotograma_gris = cv.cvtColor(fotograma, cv.COLOR_BGR2GRAY)

        caras = detector_caras.detectMultiScale(fotograma_gris, 1.3, 5)

        for (x, y, ancho_cara, alto_cara) in caras:
            ancho_spider = ancho_cara
            alto_spider = int(spiderman.shape[0] * (ancho_spider / spiderman.shape[1]))
            spider_redim = cv.resize(spiderman, (ancho_spider, alto_spider))

            # y = esquina superior de la cara detectada
            origen_y = y
            origen_x = x

            for fila in range(spider_redim.shape[0]):
                for col in range(spider_redim.shape[1]):
                    if spider_redim[fila, col][3] > 0:
                        pixel_y = origen_y + fila
                        pixel_x = origen_x + col

                        if 0 <= pixel_y < fotograma_bgra.shape[0] and 0 <= pixel_x < fotograma_bgra.shape[1]:
                            fotograma_bgra[pixel_y, pixel_x] = spider_redim[fila, col]

        resultado = cv.cvtColor(fotograma_bgra, cv.COLOR_BGRA2BGR)
        cv.imshow('Filtro Spiderman', resultado)

        if cv.waitKey(1) & 0xFF == ord('q'):
            break

    camara.release()
    cv.destroyAllWindows()
