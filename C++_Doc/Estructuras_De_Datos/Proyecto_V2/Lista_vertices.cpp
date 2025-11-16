//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#include "Lista_vertices.h"

#include <iostream>

Lista_vertices::Lista_vertices() {
    vertices_head = nullptr;
    aux = nullptr;
    lista_aristas = nullptr;
    cantidad_vertices = 0;
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

    // Crear una nueva lista de aristas para este vértice
    expandir_lista_aristas();
}

void Lista_vertices::expandir_lista_aristas(){
    // Crear un nuevo array más grande
    Lista** temp = new Lista*[cantidad_vertices +1];

    if (lista_aristas != nullptr) {
    for (int i = 0; i < cantidad_vertices; i++) {
        temp[i] = lista_aristas[i];
    }
}
    // Inicializar el nuevo puntero a lista
    temp[cantidad_vertices] = new Lista();
    // Liberar el array anterior // esto me lo dio la IA
    if (lista_aristas != nullptr) {
        delete[] lista_aristas;
    }

    lista_aristas = temp;
    cantidad_vertices++;
}

void Lista_vertices::agregar_lista_aristas(int indice, Lista* lista){
    if (indice >= 0 && indice < cantidad_vertices) {
        lista_aristas[indice] = lista;
    }
}

Lista* Lista_vertices::obtener_lista_aristas(int indice){
    if (indice >= 0 && indice < cantidad_vertices) {
        return lista_aristas[indice];
    }
    return nullptr;
}