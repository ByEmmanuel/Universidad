//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#ifndef LISTAARISTAS_H
#define LISTAARISTAS_H

#include <string>

#include "NodoArista.h"

class ListaAristas {
private:
    NodoArista* head;
    NodoArista* tail;
    int cantidad;

public:
    ListaAristas();
    ~ListaAristas();

    void insertar(std::string destino, int peso);
    void eliminar(std::string destino);
    NodoArista* buscar(std::string destino);
    NodoArista* obtener(int indice);
    int tamaño();
    bool esta_vacia();
    void imprimir();

    NodoArista* obtener_cabeza();
};

#endif // LISTAARISTAS_H