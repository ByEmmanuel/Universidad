#include "Nodo.h"

Nodo::Nodo()
{
    //ctor
}

Nodo::Nodo(int dato)
{
    this->valor = dato;
}

Nodo::Nodo(Nodo* izq, Nodo* der){
    this->izq = izq;
    this->der = der;
}

Nodo::Nodo(int valor, Nodo* izq, Nodo* der){
    this->valor = valor;
    this->izq = izq;
    this->der = der;
}

Nodo::~Nodo()
{
    //dtor
}
