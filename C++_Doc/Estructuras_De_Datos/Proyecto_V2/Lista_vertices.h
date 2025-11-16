//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#ifndef LISTA_VERTICES_H
#define LISTA_VERTICES_H
#include "Lista.h"
#include "Nodo.h"


class Lista_vertices : public Lista {
public:
    Nodo* vertices_head = nullptr;
    Nodo* aux = vertices_head;
    Lista** lista_aristas = nullptr;
    int cantidad_vertices = 0;         // Para trackear cuantas listas de aristas tenemos


    Lista_vertices();

    void insert(const std::string& vertice);
    void expandir_lista_aristas();
    void agregar_lista_aristas(int indice, Lista* lista);
    Lista* obtener_lista_aristas(int indice);
    /*void insert_at(int pos, Nodo* value)override;
    void delete_at(int pos)override;
    Nodo* search(std::string value)override;
    int size() override;
    bool is_empty()override;
    void print_all()override;
    Nodo* get(int posicion)override;
    //Nodo* get_list(int pos)override;
    Nodo* get(std::string posicion)override;*/

};



#endif //LISTA_VERTICES_H
