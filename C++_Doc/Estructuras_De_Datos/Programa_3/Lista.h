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
    void push_top(Nodo* nodo);
    void push_bottom(Nodo* nodo);
    void insert_at(int posicion);
    bool search();
    bool delete_nodo();
    bool delete_all();
    bool is_empty();
    void show_all();
    void top();
    void last();
    void previous();
    void next();
    int size();

};



#endif //LISTA_H
