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
    // retorna un nodo ( indice ) del elemento buscado
    Nodo* index_of(int codigo);
    // inserta en posicion
    bool insert_at(int posicion, Nodo* nodo_valor);
    // imprime el ultimo elemento
    void _last_element() const;
    // imprime el primer elemento
    void _first_element() const;
    // imprime el tamaño de la lista
    int size();
    // verifica si la lista esta vacia
    bool is_empty() const;
    // remueve por indice
    bool remove(int indice);
    // remueve por objeto
    bool remove(Nodo* objeto);
    // borrar todo
    void clear_all();
    // eliminar al inicio
    void pop_up();
    // eliminar al final
    void pop_bottom();


    // imprimir valores de los nodos en orden de arriba a abajo
    void print_elements() const;
    // imprimir valores de los nodos en orden de abajo hacia arriba
    void print_reverse();
    // imprime el valor que contiene auxiliar en el estado actual
    // metodos de depuracion / para conocer el estado actual de auxiliar
    void print_aux() const;
    // imprime el valor del auxiliar en su estado siguiente
    void print_aux_next() const;
    // recorrer auxiliar
    void contemplate_aux();

};



#endif //LISTA_H
