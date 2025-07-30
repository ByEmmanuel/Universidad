from fastapi import FastAPI

app = FastAPI()

@app.post("/Snake_Game/{X_coord}&{Y_coord}")
def posiciones_snake(X_coord : int, Y_coord : int):
    print(f"Cordenada X: {X_coord}, Coordenada Y: {Y_coord}")
    return f"Cordenada X: {X_coord}, Coordenada Y: {Y_coord}"

