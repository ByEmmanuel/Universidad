#include<iostream>
#include "Nodo.h"

Nodo::Nodo() {
	dato = 0;
	sig = nullptr;
	ant = nullptr;
}

Nodo::Nodo(int dato){
	this->dato = dato;
	sig = nullptr;
	ant = nullptr;
}

Nodo::Nodo(int dato, Nodo* sig, Nodo* ant) {
	this->dato = dato;
	this->sig = sig;
	this->ant = ant;
}

Nodo::~Nodo() {

}


int Nodo::getDato() {
	return dato;
}

Nodo* Nodo::getsig() {
	return sig;
}

Nodo* Nodo::getant() {
	return ant;
}


void Nodo::setsig(Nodo* sig) {
	this->sig = sig;
}
 
void Nodo::setant(Nodo* ant) {
	this->ant = ant;
}
