import sys as system
import os as os

def prueba_lista(objeto):
    lista = []
    capital = 5000
    meses = 150
    for entero in objeto:
        capital -= meses
        lista.append(capital)
    print(type(lista))
    return lista

if __name__ == '__main__':
    print(prueba_lista([0,1,2,3,4,5,6,7,8,9]))
    print(type(prueba_lista([0,1,2,3,4,5,6,7,8,9])))

