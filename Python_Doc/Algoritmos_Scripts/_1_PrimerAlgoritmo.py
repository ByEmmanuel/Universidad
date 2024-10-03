import random as r;

def random():
    return r.randint(1, 2);

opcionRandom = random();
opcionUsuario = int(input("Seleccione un numero del 1-10"))

if opcionUsuario == opcionRandom:
    print("Opcion Correcta")
else:
    print("Opcion Incorrecta")
    print(opcionRandom)