import time as tm
import requests

def enviar_solicitud(ejecucion : int):
    for _ in range(ejecucion):
        response = requests.post(url=f"http://127.0.0.1:8000/main/{_}")
        tiempo_respuesta = response.headers.get("X-Response-Time")
        print(f"respuesta : {response.json()}, tiempo_respuesta : {tiempo_respuesta}")

    return

if __name__ == '__main__':
    tiempo_inicio = tm.time()
    enviar_solicitud(3000)
    tiempo_final = tm.time()
    #esto me da el tiempo que tarda PYTHON no el tiempo de respuesta del servidor (input & output)
    print(f"Tiempo total: {tiempo_final-tiempo_inicio:.6f}" , )