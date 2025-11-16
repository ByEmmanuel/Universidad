//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#include "NodoVertice.h"

NodoVertice::NodoVertice(std::string nom)
    : nombre(nom), siguiente(nullptr) {
    aristas = new ListaAristas();
}

NodoVertice::~NodoVertice() {
    delete aristas;
}
