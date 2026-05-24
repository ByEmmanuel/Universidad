import matplotlib.pyplot as plt
import numpy as np

from Logica_Difusa.Plot_Contour import plot_contour
from Logica_Difusa.Plot_Surf import plot_surf

# funciones objetivo
#f = lambda x, y: (x - 2) ** 2 + (y - 2) ** 2
#f = lambda x, y: -20 * np.exp(-0.2 * np.sqrt(0.5*(x**2 + y**2))) - np.exp(0.5*(np.cos(2*np.pi*x)+np.cos(2*np.pi*y))) + 20 + np.exp(1)
#f = lambda x, y: -((1+np.cos(12*np.sqrt(x**2+y**2))) / (0.5*(x**2+y**2)+2))
#f = lambda x, y: 10*2 + x**2 + y**2 - 10*np.cos(2*np.pi*x) - 10*np.cos(2*np.pi*y)
f = lambda x, y: ((x**2/4000)+(y**2/4000))-(np.cos(x)*np.cos(y/np.sqrt(2)))+1

# Espacio de busqueda
xl = np.array([-5, -5])
xu = np.array([5, 5])

# Parametros del algoritmo
G = 100  # Numero de generaciones
N = 50  # Numero de particulas
D = 2  # Dimension de las particulas
CR = 0.9  # Taza se apareamiento
F = 0.6  # Factor de escala

# Inicializar particulas
X = np.zeros((D, N))
fitnes = np.zeros(N)
for i in range(N):
    X[:, i] = xl + (xu - xl) * np.random.rand(D)
    fitnes[i] = f(X[0, i], X[1, i])

# evolucion diferencial
for n in range(G):
    for i in range(N):
        # Mutación
        r1 = np.random.randint(N)
        while r1 == i:
            r1 = np.random.randint(N)

        r2 = np.random.randint(N)
        while r2 == r1 or r2 == i:
            r2 = np.random.randint(N)

        r3 = np.random.randint(N)
        while r3 == r2 or r3 == r1 or r3 == i:
            r3 = np.random.randint(N)

        v = X[:, r1] + F * (X[:, r2] - X[:, r3])

        # Recombinacion
        u = np.zeros(D)
        for j in range(D):
            r = np.random.rand()
            if r < CR:
                u[j] = v[j]
            else:
                u[j] = X[j, i]

        fitnes_u = f(u[0], u[1])
        if fitnes_u < fitnes[i]:
            X[:, i] = u
            fitnes[i] = fitnes_u

# Mostrar resultado final
ig = np.argmin(fitnes)
print('Mejor particula (índice):', ig)
print('Coordenadas:', X[:, ig])
print('Fitness:', fitnes[ig])

# Graficar estado final
plot_contour(f, X, xl, xu, ig)
plot_surf(f, X, xl, xu, ig)