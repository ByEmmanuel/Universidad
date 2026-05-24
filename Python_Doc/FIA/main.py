import matplotlib.pyplot as plt
import numpy as np
import sys
import termios
import tty
#from matplotlib.pyplot import contour
#from mpl_toolkits.mplot3d import Axes3D

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


def getch(_=0):
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    

f = lambda x, y: (x-2)**2 + (y-2)**2
#f = lambda x, y: -20 * np.exp(-0.2 * np.sqrt(0.5*(x**2 + y**2))) - np.exp(0.5*(np.cos(2*np.pi*x)+np.cos(2*np.pi*y))) + 20 + np.exp(1)
#f = lambda x, y: -((1+np.cos(12*np.sqrt(x**2+y**2))) / (0.5*(x**2+y**2)+2))
#f = lambda x, y: 10*2 + x**2 + y**2 - 10*np.cos(2*np.pi*x) - 10*np.cos(2*np.pi*y)
#f = lambda x, y: ((x**2/4000)+(y**2/4000))-(np.cos(x)*np.cos(y/np.sqrt(2)))+1


# Espacio de busqueda 

x1 = np.array([-5,-5])
xu = np.array([5,5])

# parametros del algoritmo

G = 100 # numero de generaciones 
N = 50  # numero de particulas
D = 2   # Dimension del problema

# costo computaciones = N*G


F = 0.6 # Factor escala
CR = 0.9 # tasa de apareamiento


# Inicializar las particulas
# Contenedores
x = np.zeros((D,N))

#Evaluacion en funcion objetivo (MAXIMIZAR)
fitness = np.zeros(N)

for i in range (N):
    x[:, i]= x1 + (xu - x1) * np.random.rand(D)
    fitness[i] = f(x[0,i], x[1,i])


# Evolucion diferencial
for n in range(G):
    for i in range(N):
        # Mutacion
        # Escoger 3 particulas diferentes de la inicial (X_i)
        r1 = i
        while r1 == 1:
            r1 = np.random.randint(N)

        r2 = r1 
        while r2 == r1 or r2 == 1:
            r2 = np.random.randint(N)

        r3 = r2
        while r3 == r2 or r3 == r2 or r3 == 1:
            r3 = np.random.randint(N)

        v = x[:,r1] + F * (x[:,r2]) - (x[:,r3])

        #Recombinacion
        u = np.zeros(D)
        for j in range(D):
            #Recorrer cada dimension
            # Agarrar informacion del padre o del hijo
            r = np.random.rand()
            if i <= CR:
                u[j] = v[j]
            else:
                u[j] = x[j,i]

        
        # Seleccion -> donde el papa muere
        fitness_u = f(u[0], u[1])
        if fitness_u < fitness[i]:
            x[:,i] = u
            fitness[i] = fitness_u
        
ig = np.argmin(fitness)
print("Mejor particula: ", ig)

plot_contour(f, x, x1, xu, ig)
print("Presiona cualquier tecla para cerrar...")
getch(0)