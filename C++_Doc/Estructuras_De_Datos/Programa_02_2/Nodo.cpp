//
// Created by Jesus Emmanuel Garcia on 8/27/25.
//
#include "Lista.h"
#include "Nodo.h"

Nodo::Nodo(Nodo* nodo){
    this->siguiente = nodo;
}

Nodo::Nodo(Nodo *nodo, Alumno *alumno) {
    this->siguiente = nodo;
    this->alumno = alumno;
}

Nodo::Nodo(Alumno* alumno) {
    this->alumno = alumno;
}
