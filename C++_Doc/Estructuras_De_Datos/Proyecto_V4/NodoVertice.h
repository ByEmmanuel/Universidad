
#ifndef NODO_H
#define NODO_H

#include <string>
#include "ListaAristas.h"
#include "Sucursal.h"

class NodoVertice{
public:
    std::string nombre;
    // cada Nodo vertice tiene una lista de aristas
    ListaAristas* aristas;
    // nodo vertice sera la lista principal
    NodoVertice* sig;
    // cada vertice tendra una sucursal
    Sucursal* sucursal;

    NodoVertice();
    NodoVertice(std::string nombre);
    NodoVertice(std::string nombre, Sucursal* sucursal);
    ~NodoVertice();
};

#endif NODO_H