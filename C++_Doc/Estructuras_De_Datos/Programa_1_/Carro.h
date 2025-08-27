//
// Created by Jesus Emmanuel Garcia on 8/22/25.
//
#include <string>

#ifndef CARRO_H
#define CARRO_H

using namespace std;

class Carro {
public:
    string marca;
    string modelo;
    int año;

    void set_marca(string marca);
    void set_modelo(string modelo);
    void set_año(int año);
    void imprimir();

};



#endif //CARRO_H
