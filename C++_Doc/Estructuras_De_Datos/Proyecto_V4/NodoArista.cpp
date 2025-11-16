#include "NodoArista.h"

NodoArista::NodoArista(){};
    
NodoArista::NodoArista(std::string dest, int peso){
    this->destino = dest;
    this->peso = peso;
};

NodoArista::NodoArista(std::string dest, int peso, NodoArista* sig){
    this->destino = dest;
    this->peso = peso;
    this->sig = sig;
};

NodoArista::~NodoArista(){
    // delete nodos
};