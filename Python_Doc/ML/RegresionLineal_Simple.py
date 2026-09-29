import numpy as np
import matplotlib.pyplot as pl

# valores de la tabla
# x
x = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15])
y = np.array([12, 14, 17, 19, 22,25,27,30,32, 35, 42, 44, 46, 48, 51, 55])

media_x = np.mean(x)
media_y = np.mean(y)

print("Media de x:", media_x)
print("Media de y:", media_y)

# Calcular la pendiente (m) y el intercepto (b) de la recta de regresión
# b = media_y - m * media_x

numerator = np.sum((x - media_x) * (y - media_y))
denominator = np.sum((x - media_x) ** 2)
m = numerator / denominator
b = media_y - m * media_x

print("Pendiente (m):", m)
print("Intercepto (b):", b)

print("Valores de la recta de regresión:")
linea_recta = []
for i in range(len(x)):
    linea_recta.append(m * x[i] + b)
    #print(f"x: {x[i]}, y: {y[i]}, y_pred: {linea_recta[i]}")

pl.plot(linea_recta)
pl.xlabel("Años xp")
pl.ylabel("Salario ")
pl.title("Calculo de prediccion de salario")
pl.grid()
pl.show()
