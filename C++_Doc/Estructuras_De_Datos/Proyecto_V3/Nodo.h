//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#ifndef NODO_H
#define NODO_H

#include <string>

class Nodo {
public:
    std::string valor;
    Nodo* siguiente;

    Nodo(std::string val);
    ~Nodo();
};

#endif // NODO_H