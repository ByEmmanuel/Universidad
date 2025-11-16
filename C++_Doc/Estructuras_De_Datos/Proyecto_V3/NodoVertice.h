//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#ifndef NODOVERTICE_H
#define NODOVERTICE_H

#include <string>
#include "ListaAristas.h"

class NodoVertice {
public:
    std::string nombre;
    ListaAristas* aristas;
    NodoVertice* siguiente;

    NodoVertice(std::string nom);
    ~NodoVertice();
};

#endif // NODOVERTICE_H