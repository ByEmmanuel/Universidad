//
// Created by Jesus Emmanuel Garcia on 9/17/25.
//

#include "Lista.h"

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

void ListaDobleLigada::push_top(Nodo* nodo){
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

void ListaDobleLigada::push_bottom(Nodo* nodo){

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
