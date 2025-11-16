//
// Created by Jesus Emmanuel Garcia on 8/27/25.
//
#include "Lista.h"
#include "Nodo.h"


Nodo::Nodo(int peso){
    this->peso = peso;
}

Nodo::Nodo(int peso, std::string vertice_str){
    this->peso = peso;
    this->vertice_num = vertice_str;
};

Nodo::Nodo(std::string vertice){
    this->vertice_num = vertice;
}