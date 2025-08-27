//
// Created by Jesus Emmanuel Garcia on 8/22/25.
//

#include "Carro.h"
#include <iostream>
using namespace std;

void Carro::set_marca(string marca){
    this->marca = marca;
};

void Carro::set_modelo(string modelo){
    this->modelo = modelo;
};

void Carro::set_año(int año){
    this->año = año;
};

void Carro::imprimir(){
    cout << "Marca del carro: " << this->marca << "\n";
    cout << "Modelo del carro: " << this->modelo <<"\n";
    cout << "Año del carro: " << this->año << "\n\n";
};
