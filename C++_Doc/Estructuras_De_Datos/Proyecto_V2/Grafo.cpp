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



Lista* list_adj;
Grafo::Grafo(){
this->list_adj = new Lista_vertices();
};

void Grafo::insertar_vertice(const std::string& vertice){
    this->list_adj->insert(vertice);

};

void Grafo::insertar_arista(string origen, string destino, int peso){

};

void Grafo::print_vertices(){
    Nodo* tmp = this->list_adj->vertices_head;
    while (tmp){
        std::cout << tmp->vertice_num << endl;
        tmp = tmp->sig;
    }
}

