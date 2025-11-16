//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#include "Grafo.h"

#include <iostream>

// como va a ser el grafo????
/*
 * El grafo sera una lista de listas
 * Tendra una lista principal
 * De esas listas principales tendra listas abyacentes
 *
 *
 */



Grafo::Grafo(){
    this->list_adj = new Lista_vertices();
};

void Grafo::insertar_vertice(const std::string& vertice){
    this->list_adj->insert(vertice);

};

void Grafo::insertar_arista(string origen, string& destino, int peso){
    int index = this->list_adj->search_index(origen);
    Lista* adj;
    if (index >= 0){
        adj = list_adj->obtener_lista_aristas(index);
        Nodo* nodo_tmp = new Nodo(peso, destino);
        adj->insert(nodo_tmp);

        //list_adj->agregar_lista_aristas(index,adj);
    }

};

void Grafo::print_vertices(){
    Nodo* tmp = this->list_adj->vertices_head;
    while (tmp){
        std::cout << tmp->vertice_num << endl;
        tmp = tmp->sig;
    }
}

void Grafo::print_all(){
    int contador = 0;
    Nodo* lista_vertices = list_adj->vertices_head;

    while (lista_vertices){
        cout << lista_vertices->vertice_num << endl;

        Lista** aristas = list_adj->lista_aristas;

        for (int i = 0; i < aristas[contador]->size(); i++){

            cout << aristas[contador]->get(i)->vertice_num << endl;
        }

        lista_vertices = lista_vertices->sig;
    }

}

/*
void Grafo::print_all() {
    Nodo* v = list_adj->vertices_head;
    int vIndex = 0;

    while (v) {
        cout << "Vertice: " << v->vertice_num << endl;

        Lista* lista = list_adj->lista_aristas[vIndex];

        // Recorrer aristas del vértice
        for (int eIndex = 0; eIndex < lista->size(); eIndex++) {
            cout << "  -> " << lista->get(eIndex)->vertice_num << endl;
        }

        v = v->sig;
        vIndex++;
    }
}*/