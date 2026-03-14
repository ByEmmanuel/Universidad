import cv2 as cv
import numpy as np

def create_white_mask(frame, threshold=200, blur_size=21):
    """
    [0, 255]: qué tan "blanco" debe ser el píxel
    """
    # min canal a canal: m(x,y) = min(B(x,y), G(x,y), R(x,y))
    min_channel = np.min(frame, axis=2)

    _, mask = cv.threshold(min_channel, threshold, 255, cv.THRESH_BINARY)

    kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, (7, 7))
    mask = cv.morphologyEx(mask, cv.MORPH_OPEN,  kernel)  # elimina ruido pequeño
    mask = cv.morphologyEx(mask, cv.MORPH_CLOSE, kernel)  # rellena huecos

    mask_soft = cv.GaussianBlur(mask, (blur_size, blur_size), blur_size // 3)

    return mask_soft

def composite(frame, background, mask_white_soft):
    """
    Composición alfa:
    R(x,y,c) = F(x,y,c)·(1 - α) + B(x,y,c)·α
    donde α = mask_white_soft / 255 ∈ [0,1]
    """
    bg = cv.resize(background, (frame.shape[1], frame.shape[0]))

    alpha = mask_white_soft.astype(np.float32) / 255.0  # α ∈ [0,1]^{H×W}

    frame_f = frame.astype(np.float32)
    bg_f    = bg.astype(np.float32)

    result = np.zeros_like(frame_f)
    for c in range(3):
        result[:,:,c] = frame_f[:,:,c] * (1.0 - alpha) + bg_f[:,:,c] * alpha

    return result.astype(np.uint8)

def main():
    background = cv.imread('lasvegas.png')
    if background is None:
        print("'playa.jpg' no encontrada. Usando fondo de color.")
        background = np.full((480, 640, 3), (180, 100, 30), dtype=np.uint8)

    cap = cv.VideoCapture(0)
    if not cap.isOpened():
        print("[ERROR] No se pudo abrir la cámara.")
        return

    # Umbral ajustable con trackbar: θ ∈ [0, 255]
    cv.namedWindow('Resultado')
    cv.createTrackbar('Umbral blanco', 'Resultado', 200, 255, lambda x: None)
    cv.createTrackbar('Suavidad borde', 'Resultado',  21, 61, lambda x: None)

    print("Teclas: 'q' salir | 's' guardar")

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # Leer parámetros en tiempo real
        threshold  = cv.getTrackbarPos('Umbral blanco',  'Resultado')
        blur_raw   = cv.getTrackbarPos('Suavidad borde', 'Resultado')
        blur_size  = blur_raw if blur_raw % 2 == 1 else blur_raw + 1  # debe ser impar
        blur_size  = max(blur_size, 1)

        mask_soft = create_white_mask(frame, threshold, blur_size)
        result    = composite(frame, background, mask_soft)

        # Visualización de la máscara como imagen de 3 canales
        mask_vis = cv.cvtColor(mask_soft, cv.COLOR_GRAY2BGR)

        cv.imshow('Original',     frame)
        cv.imshow('Mascara',      mask_vis)
        cv.imshow('Resultado',    result)

    cap.release()
    cv.destroyAllWindows()

if __name__ == '__main__':
    main()