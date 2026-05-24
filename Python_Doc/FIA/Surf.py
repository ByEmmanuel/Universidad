import matplotlib.pyplot as plt
import numpy as np

def plot_contour(f, x, xl, xu, n):
    
    # Borrar gráfico anterior
    plt.clf()
    
    # Crear malla de puntos
    X = np.arange(xl[0], xu[0], 0.01)
    Y = np.arange(xl[1], xu[1], 0.01)
    X, Y = np.meshgrid(X, Y)

    # Dibujar función
    plt.contourf(X, Y, f(X,Y))
    plt.xlim(xl[0], xu[0])
    plt.ylim(xl[1], xu[1])
    
    # Dibujar partículas
    plt.scatter(x[0], x[1], marker="o", c='r', s=120)

    # Poner etiquetas
    plt.title("Differential Evolution ( iter: " + str(n)+ ")")
    plt.xlabel('x')
    plt.ylabel('y')

    # Mostrar y pausar
    plt.show(block=False)
    plt.pause(.05)