//
// Created by yo on 13/09/25.
//

#ifndef ESTRUCTURAS_DE_DATOS_PROGRAMA_1__ALUMNO_H
#define ESTRUCTURAS_DE_DATOS_PROGRAMA_1__ALUMNO_H

#include <string>

using namespace std;

class Alumno {
private:
    // atributos
    int codigo{};
    double promedio{};
    string nombre;
    int edad{};
    int semestre{};


public:
    // metodos
    Alumno(int codigo, double promedio, string nombre, int edad, int semestre);
    int codigo1();
    double promedio1();
    string nombre1();
    int edad1();
    int semestre1();

};


#endif //ESTRUCTURAS_DE_DATOS_PROGRAMA_1__ALUMNO_H