//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#include <iostream>
#include "Lista.h"

using namespace std;

template <typename T>
Lista<T>::Lista(){};

template <typename T>
void Lista<T>::insert(T value){
    Nodo<T>* tmp = new Nodo(value);
    if (head == nullptr){
        aux = tmp;
        head = aux;
        head->sig = aux->sig;
    }else{
        aux->sig = tmp;
        aux = aux->sig;
    }
};

template <typename T>
void Lista<T>::insert_at(int pos, T value){
    Nodo<T>* tmp = new Nodo(value);
    int tamaño = size();
    // insertar arriba ( top )
    if (pos <= 0){
        tmp->sig = head;
        head = tmp;
    }else if (pos > tamaño){// insertar al ultimo
        aux->sig = tmp;
        aux = aux->sig;
    }else{  // en posicion
        int contador_aux = 0;
        Nodo<T>* tmp_h = head;
        while (contador_aux < pos - 1){ // recorre hasta llegar al indice de la posicion indicada
            tmp_h = tmp_h->sig;
            contador_aux++;
        }
        // una vez llega a la posicion indicada
        tmp->sig = tmp_h->sig;
        tmp_h->sig = tmp;
    }

};

template <typename T>
void Lista<T>::delete_at(int pos){

};

template <typename T>
Nodo<T>* Lista<T>::search(T value){

};

template <typename T>
int Lista<T>::size(){
    Nodo<T>* tmp = head;
    int size = 0;
    while (tmp){
        size++;
        tmp = tmp->sig;
    }
    return size;
};

template <typename T>
bool Lista<T>::is_empty(){
 return head ? true : false;
};

template <typename T>
void Lista<T>::print_all(){
    Nodo<T>* tmp = head;
    while (tmp != nullptr){
        cout << tmp->valor << endl;
        tmp = tmp->sig;
    }
}
