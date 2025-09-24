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
    if (head == nullptr){
        head = tail = nodo;
        return;
    }
    if (head == tail){
        tail->siguiente = nodo;
        nodo->anterior = head;
        tail = nodo;
        aux_tail = tail;
    }else{
        tail->siguiente = nodo;
        nodo->anterior = tail;
        tail = nodo;
        aux_tail = tail;
    }
}

void ListaDobleLigada::push_top(int dato){
    Nodo* nodo = new Nodo(dato);
    // caso lista vacia
    if (head == nullptr){
        head  = tail = nodo;
        return;
    }
    // caso lista hay un elemento
    if (head == tail){
        nodo->siguiente = head;
        head->anterior = nodo;
        head = nodo;
        return;
    }
    nodo->siguiente = head;
    head->anterior = nodo;
    nodo->anterior = nullptr;
    head = nodo;
}

void ListaDobleLigada::insert_at(int posicion, Nodo* nodo){
    int inicial_pos = 0;
    int tamaño_lista = size();
    Nodo* izquierda = head;
    Nodo* derecha = tail;


    if (posicion == 0){
        push_top(nodo->get_tipoDato_actual());
        return;
    }
    if (posicion == tamaño_lista){
        push_bottom(nodo);
        return;
    }
    if (posicion > tamaño_lista){
        cout << "Estas intentando añadir un elemento fuera del rango de la lista" << endl;

        return;
    }


    // suponiendo que esta en medio de la lista

    // comprobar que es mayor ahora
    // ej insertar en la posicion 2 / 10
    if (posicion < (tamaño_lista / 2)){
        while (inicial_pos != posicion){
            izquierda = izquierda->siguiente;
            inicial_pos++;
        }
        // esta en la primera mitad de la lista
        nodo->siguiente = izquierda->siguiente;
        izquierda->siguiente->anterior = nodo;
        izquierda->siguiente = nodo;
        nodo->anterior = izquierda;
    }else{
        while (tamaño_lista != posicion){
            derecha = derecha->anterior;
            tamaño_lista--;
        }
        // esta en la segunda mitad de la lista
        derecha->anterior->siguiente = nodo;
        nodo->anterior = derecha->anterior;
        nodo->siguiente = derecha;
        derecha->anterior = nodo;
    }
}

Nodo* ListaDobleLigada::search(int posicion){
    int tamaño_lista = size()-1;
    int pos_list = 0;
    Nodo* derecha = tail;
    Nodo* izquierda = head;

    if (posicion == 0)return head;
    if (posicion == size()-1)return tail;
    if (posicion < 0 || posicion > tamaño_lista) return nullptr;

    if (posicion < tamaño_lista / 2){
        while (izquierda){
            if (pos_list == posicion){
                return izquierda;
            }
            izquierda = izquierda->siguiente;
            pos_list++;
        }
    }else{
        pos_list = tamaño_lista;
        while (derecha){
            if (pos_list == posicion){
                return derecha;
            }
            derecha = derecha->anterior;
            pos_list--;
        }
    }
    return nullptr;
}

bool ListaDobleLigada::delete_nodo(int posicion){
    int tamaño_lista = size();
    int recorrido = 0;
    Nodo* tmp = nullptr;
    Nodo* tmpR;
    if (head == nullptr)return false;
    if (posicion >= tamaño_lista)return false;

    if (posicion == 0){
        Nodo* tmpN = head;
        head = head->siguiente;
        delete tmpN;
        tmpN = nullptr;
        return true;
    }
    // esta al final el que vamos a eliminar
    if (posicion == tamaño_lista -1){
        tmp = tail;
        tail = tail->anterior;
        delete tmp;
        tail->siguiente = nullptr;
        return true;
    }

    // si es menor esta en la primera mitad
    if (posicion < tamaño_lista / 2){
        tmpR = head;
        if (head->siguiente != nullptr)
            tmp = head->siguiente;

        while (tmp){
            if (recorrido == posicion){
                tmpR->siguiente = tmp->siguiente;

                tmp->siguiente->anterior = tmpR;
                delete tmp;
                return true;
            }
            tmpR = tmp;
            tmp = tmp->siguiente;
            recorrido++;
        }
    }

    // si esta en la segunda mitad de la lista
    if (posicion >= tamaño_lista / 2) {
        tmpR = tail;
        recorrido = tamaño_lista - 1;

        while (tmpR) {
            if (recorrido == posicion) {
                if (tmpR->anterior != nullptr){
                    tmpR->anterior->siguiente = tmpR->siguiente;
                }
                else{
                    // si es el head
                    head = tmpR->siguiente;
                }

                if (tmpR->siguiente){
                    tmpR->siguiente->anterior = tmpR->anterior;
                }
                else{
                    tail = tmpR->anterior; // si es el tail
                }
                delete tmpR;
                return true;
            }
            tmpR = tmpR->anterior;
            recorrido--;
        }
    }

    return false;
}

bool ListaDobleLigada::delete_nodo(int posicion, Nodo* nodo){

}

void ListaDobleLigada::delete_all(){
    while (head){
        Nodo* tmp = head;
        head = head->siguiente;
        delete tmp;
    }
}

bool ListaDobleLigada::is_empty(){
    return head == nullptr;
}

void ListaDobleLigada::top(){
    cout << "Top: " << head->get_tipoDato_actual() << endl;
}

void ListaDobleLigada::last(){
    cout << "Top: " << tail->get_tipoDato_actual() << endl;
}

void ListaDobleLigada::previous(){
    if (tail->anterior)
    cout << "Previous: " << tail->anterior->get_tipoDato_actual() << endl;

}

void ListaDobleLigada::next(){
    if (head->siguiente)
        cout << "Next: " << head->siguiente->get_tipoDato_actual() << endl;

}

int ListaDobleLigada::size(){
    int tamaño = 0;
    Nodo* tmp = head;
    while (tmp){
        tmp = tmp->siguiente;
        tamaño++;
    }
    //cout << "tamaño = " << tamaño << endl;
    return tamaño;
}

void ListaDobleLigada::print_tail_to_head(){
    Nodo* tmp = tail;
    cout << "t" << endl;
    while (tmp){
        cout << tmp->get_tipoDato_actual() << endl;
        tmp = tmp->anterior;
    }
    cout << "h" << endl;
}

void ListaDobleLigada::print_head_to_tail(){
    Nodo* tmp = head;
    cout << "h" << endl;
    while (tmp){
        cout << tmp->get_tipoDato_actual() << endl;
        tmp = tmp->siguiente;
    }
    cout << "t" << endl;
}

// funcion recursiva
void print_to_head(Nodo* nodo ){
    if (nodo == nullptr) return;
    print_to_head(nodo->anterior);
    cout << nodo->get_tipoDato_actual() << endl;
}

void ListaDobleLigada::print(){
    print_to_head(tail);
}

