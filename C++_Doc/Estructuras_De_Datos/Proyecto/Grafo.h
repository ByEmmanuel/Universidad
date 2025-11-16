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

    void insert_vertice(string vertice);
    void insert_arista(string origen, string destino, K peso);
    void imprimir(K origen);

    Lista<K>* dijkstra(K origen);

};


template <typename K>
void Grafo<K>::insert_vertice(string vertice){
    Lista<K>* tmp = this->lista_adj;
    // si no fue encontrado el vertice, agregarlo a la lista principal
    if (!tmp->search(vertice)){
        this->lista_adj.insert(vertice);
    }// si fue encontrado el vertice
    else{
        cout << "la lista ya contiene al nodo: " << vertice << endl;
    }

};


template <typename K>
void Grafo<K>::insert_arista(string origen, string destino, K peso){
    Lista<K>* tmp_principal = this->lista_adj;
    //Lista<K>* lis_adj = new Lista<K>;

    //si existen los nodos en las lista principal de vertices
    if (tmp_principal->search(origen) && tmp_principal->search(destino)){
        // busca la lista de adyacencia del origen
        Lista<K>* ls = tmp_principal->search(origen);
        if (!ls->listaInterna){
            ls->listaInterna = new Lista<string>;
            ls->listaInterna->insert(destino,peso);
        }
    }else{
        cout << "ocurrio un error durante la insercion " << endl;
    }
};

template <typename K>
Lista<K>* Grafo<K>::dijkstra(K origen) {


    // implementación real aquí
    return nullptr;
}

template <typename V>
void Grafo<V>::imprimir(V origen){

    Nodo<int>* tmp = origen;

}

#endif //GRAFO_H
