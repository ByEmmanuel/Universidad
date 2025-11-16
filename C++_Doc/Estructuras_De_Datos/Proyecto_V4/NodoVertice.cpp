#include <iostream>
#include <string>

#include "NodoVertice.h"
#include "ListaAristas.h"

NodoVertice::NodoVertice(){};

NodoVertice::NodoVertice(std::string nombre){ 
    this->nombre = nombre;
    this->sig = nullptr;
    this->aristas = new ListaAristas();
};

NodoVertice::~NodoVertice(){}