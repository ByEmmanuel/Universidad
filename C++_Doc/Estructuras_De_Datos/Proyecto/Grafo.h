//
// Created by Jesus Emmanuel Garcia on 11/8/25.
//

#ifndef GRAFO_H
#define GRAFO_H
#include "Lista.h"


template <typename K>

class Grafo{
public:
    Lista<K>* lista_adj;

    Grafo() : lista_adj(new Lista<K>()) {}

    Lista<K>* dijkstra(K origen);
    void insert(string Vertice, K arista);
    void insert(string Vertice);
    void imprimir(K origen);

};

template <typename K>
Lista<K>* Grafo<K>::dijkstra(K origen) {


    // implementación real aquí
    return nullptr;
}

template <typename V>
void insert(V value){

};

template <typename V>
void Grafo<V>::imprimir(V origen){

    Nodo<int>* tmp = origen;

}

#endif //GRAFO_H
