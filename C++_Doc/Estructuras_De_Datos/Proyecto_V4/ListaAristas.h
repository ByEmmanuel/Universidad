#ifndef LISTAARISTAS_H
#define LISTAARISTAS_H

#include "NodoArista.h"

class ListaAristas{
private:
    NodoArista* head;
    NodoArista* tail;
    int cantidad;
    // DEFINICION DE LOS METODOS DE LAS LISTAS DE LISTA (GRAFO)

public:
    ListaAristas();
    ~ListaAristas();
    
    void insertar(std::string destino, int peso);
    void eliminar(std::string destino);
    NodoArista* buscar_por_destino(std::string destino);
    NodoArista* get_by_index(int pos);
    int size();
    bool is_empty();
    void imprimir();
    NodoArista* get_head();

};

#endif
