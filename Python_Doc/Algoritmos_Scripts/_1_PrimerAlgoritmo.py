import random as r

def random():
    return r.randint(1, 10)


def main ():
    opcionrandom = random()
    try:
        opcionusuario = int(input("Seleccione un numero del 1-10\n"))
    except ValueError:
        print("Error")
        return -2

    print(opcionusuario)
    if not 1 <= opcionusuario <= 10:
        print("El numero debe estar entre 1 y 10")
        return -1

    if opcionusuario == opcionrandom:
        print("Opcion Correcta")
    else:
        print("Opcion Incorrecta")
        #print(opcionrandom)
    return opcionrandom

if __name__ == "__main__":
    print(__name__)

    while True :
         resultado = main()
         print("El valor que retorna es: " + str(resultado) )
         if resultado == -1 or resultado == -2:
             print("Juego terminado")
             break

