import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split

df = pd.read_csv("IRIS_PLANT.csv")  # ruta al archivo



def cargar_datos():
    # 1. Cargar el CSV

    print(df.head())  # primeras filas
    print(df.shape)  # (filas, columnas)
    print(df.isnull().sum())  # valores faltantes por columna

    # 2. Separar features (X) y objetivo (y)
    X = df.drop(
        columns=["sepal_length", "sepal_width", "petal_length", "petal_width"])  # todas las columnas menos la objetivo
    y = df["species"]  # columna objetivo

    # 3. Dividir 80% entrenamiento / 20% prueba
    X_train, X_test, y_train, y_test = train_test_split(
        X, y,
        test_size=0.20,  # 20% para prueba
        random_state=42  # reproducibilidad
    )
    print("Train:", X_train.shape, " Test:", X_test.shape, "\n")

    return X_train,X_test,y_train,y_test;

# calcular accuracy, precision, F1-score, specificity y recall del modelo.

def normalizar_elemento(dato, max_val, min_val):
    # formula
    # v_i = ( v_i - min(d) ) / (max(d) - min(d))
    print("Debug - Maximo: ", max_val)
    print("Debug - Minimo: ", min_val)

    print("Debug - Normalizado: ")

    return dato - min_val / (max_val - min_val)

if __name__ == "__main__":
    print("Hola mundo")

    # X_train, X_test, y_train, y_test
    X_train, X_test, y_train, y_test = cargar_datos()
    print("Datos: X traing Longitud:  \n", len(X_train))  # X_train
    print("Datos: X Test Longitud:  \n", len(X_test))  # X_train
    # sacar los valores maximos y minimos de X_train y X_test


    # ver diapositiva
    for i in range(len(X_test)):
        q_i = normalizar_elemento(X_test.iloc[i], X_test.max(), X_test.min())


        # meter en una lista o lo que sea el conjunto de K, K = 1, K = 3, K = 5 y asignarle su clase
        predecir_clase(q_i, X_train, k)

    # array de 2 valores
    normalizacion_X_traing = normalizar_elemento(X_train)


    for i in range(len(normalizacion_X_traing)):
        print(normalizacion_X_traing[:])
