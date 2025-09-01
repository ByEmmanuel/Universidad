//
// Created by Jesus Emmanuel Garcia on 8/27/25.
//

#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"


class Lista {
private:
    Nodo* head = nullptr;
    Nodo* aux = head;

public:

    // insertar arriba
    void push_up(Nodo* nodo);
    // insertar atras
    void push_bottom(Nodo* nodo);
    // imprimir valores de los nodos
    void print_elements() const;
    // retorna un nodo ( indice ) del elemento buscado
    Nodo* index_of(Nodo* nodo);
    // imprime el ultimo elemento
    void print_last_element() const;
    // imprime el primer elemento
    void print_first_element() const;
    // imprime el valor que contiene auxiliar en el estado actual
    void print_aux() const;
    // imprime el valor del auxiliar en su estado siguiente
    void print_aux_next() const;
    // imprime el tamaño de la lista
    int size();
    // inserta en posicion
    bool insert_at(int posicion, Nodo* nodo_valor);
    // verifica si la lista esta vacia
    bool is_empty() const;
    // remueve por indice
    bool remove(int indice);
    // remueve por objeto
    bool remove(Nodo* objeto);

    void contemplate_aux();

    void pop_up();

    void pop_bottom();

    void print_reverse();
};



#endif //LISTA_H
