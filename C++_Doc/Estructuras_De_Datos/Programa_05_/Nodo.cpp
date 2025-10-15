
//
// Created by Jesus Emmanuel Garcia on 10/5/25.
//

#include "Nodo.h"

Nodo::Nodo() : dato(0), sig(nullptr) {}

Nodo::Nodo(Nodo* nodo) : dato(0), sig(nodo) {}

Nodo::Nodo(int dato) : dato(dato), sig(nullptr) {}