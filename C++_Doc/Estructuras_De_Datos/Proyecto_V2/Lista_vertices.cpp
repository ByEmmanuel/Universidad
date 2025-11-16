//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#include "Lista_vertices.h"

#include <iostream>

Lista_vertices::Lista_vertices(){
    this->lista_aristas = new Lista();

}


// Sobrecarga: recibe std::string y construye el Nodo
void Lista_vertices::insert(const std::string& vertice) {
    Nodo* tmp = new Nodo(vertice);
    tmp->sig = nullptr; // asegura que el nuevo nodo cierre la lista

    if (vertices_head == nullptr) {
        vertices_head = tmp;
        aux = tmp;
    } else {
        aux->sig = tmp;
        aux = tmp;
    }
}

/*void Lista_vertices::insert(Nodo* tmp){
    //Nodo* tmp = new Nodo(value);

};*/