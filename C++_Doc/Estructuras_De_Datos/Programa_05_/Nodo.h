// Nodo.h
#pragma once

class Nodo {
public:
    int dato;
    Nodo* sig;

    Nodo();
    Nodo(Nodo* nodo);
    Nodo(int dato);
};
