def ordenamiento_lineal(lista):
    indice_x = 0
    for x in lista:
        indice_y = 0
        for y in lista:
            if x < y:
                lista[indice_y] = x
                lista[indice_x] = y
            indice_y+=1
        indice_x += 1

    return lista


if __name__ == '__main__':

    lista_ = [0,45,2,2,5,45,34,23,124,32,543,53,6,1]

    print(ordenamiento_lineal(lista_))
