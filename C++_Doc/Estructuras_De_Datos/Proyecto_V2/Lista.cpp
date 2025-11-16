//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#include <iostream>
#include "Lista.h"

using namespace std;


Lista::Lista(){};


void Lista::insert(Nodo* tmp){
    //Nodo* tmp = new Nodo(value);
    if (head == nullptr){
        aux = tmp;
        head = aux;
        head->sig = aux->sig;
    }else{
        aux->sig = tmp;
        aux = aux->sig;
    }
};


/*
void Lista::insert(Nodo* tmp){
    //Nodo* tmp = new Nodo(value);
    
    if (head == nullptr){
        aux = tmp;
        head = aux;
        head->sig = aux->sig;
    }else{
        aux->sig = tmp;
        aux = aux->sig;
    }
};*/


void Lista::insert_at(int pos, Nodo* tmp){
    //Nodo* tmp = new Nodo(value);
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
        Nodo* tmp_h = head;
        while (contador_aux < pos - 1){ // recorre hasta llegar al indice de la posicion indicada
            tmp_h = tmp_h->sig;
            contador_aux++;
        }
        // una vez llega a la posicion indicada
        tmp->sig = tmp_h->sig;
        tmp_h->sig = tmp;
    }

};


void Lista::delete_at(int pos){

};


Nodo* Lista::search(string value){
    Nodo* tmp = head;
    while (tmp){
        if (tmp->vertice_num == value){
            return tmp;
        }
        tmp = tmp->sig;
    }
    return nullptr;
};

int Lista::search_index(string value){
    Nodo* tmp = head;
    int contador = 0;
    while (tmp){
        if (tmp->vertice_num == value){
            return contador;
        }
        tmp = tmp->sig;
    }
    return -1;
};

int Lista::size(){
    Nodo* tmp = head;
    int size = 0;
    while (tmp){
        size++;
        tmp = tmp->sig;
    }
    return size;
};


bool Lista::is_empty(){
 return head ? true : false;
};


void Lista::print_all(){
    Nodo* tmp = head;
    while (tmp != nullptr){
        cout << tmp->vertice_num << endl;
        tmp = tmp->sig;
    }
}


Nodo* Lista::get(int posicion){
    Nodo* tmp = head;
    int contador = 0;

    while (tmp) {
        if (contador == posicion) {
            return tmp;
        }
        tmp = tmp->sig;
        contador++;
    }

    return nullptr; // por si no existe la posición
}


Nodo* Lista::get(std::string posicion) {
    Nodo* tmp = head;

    while (tmp) {
        if (tmp->vertice_num == posicion) {
            return tmp;
        }
        tmp = tmp->sig;
    }

    return nullptr;
}


/*
T* Lista::get_list(int pos) {
    Nodo* tmp = head;
    int contador = 0;

    while (tmp) {
        if (contador == pos) {
            return &tmp->valor;  // porque valor ES un T, no un Nodo<T>
        }
        tmp = tmp->sig;
        contador++;
    }

    return nullptr;
}*/