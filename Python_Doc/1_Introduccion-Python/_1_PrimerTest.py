# Descripción: Primer test de Python
# Fecha: 2/10/2024
# Autor: @ByEmmanuel
# Breve explicacion de la estructura de un programa en Python:

# 1. Importar modulos
# 2. Definir funciones
# 3. Definir variables
# 4. Ejecutar funciones
# 5. Ejecutar codigo

# Importar modulos
import random as r;

# Definir funciones
def random():
    return r.randint(1, 2);

# Definir variables
opcionRandom = random();
opcionUsuario = int(input("Seleccione un numero del 1-2\n"))

# Ejecutar funciones
if opcionUsuario == opcionRandom:
    print("Opcion Correcta")
else:
    print("Opcion Incorrecta")
    print(opcionRandom)

# Ejecutar codigo

def suma(a, b):
    return a + b

def resta(a, b):
    return a - b

def multiplicacion(a, b):
    return a * b

def division(a, b):
    return a / b

def potencia(a, b):
    return a ** b

def raizCuadrada(a:int):
    if a < 0:
        return "No se puede calcular la raiz cuadrada de un numero negativo"
    elif a == 0:
        return 0
    elif a == str:
        return "No se puede calcular la raiz cuadrada de un string"
    return a ** 0.5

print("Raiz cuadrada " + str(int(raizCuadrada(9))))



# Nota: En Python no es necesario declarar el tipo de dato de una variable


