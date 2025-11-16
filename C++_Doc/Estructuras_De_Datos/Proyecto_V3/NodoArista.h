//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//
#ifndef NODOARISTA_H
#define NODOARISTA_H

#include <string>

class NodoArista {
public:
    std::string destino;
    int peso;
    NodoArista* siguiente;

    NodoArista(std::string dest, int p);
    ~NodoArista();
};

#endif // NODOARISTA_H