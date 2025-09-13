//
// Created by yo on 13/09/25.
//

#include "Alumno.h"

Alumno::Alumno(int codigo, double promedio, string nombre, int edad, int semestre) {
    this->codigo = codigo1();
    this->promedio = promedio;
    this->nombre = nombre;
    this->edad = edad;
    this->semestre = semestre;
}

int Alumno::codigo1() {
    return codigo;
}

double Alumno::promedio1() {
    return promedio;
}

string Alumno::nombre1() {
    return nombre;
}

int Alumno::edad1() {
    return edad;
}

int Alumno::semestre1() {
    return semestre;
}
