def idk():
    print(type(int(input("Escribe un numero:  "))))
    print(type(str(input("Escribe un String:  "))))


class Banco:
    def __init__(self, saldo, num_cliente, cuenta_cliente, contacto):
        self.__saldo = saldo
        self.__num_cliente =  num_cliente
        self.__cuenta_cliente = cuenta_cliente
        self.__contacto = contacto

    def saludar_cliente(self, nombre_cliente):
        return f"Bienvenido!:  {nombre_cliente}"

    def imprimir_atributos(self,parametro:int, nombrecliente:str):
        mensaje = self.saludar_cliente(nombrecliente)
        saldo = self.__saldo
        num_cliente = self.__num_cliente
        cuenta_cliente = self.__cuenta_cliente
        contacto_cliente = self.__contacto
        # print(type(parametro))

        if not isinstance(parametro, int):
            return -1
        return (
            f"{mensaje}\n"
            f"Saldo Cliente    : {saldo}          \n"
            f"Numero Cliente   : {num_cliente}    \n"
            f"Cuenta Cliente   : {cuenta_cliente} \n"
            f"Contacto Cliente : {contacto_cliente} \n"
        )



if __name__ == '__main__':
    instancia_1 = Banco(200,201, 20903, "Luis")
    #instancia_1.imprimir_atributos()
    print(instancia_1.imprimir_atributos(290,"Emmanuel"))