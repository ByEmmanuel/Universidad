//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#include "NodoArista.h"

NodoArista::NodoArista(std::string dest, int p)
    : destino(dest), peso(p), siguiente(nullptr) {}

NodoArista::~NodoArista() {}