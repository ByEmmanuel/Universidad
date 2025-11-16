//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#include "ListaEnlazada.h"
#include <iostream>

using namespace std;

/*
ListaEnlazada::ListaEnlazada() : head(nullptr), tail(nullptr), cantidad(0) {}

ListaEnlazada::~ListaEnlazada() {
    Nodo* actual = head;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaEnlazada::insertar(std::string valor) {
    Nodo* nuevo = new Nodo(valor);

    if (head == nullptr) {
        head = nuevo;
        tail = nuevo;
    } else {
        tail->siguiente = nuevo;
        tail = nuevo;
    }
    cantidad++;
}

void ListaEnlazada::eliminar(std::string valor) {
    if (head == nullptr) return;

    // Si es el primer nodo
    if (head->valor == valor) {
        Nodo* temp = head;
        head = head->siguiente;
        if (head == nullptr) tail = nullptr;
        delete temp;
        cantidad--;
        return;
    }

    // Buscar en el resto
    Nodo* actual = head;
    while (actual->siguiente != nullptr) {
        if (actual->siguiente->valor == valor) {
            Nodo* temp = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            if (actual->siguiente == nullptr) tail = actual;
            delete temp;
            cantidad--;
            return;
        }
        actual = actual->siguiente;
    }
}

Nodo* ListaEnlazada::buscar(std::string valor) {
    Nodo* actual = head;
    while (actual != nullptr) {
        if (actual->valor == valor) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

int ListaEnlazada::buscar_indice(std::string valor) {
    Nodo* actual = head;
    int indice = 0;
    while (actual != nullptr) {
        if (actual->valor == valor) {
            return indice;
        }
        actual = actual->siguiente;
        indice++;
    }
    return -1;
}

Nodo* ListaEnlazada::obtener(int indice) {
    if (indice < 0 || indice >= cantidad) return nullptr;

    Nodo* actual = head;
    int contador = 0;
    while (actual != nullptr) {
        if (contador == indice) {
            return actual;
        }
        actual = actual->siguiente;
        contador++;
    }
    return nullptr;
}

int ListaEnlazada::tamaño() {
    return cantidad;
}

bool ListaEnlazada::esta_vacia() {
    return head == nullptr;
}

void ListaEnlazada::imprimir() {
    Nodo* actual = head;
    while (actual != nullptr) {
        cout << actual->valor << " -> ";
        actual = actual->siguiente;
    }
    cout << "nullptr" << endl;
}

Nodo* ListaEnlazada::obtener_cabeza() {
    return head;
}
*/
