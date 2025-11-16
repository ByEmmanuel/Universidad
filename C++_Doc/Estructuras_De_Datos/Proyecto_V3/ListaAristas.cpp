//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#include "ListaAristas.h"
#include <iostream>

using namespace std;

ListaAristas::ListaAristas() : head(nullptr), tail(nullptr), cantidad(0) {}

ListaAristas::~ListaAristas() {
    NodoArista* actual = head;
    while (actual != nullptr) {
        NodoArista* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaAristas::insertar(std::string destino, int peso) {
    NodoArista* nuevo = new NodoArista(destino, peso);

    if (head == nullptr) {
        head = nuevo;
        tail = nuevo;
    } else {
        tail->siguiente = nuevo;
        tail = nuevo;
    }
    cantidad++;
}

void ListaAristas::eliminar(std::string destino) {
    if (head == nullptr) return;

    if (head->destino == destino) {
        NodoArista* temp = head;
        head = head->siguiente;
        if (head == nullptr) tail = nullptr;
        delete temp;
        cantidad--;
        return;
    }

    NodoArista* actual = head;
    while (actual->siguiente != nullptr) {
        if (actual->siguiente->destino == destino) {
            NodoArista* temp = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            if (actual->siguiente == nullptr) tail = actual;
            delete temp;
            cantidad--;
            return;
        }
        actual = actual->siguiente;
    }
}

NodoArista* ListaAristas::buscar(std::string destino) {
    NodoArista* actual = head;
    while (actual != nullptr) {
        if (actual->destino == destino) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

NodoArista* ListaAristas::obtener(int indice) {
    if (indice < 0 || indice >= cantidad) return nullptr;

    NodoArista* actual = head;
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

int ListaAristas::tamaño() {
    return cantidad;
}

bool ListaAristas::esta_vacia() {
    return head == nullptr;
}

void ListaAristas::imprimir() {
    NodoArista* actual = head;
    while (actual != nullptr) {
        cout << actual->destino << "(p:" << actual->peso << ") -> ";
        actual = actual->siguiente;
    }
    cout << "nullptr" << endl;
}

NodoArista* ListaAristas::obtener_cabeza() {
    return head;
}