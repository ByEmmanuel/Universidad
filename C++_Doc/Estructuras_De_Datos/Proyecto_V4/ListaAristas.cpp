#include "ListaAristas.h"
#include <iostream>

using namespace std;

ListaAristas::ListaAristas() {
    head = nullptr;
    tail = nullptr;
    cantidad = 0;
}

void ListaAristas::insertar(string destino, int peso){
    NodoArista* tmp = new NodoArista(destino, peso);

    if (head == nullptr){
        head = tmp;
        tail = head;
    }else{
        tail->sig = tmp;
        tail = tmp;
    }
    cantidad++;

};

void ListaAristas::eliminar(string destino){
    // no hay lista de lista original
    if(head == nullptr)return;
    
    // recordamos que hay 3 casos, al inicio, al final y en posicion, pero el segundo condicional hace en POS y al final
    // si es el primero
    if(head->destino == destino){
        NodoArista* tmp = head;
        head = head->sig;
        if(head == nullptr){
            tail = nullptr;
        }
        delete tmp;
        cantidad--;
        return;
    }

    NodoArista* tmp = head;
    while(tmp->sig != nullptr){
        if(tmp->sig->destino == destino){
            // eliminacion de toda la vida
            NodoArista* a_borrar = tmp->sig;
            tmp->sig = tmp->sig->sig;
            if(tmp->sig == nullptr){
                tail = tmp;
            }
            delete a_borrar;
            cantidad--;
            return;
        }
        tmp = tmp->sig;
    }
}


NodoArista* ListaAristas::buscar_por_destino(string destino){
    NodoArista* tmp = head;

    while (tmp){
        if(tmp->destino == destino){
            return tmp;
        }
        tmp = tmp->sig;
    }
    return nullptr;
};

NodoArista* ListaAristas::get_by_index(int pos){
    if(pos < 0 || pos >= cantidad)return nullptr;

    NodoArista* tmp = head;
    int contador = 0;
    while (tmp){
        if(contador == pos){
            return tmp;
        }
        tmp = tmp->sig;
        contador++;
    }
    return nullptr;
};

int ListaAristas::size(){
    return cantidad;
};

bool ListaAristas::is_empty(){
    return head == nullptr;
};

void ListaAristas::imprimir(){
    NodoArista* tmp = head;

    while (tmp){
        cout << "Destino: " << tmp->destino << " Peso: " << tmp->peso << endl;
        tmp = tmp->sig;
    }
    cout << " null " << endl;
}

NodoArista* ListaAristas::get_head(){
    return this->head;
}