#include <iostream>
#include <string>

#include "NodoVertice.h"
#include "ListaAristas.h"

NodoVertice::NodoVertice(){
    this->nombre = "";
    this->sucursal = nullptr;
    this->aristas = new ListaAristas();
    this->sig = nullptr;
}

NodoVertice::NodoVertice(std::string nombre){
    this->nombre = nombre;
    this->sucursal = nullptr;
    this->aristas = new ListaAristas();
    this->sig = nullptr;
}

NodoVertice::NodoVertice(std::string nombre, Sucursal* sucursal){
    this->nombre = nombre;
    this->sucursal = sucursal;
    this->aristas = new ListaAristas();
    this->sig = nullptr;
}

NodoVertice::~NodoVertice(){
    if(sucursal != nullptr){
        delete sucursal;
    }
    if(aristas != nullptr){
        delete aristas;
    }
}