//
// Created by Jesus Emmanuel Garcia on 9/17/25.
//

#include "Nodo.h"

Nodo::Nodo(){

}

Nodo::Nodo(int tipo_dato){
    this->tipo_dato = tipo_dato;
}

Nodo::Nodo(int tipo_dato, Nodo* siguiente){
    this->tipo_dato = tipo_dato;
    this->siguiente = siguiente;
}

int Nodo::get_tipoDato(){
    return this->tipo_dato;
};

void Nodo::set_tipoDato(int dato){
    this->tipo_dato = dato;
};