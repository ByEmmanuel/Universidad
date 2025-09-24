//
// Created by Jesus Emmanuel Garcia on 9/17/25.
//

#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"

class ListaDobleLigada {
public:
    Nodo* head;
    Nodo* aux_head = head;
    Nodo* tail;
    Nodo* aux_tail = tail;
    int tamano;

    ListaDobleLigada();
    void push_top(int dato);


    // no necesitamos los demas metodos para el merge sort
    void push_bottom(Nodo* nodo);
    void insert_at(int posicion, Nodo* nodo);
    Nodo* search(int posicion);
    bool delete_nodo(int posicion);
    bool delete_nodo(int posicion, Nodo* nodo);
    void delete_all();
    bool is_empty();

    void top();
    void last();
    void previous();
    void next();
    int size();
    void print_tail_to_head();
    void print_head_to_tail();
    void print();

};



#endif //LISTA_H
