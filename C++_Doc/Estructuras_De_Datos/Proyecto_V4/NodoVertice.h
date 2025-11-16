
#ifndef NODO_H
#define NODO_H

#include <string>
#include "ListaAristas.h"

class NodoVertice{
public:
    std::string nombre;
    // cada Nodo vertice tiene una lista de aristas
    ListaAristas* aristas;
    // nodo vertice sera la lista principal
    NodoVertice* sig;

    NodoVertice();
    NodoVertice(std::string nombre);
    ~NodoVertice();
};

#endif NODO_H