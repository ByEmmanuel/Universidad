import pandas as pd
import numpy as np
from matplotlib import pyplot as pl
from scipy.special import expit  # para usar sigmoid estable
import time
import psutil
import os

# Leer el archivo
df = pd.read_excel("PercMultAplicado.xlsx")

# Mapear 'Mora' a binario
df["Mora"] = df["Mora"].map({"NO": 0, "SI": 1})

# Eliminar columna no numérica
df = df.drop(columns=["Entidad"])

# Limpiar símbolos ($, %, puntos de millares, comas decimales)
for col in df.columns:
    df[col] = df[col].astype(str)
    df[col] = df[col].str.replace("[$,%]", "", regex=True)
    df[col] = df[col].str.replace(".", "", regex=False)  # quita punto como separador de miles
    df[col] = df[col].str.replace(",", ".", regex=False)  # cambia coma decimal a punto
    df[col] = pd.to_numeric(df[col], errors="coerce")

# Eliminar filas con datos faltantes
df = df.dropna()

# Separar entradas y salidas
N = 6  # columnas de entrada
M = 1  # salida: Mora
x = df.iloc[:, :N].to_numpy()
d = df.iloc[:, N:].to_numpy()

# Normalizar x entre 0 y 1 (min-max)
x_min = x.min(axis=0)
x_max = x.max(axis=0)
x_norm = (x - x_min) / (x_max - x_min)

# Mezclar y combinar entradas y salidas
df_total = pd.concat([pd.DataFrame(x_norm), pd.DataFrame(d)], axis=1)
df_total = df_total.sample(frac=1, random_state=42).reset_index(drop=True)

# Dividir 70% entrenamiento, 30% prueba
train_size = int(0.7 * len(df_total))
df_train = df_total.iloc[:train_size]
df_test = df_total.iloc[train_size:]

# Extraer x y d para entrenamiento y prueba
x_train = df_train.iloc[:, :N].to_numpy()
d_train = df_train.iloc[:, N:].to_numpy()
x_test = df_test.iloc[:, :N].to_numpy()
d_test = df_test.iloc[:, N:].to_numpy()

# Función sigmoide estable
def sigmoid(x, a=1):
    return expit(a * x)

# Configuración de red
L = 9      # Neuronas ocultas
alfa = 0.2    # Tasa de aprendizaje
E = 5       # Error inicial

# Inicializar pesos aleatorios
wh = np.random.uniform(-1, 1, (L, N))
wo = np.random.uniform(-1, 1, (M, L))

Errores = []
Q = x_train.shape[0]

# Iniciar temporizador y medición de recursos
start_time = time.time()
process = psutil.Process(os.getpid())
cpu_start = process.cpu_times()
mem_start = process.memory_info().rss  # en bytes

# Entrenamiento
while E > 1e-4:
    for i in range(Q):
        xi = x_train[i].reshape(N, 1)
        di = d_train[i].reshape(M, 1)

        # Propagación hacia adelante
        neth = wh @ xi
        yh = sigmoid(neth)
        neto = wo @ yh
        y = sigmoid(neto)

        # Retropropagación
        deltao = (di - y) * y * (1 - y)
        deltah = yh * (1 - yh) * (wo.T @ deltao)

        # Actualización de pesos
        wo += alfa * deltao @ yh.T
        wh += alfa * deltah @ xi.T

    E = np.linalg.norm(deltao)
    Errores.append(E)

pl.plot(Errores)
pl.xlabel("Épocas")
pl.ylabel("Error")
pl.title("Error de entrenamiento")
pl.grid()
pl.show()

print("\n--- Evaluación con conjunto de prueba ---")
for i in range(len(x_test)):
    xi = x_test[i].reshape(N, 1)
    di = d_test[i].reshape(M, 1)
    yh = sigmoid(wh @ xi)
    y = sigmoid(wo @ yh)
    clasificacion = "SI" if y.ravel()[0] >= 0.5 else "NO"
    print(f"Esperado: {'SI' if di.ravel()[0]==1 else 'NO'}  |  Predicho: {clasificacion} ({round(y.ravel()[0], 3)})")

# Medir tiempo y recursos al final
end_time = time.time()
cpu_end = process.cpu_times()
mem_end = process.memory_info().rss

# Calcular diferencias
total_time = end_time - start_time
cpu_user_time = cpu_end.user - cpu_start.user
cpu_system_time = cpu_end.system - cpu_start.system
mem_used_mb = (mem_end - mem_start) / (1024**2)  # convertir a MB

# Mostrar resultados
print("\n--- Coste computacional ---")
print(f"Tiempo total de ejecución: {total_time:.2f} segundos")
print(f"Tiempo CPU en modo usuario: {cpu_user_time:.2f} segundos")
print(f"Tiempo CPU en modo sistema: {cpu_system_time:.2f} segundos")
print(f"Memoria RAM utilizada: {mem_used_mb:.2f} MB")

class hola:
    lista : list