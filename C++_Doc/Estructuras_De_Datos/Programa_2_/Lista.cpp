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

void Lista::print_elements() const{
    Nodo* dummy = head;
    while (dummy != nullptr){
        cout << "Print Elements : " << dummy->valor << "\n";
        dummy = dummy->siguiente;
    }
}

//Retornar indice
// Esto retorna un nodo ( objeto ) con el valor del indice a buscar
Nodo* Lista::index_of(Nodo* nodo) {
    int contador = 0;
    Nodo* tmp = head;
    while (tmp) {
        if (tmp->valor == nodo->valor ) {
            return new Nodo(contador);
        }
        contador++;
        tmp = tmp->siguiente;
    }
    return nullptr;
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

int Lista::size() {
    Nodo* nodo = head;
    if (!head){
        return 0;
    }
    int contador = 1;
    while (nodo->siguiente != nullptr) {
        if (nodo->siguiente){
        nodo = nodo->siguiente;
        contador++;
        }else{
            break;
        }
    }
    return contador ;
}

bool Lista::insert_at(int posicion, Nodo* nodo){
    if (posicion < 0)return false;

    if (posicion == 0){
        nodo->siguiente = head;
        head = nodo;
        return true;
    }

    // este metodo siempre  devolvera true sin importar el resultado
    if (posicion == size() -1){
        Nodo* tmp = head;
        while (tmp->siguiente){
            tmp = tmp->siguiente;
        }
        tmp->siguiente = nodo;
        return true;
    }

    Nodo* tmp = head;
    int contador = 0;
    while (tmp->siguiente){
        if (contador == posicion){
            break;
        }
        tmp = tmp->siguiente;
        contador++;
    }
    nodo->siguiente = tmp->siguiente;
    tmp->siguiente = nodo;

}

bool Lista::is_empty() const {
    return head == nullptr;
};
// no terminado
bool Lista::remove(int indice) {
    Nodo* dummy = head;
    int contador = 0;
    while (dummy->siguiente) {
        if (contador == indice) {
            Nodo* aux_2_ = dummy;
            while (aux->siguiente != nullptr) {
                head = aux_2_->siguiente;
                dummy = dummy->siguiente;
            }
            return true;
        }
        dummy = dummy->siguiente;
        contador++;
    }
    return false;
};


// este metodo no esta bien
// esto recorre todos los nodos anteriores
// aux apunta al ultimo elemento
void Lista::contemplate_aux(){
    Nodo* dummy = aux;

    while (dummy) {
        cout << dummy->valor << "\n";
        dummy = dummy->siguiente;
    }
}
//Eliminar arriba ( en el head )
void Lista::pop_up(){
    if (head->siguiente){
        Nodo* tmp = head;
        head = tmp->siguiente;
        delete tmp;
    }
}

void Lista::pop_bottom(){
    if (head->siguiente){
        Nodo* tmp = head;
        Nodo* tmpR = tmp;
        while (tmp->siguiente){
            tmpR = tmp;
            tmp = tmp->siguiente;
        }
        tmpR->siguiente = nullptr;
    }
}

void Lista::print_reverse(){
    // size n
    int tamaño = size()-1;

    Nodo* tmp = head;

    while (tamaño >= 0){
        for (int i = 0; i < tamaño; i++){
            if (tmp->siguiente){
                tmp = tmp->siguiente;
            }
        }
        cout << "Print Reverse: " << tmp->valor << "\n";
        tamaño--;
        tmp = head;
    }
}