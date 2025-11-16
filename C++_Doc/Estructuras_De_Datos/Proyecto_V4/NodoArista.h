#ifndef NODOARISTA_H
#define NODOARISTA_H

#include <string>


// se crea una lista de NODOS ARISTA unicamente por cada vertice
class NodoArista{

public:
    std::string destino;
    NodoArista* sig;
    int peso;

    NodoArista();
    // seria redundante o malo, el solo poner el destino en un nodo, en dado caso no estaria ponderado
    NodoArista(std::string dest, int peso);
    NodoArista(std::string dest, int peso, NodoArista* sig);
    ~NodoArista();

};

#endif NODOARISTA_H