# Esta opcion te calcula el retorno obtenido de una venta de un activo
# R_t, R_(t+1) = (P_(t+1) / P_t) -1
from time import sleep

#Logica del negocio
def calcular_roi(precio_venta  : float , precio_compra : float):
    return (precio_venta / precio_compra) - 1

def pedir_datos_usuario(cantidad_de_datos : int, tipo_de_datos, lista_prompts : list):
    array_respuestas = []
    i = 0
    for _ in range(cantidad_de_datos):
        array_respuestas.append(tipo_de_datos(input(lista_prompts[i])))
        i+=1
    return array_respuestas

def mostrar_calculo_roi():
    try:
        array_respuestas = pedir_datos_usuario(2,float,["Ingrese precio de venta:  ","Ingrese precio de compra:  "])
        print("Calculando ROI%")
        for i in range(5):
            sleep(0.5)
            print(".", end="", flush=True)
        print("\n")
        # corresponde a precio : VENTA , COMPRA
        roi = calcular_roi(array_respuestas[0],array_respuestas[1])
        print(f"{roi:.5f} %")
        print(f"{roi*100:.5f} %")
    except ValueError:
        print("Porfavor Ingrese valores validos")

def opcion_2():
    print("Opcion 2")

def opcion_3():
    print("Opcion 3")

def menu(opciones : dict):
    print("Bienvenido al sistema de finanzas inteligente con python :) \n")
    for key, value in opciones.items():
        print(f"{key}: {value[0]}")
    return int(input("Escoge una opcion :  "))


def main():
    acciones = {
        1: ("Calcular ROI (%)", mostrar_calculo_roi),
        2: ("Calcular % de inversion", opcion_2),
        3: ("Salir", lambda : exit(1))
    }
    while True:
        try:
            opc_usr = menu(acciones)
            acciones.get(opc_usr, ("Opcion invalida", lambda :print("opcion no valida")))[1]()
        except Exception as e:
            print(f"ERROR : {e}")

if __name__ == '__main__':
    main()