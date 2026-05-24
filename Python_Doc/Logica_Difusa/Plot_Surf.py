import matplotlib.pyplot as plt
import numpy as np


def plot_surf(f, x, xl, xu, ig):
    # Crear malla de puntos
    X = np.arange(xl[0], xu[0], 0.25)
    Y = np.arange(xl[1], xu[1], 0.25)
    X, Y = np.meshgrid(X, Y)
    Z = f(X, Y)

    # Dibujar función en 3D
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(X, Y, Z, cmap='coolwarm', alpha=0.8, linewidth=0)
    ax.set_title('Differential evolution')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')

    # Dibujar mejor partícula
    ax.scatter(x[0][ig], x[1][ig], f(x[0][ig], x[1][ig]), c='r', s=120)

    # Mostrar
    plt.show()