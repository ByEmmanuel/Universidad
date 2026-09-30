import math

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
        columns=["species"])
    y = df["species"]  # columna objetivo

    # 3. Dividir 80% entrenamiento / 20% prueba
    X_train, X_test, y_train, y_test = train_test_split(
        X, y,
        test_size=0.20,  # 20% para prueba
        random_state=42  # reproducibilidad
    )
    print("Train:", X_train.shape, " Test:", X_test.shape, "\n")

    return X_train,X_test,y_train,y_test

# calcular accuracy, precision, F1-score, specificity y recall del modelo.

def normalizar_elemento(q_i,minimos,maximos):
    # formula
    # v_i = ( v_i - min(d) ) / (max(d) - min(d))

    print("Debug:", minimos[0])
    result = []
    for i in range(len(minimos)):
        numerador = q_i.iloc[i] - minimos[i]
        denominador = maximos[i] - minimos[i]
        result.append(numerador/denominador)
    return result

# como cono normalizo 120 x 4
def normalizar_conjunto(set, minimos, maximos):
    X_train_norm = [normalizar_elemento(X_train.iloc[i], minimos_train, maximos_train)
                    for i in range(len(X_train))]

    # print(len(set)) # esto imprime 120
    # print("Arreglosdify \n",np.array(X_train_norm))
    return np.array(X_train_norm)



def predecir_clase(q_i, datos_entrenamiento):
    k_1 = 1
    k_2 = 3
    k_3 = 5
    # 120

    return



if __name__ == "__main__":
    print("Hola mundo")

    # X_train, X_test, y_train, y_test
    X_train, X_test, y_train, y_test = cargar_datos()
    print("Datos: Y traing :  \n", y_test)  # X_train
    print("Datos: X Test :  \n", X_test)  # X_train
    print("Datos: X traing Longitud:  \n", len(X_train))  # X_train
    print("Datos: X Test Longitud:  \n", len(X_test))  # X_train
    # sacar los valores maximos y minimos de X_train y X_test

    resultados = []

    # minimos de toda una columna
    # print(X_test.iloc[:,0])  # array([5.1, 3.5, 1.4, 0.2]))
    # X_test.iloc[:]
    print(len(X_test.iloc[:]))  # array([5.1, 3.5, 1.4, 0.2]))


    minimos_test = [min(X_test.iloc[:,i]) for i in range(X_test.shape[1])]
    maximos_test = [max(X_test.iloc[:,i]) for i in range(X_test.shape[1])]

    minimos_train = [min(X_train.iloc[:,i]) for i in range(X_train.shape[1])]
    maximos_train = [max(X_train.iloc[:,i]) for i in range(X_train.shape[1])]


    print(minimos_test, maximos_test)
    print(minimos_train, maximos_train)

    #cada elemento de las 4 columnas debe estar normalizado
    normalizacion_X_train = normalizar_conjunto(X_train, minimos_train, maximos_train)
    # ver diapositiva
    # esto se ejecutara 30 veces (20%)


    for i in range(len(X_test)):
        k_nn_respecto_q_i = []
        q_i = normalizar_elemento(X_test.iloc[i], minimos_train, maximos_train)
        # esto me devuelve los atributos normalizados con las 4 columnas
        print(f"q_{i}\n: ", q_i)
        print(f"q_{i}\n: ", np.array(q_i))
        # meter en una lista o lo que sea el conjunto de K, K = 1, K = 3, K = 5 y asignarle su clase
        # calcular distancias de q_i y meterlas en un arreglo
        # esto se va a hacer 120 veces
        distancias_respecto_qi = []

        for j in range(len(normalizacion_X_train)):
            distancia = 0

            for k in range(len(normalizacion_X_train[0])):
                # sacar distancia aqui
                distancia += pow((q_i[k] - normalizacion_X_train[j][k]),2 )

            distancias_respecto_qi.append(math.sqrt(distancia))
            distancias_respecto_qi = np.sort(distancias_respecto_qi)

            for l in range(len(distancias_respecto_qi)):
                arr = []
                arr_aux = []
                for n in range (1):
                    arr_aux.append(distancias_respecto_qi[l])

                arr.append(arr_aux)
                arr_aux.clear()

                for n in range (3):
                    arr.append(distancias_respecto_qi[l])

                arr.append(arr_aux)
                arr_aux.clear()
                for n in range (5):
                    arr.append(distancias_respecto_qi[l])

                arr.append(arr_aux)
                arr_aux.clear()
                distancias_respecto_qi.append(arr)


        # ahora lo que tengo que hacer es sacar los vecinos mas cercanos de q_i en base a la distancia obtenida
        # np sort e iterar 1, 3 y 5 veces para los knn



        resultados.append(predecir_clase(q_i, X_train))

        # de los 30 de test, queremos calcular sus knn mas cercaanos CON LOS 120
        # es decir, 1 de test con los 120 y asi sucesivamente



    for i in range(len(normalizacion_X_traing)):
        print(normalizacion_X_traing[:])
