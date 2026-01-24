import math
import random


class Usuario:
    def __init__(self, nombre:str, apellido:str, num_tel:int, correo:str):
        self.nombre = nombre
        self.apellido = apellido
        self.num_tel = num_tel
        self.correo = correo

    def crear_cuenta(self):
        num_targeta = random.random()
        


        return num_targeta

    def obtener_detalles_usr(self):
        return {
            self.nombre,
            self.apellido,
            self.num_tel,
            self.correo
        }