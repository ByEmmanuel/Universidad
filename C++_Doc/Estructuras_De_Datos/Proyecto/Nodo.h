//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo{
public:
    T valor;
    Nodo<T>* sig;
    Nodo() : valor(), sig(nullptr) {}
    Nodo(T valor) : valor(valor), sig(nullptr) {}
    Nodo(Nodo<T>* sig) : valor(), sig(sig) {}
    Nodo(Nodo<T>* sig, T valor) : valor(valor), sig(sig) {}

};

#include "Nodo.tpp"


#endif //NODO_H
