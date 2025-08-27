//
// Created by Jesus Emmanuel Garcia on 8/22/25.
//
#include <iostream>
#include <string>

#ifndef GATO_H
#define GATO_H

using namespace std;

class Gato {
public:
    int edad_meses;
    string nombre;
    string raza;

    Gato(){}

    void hacer_ruido();
    void set_edad(int edad);
    void set_nombre_raza(string nombre, string raza);
    void mostrar_caracteristicas();
};


#endif //GATO_H
