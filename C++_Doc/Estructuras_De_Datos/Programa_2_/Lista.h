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

    void push_up(Nodo* nodo);
    void push_bottom(Nodo* nodo);
    void print_elements() const;

    void print_last_element() const;
    void print_first_element() const;
    void print_aux() const;
    void print_aux_next() const;
};



#endif //LISTA_H
