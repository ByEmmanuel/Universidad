#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include "Nodo.h"

class ListaEnlazada {
private:
    Nodo* head;
    Nodo* tail;
    int cantidad;

public:
    ListaEnlazada();
    ~ListaEnlazada();
    
    void insertar(std::string valor);
    void eliminar(std::string valor);
    Nodo* buscar(std::string valor);
    int buscar_indice(std::string valor);
    Nodo* obtener(int indice);
    int tamaño();
    bool esta_vacia();
    void imprimir();
    
    Nodo* obtener_cabeza();
};

#endif // LISTAENLAZADA_H