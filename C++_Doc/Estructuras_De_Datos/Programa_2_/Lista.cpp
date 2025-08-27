//
// Created by Jesus Emmanuel Garcia on 8/27/25.
//

#include "Lista.h"
#include <iostream>
using namespace std;

void Lista::push_bottom(Nodo* nodo){
    if (head == nullptr){
            head = nodo;
            head->siguiente = nullptr;
            aux = head;
    }else{
        Nodo* temp = aux;
        while (temp->siguiente){
            temp = temp->siguiente;
        }
        temp->siguiente = nodo;
        nodo->siguiente = nullptr;
    }
}

void Lista::push_up(Nodo* nodo){
    if (head == nullptr){
        head = nodo;
        head->siguiente = nullptr;
        aux = head;
    }else{
        nodo->siguiente = head;
        head = nodo;
    }
}


/*
 *void Lista::push_bottom(Nodo* nodo){
    Nodo* tmp = aux;
    nodo->siguiente = nullptr;
    if (aux){
        cout << "aux value: " << aux->valor << "\n";
    }
    if (tmp){
        cout << "tmp value: " << tmp->valor << "\n";
    }
    /*
     *
     * Logica
     * Nodo ya tiene un valor asignado
     * mientras tmp no sea null
     * el link al siguiente nodo (valor) es igual a aux ( primera posicion )
     * y tmp se actualiza al siguiente nodo
     #1#
    if (aux == nullptr){
        aux = nodo;
        head = nodo;
    }else{
        Nodo* tmp = aux;
        while (tmp->siguiente){
            tmp = tmp->siguiente;
        }
        tmp->siguiente = nodo;
    }
}
*/

void Lista::print_elements() const{
    Nodo* dummy = head;
    while (dummy != nullptr){
        cout << "Print Elements : " << dummy->valor << "\n";
        dummy = dummy->siguiente;
    }
}

void Lista::print_first_element() const{
    cout << "First element " << head->valor << "\n";
};

void Lista::print_last_element() const{
    Nodo* tmp = head;
    while (tmp->siguiente){
        tmp = tmp->siguiente;
    }
    cout << "Last element " << tmp->valor << "\n";
};


void Lista::print_aux() const{
    if (aux){
        cout << "Aux Value  " << aux->valor << "\n";
    }else{
        cout << "Aux Has no value" << "\n";
    }
}

void Lista::print_aux_next() const{
    if (aux->siguiente){
        cout << "Aux Next Value  " << aux->siguiente->valor << "\n";
    }else{
        cout << "Aux Next Has no value" << "\n";
    }
}