import time
from typing import Union
from fastapi import FastAPI
import logging

from starlette.requests import Request

app = FastAPI()

@app.get("/")
def read_root():
    return {"Hola", "Mundo"}

@app.get("/items/{item_id}")
def read_item(item_id: int, q: Union[str, None] = None):
    return {"item_id": item_id, "q": q}

@app.get("/home")
def main_api():
    return {"Hola": "Jotos"}

@app.post("/main/{id}")
def main_app(id : int):
    return {"id_user": id}


@app.middleware("http")
async def medir_tiempo_respuesta(request: Request, call_next):
    inicio = time.time()
    response = await call_next(request)
    fin = time.time()

    duracion = fin - inicio
    response.headers["X-Response-Time"] = f"{duracion:.6f}"
    return response