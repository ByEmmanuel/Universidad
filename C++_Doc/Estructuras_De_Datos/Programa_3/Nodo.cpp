//
// Created by Jesus Emmanuel Garcia on 9/17/25.
//

#include "Nodo.h"

Nodo::Nodo(){

}

Nodo::Nodo(Alumno* tipo_dato){
    this->tipo_dato = tipo_dato;
}

Nodo::Nodo(Alumno* tipo_dato, Nodo* siguiente){
    this->tipo_dato = tipo_dato;
    this->siguiente = siguiente;
}

Alumno* Nodo::get_tipoDato_actual(){
    return this->tipo_dato;
};