import pandas as pd
from sklearn.model_selection import train_test_split

class K_NN:

    def cargar_datos():
        # 1. Cargar el CSV
        df = pd.read_csv("IRIS_PLANT.csv")          # ruta al archivo
        print(df.head())                       # primeras filas
        print(df.shape)                        # (filas, columnas)
        print(df.isnull().sum())               # valores faltantes por columna

        # 2. Separar features (X) y objetivo (y)
        X = df.drop(columns=["sepal_length", "sepal_width","petal_length","petal_width"])  # todas las columnas menos la objetivo
        y = df["species"]                 # columna objetivo

        # 3. Dividir 80% entrenamiento / 20% prueba
        X_train, X_test, y_train, y_test = train_test_split(
            X, y,
            test_size=0.20,      # 20% para prueba
            random_state=42      # reproducibilidad
        )
        print("Train:", X_train.shape, " Test:", X_test.shape)

        return {X_train, X_test, y_train, y_test}

# calcular accuracy, precision, F1-score, specificity y recall del modelo.

def normalizar_dataset(datos_entrenamiento):
    # formula
    # dataset = d
    # v_i = ( v_i - min(d) ) / (max(d) - min(d))
    datos_normalizados = []
    valor_maximo = max(datos_entrenamiento)
    valor_minimo = min(datos_entrenamiento)
    for i in range(len(datos_entrenamiento)):
        v_i = datos_entrenamiento[i] - valor_minimo
        v_i /= (valor_maximo-valor_minimo)
        datos_normalizados.append(v_i)

    for i in range(len(datos_normalizados)):
        print(datos_normalizados[i])


if __name__ == "main":

    cargar_datos()
    normalizar_dataset()