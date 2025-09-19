//
// Created by Jesus Emmanuel Garcia on 9/17/25.
//

#include "Lista.h"
#include <iostream>

using namespace std;

ListaDobleLigada::ListaDobleLigada(){
    this->head = nullptr;
}
/*Inicializar
insertar al inicio
insertar al final
-insertar en posicion
-buscar
-eliminar
-eliminar todo
vacia
-mostrar todo
primero
ultimo
anterior
siguiente
tamanho*/

void ListaDobleLigada::push_bottom(Nodo* nodo){
    if (this->head == nullptr){
        head = nodo;
        aux_head = head;
        tail = nodo;
        aux_tail = tail;
    }else{
        head->siguiente = nodo;
        nodo->anterior = head;
        head = head->siguiente;
        aux_head = head;
    }
}

void ListaDobleLigada::push_top(Nodo* nodo){
    if (tail->anterior == nullptr){
        nodo->siguiente = tail;
        tail->anterior = nodo;
        tail = nodo;
        aux_tail = tail;
    }
}

void ListaDobleLigada::insert_at(int posicion){

}

bool ListaDobleLigada::search(){

}

bool ListaDobleLigada::delete_nodo(){

}

bool ListaDobleLigada::delete_all(){

}

bool ListaDobleLigada::is_empty(){

}

void ListaDobleLigada::show_all(){

}

void ListaDobleLigada::top(){

}

void ListaDobleLigada::last(){

}

void ListaDobleLigada::previous(){

}

void ListaDobleLigada::next(){

}

int ListaDobleLigada::size(){

}

void ListaDobleLigada::print_tail_to_head(){
    Nodo* tmp = tail;
    cout << "t" << endl;
    while (tmp){
        cout << tmp->get_tipoDato_actual() << endl;
        tmp = tmp->siguiente;
    }
    cout << "h" << endl;
}

void ListaDobleLigada::print_head_to_tail(){
    Nodo* tmp = head;
    cout << "h" << endl;
    while (tmp){
        cout << tmp->get_tipoDato_actual() << endl;
        tmp = tmp->anterior;
    }
    cout << "t" << endl;
}

// funcion recursiva
void print_to_head(Nodo* nodo ){
    if (nodo == nullptr) return;
    print_to_head(nodo->siguiente);
    cout << nodo->get_tipoDato_actual() << endl;
}

void ListaDobleLigada::print(){
    print_to_head(tail);
}

