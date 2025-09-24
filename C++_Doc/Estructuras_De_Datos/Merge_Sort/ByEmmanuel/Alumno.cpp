//
// Created by Jesus Emmanuel Garcia on 9/17/25.
//

#include "Alumno.h"
#include <iostream>
#include <sstream>

Alumno::Alumno() {
    this->nombre = "";
    this->apellido = "";
    this->edad = 0;
    this->matricula = "";
    this->promedio = 0.0f;
}

Alumno::Alumno( string nombre,  string apellido, int edad,  string matricula, float promedio) {
    this->nombre = nombre;
    this->apellido = apellido;
    this->edad = edad;
    this->matricula = matricula;
    this->promedio = promedio;
}


Alumno::Alumno( string nombre,  string matricula) {
    this->nombre = nombre;
    this->apellido = "";
    this->edad = 0;
    this->matricula = matricula;
    this->promedio = 0.0f;
}


Alumno::~Alumno() {

}

 string Alumno::get_nombre()  {
    return this->nombre;
}

 string Alumno::get_apellido()  {
    return this->apellido;
}

int Alumno::get_edad(){
    return this->edad;
}

 string Alumno::get_matricula()  {
    return this->matricula;
}

float Alumno::get_promedio()  {
    return this->promedio;
}

// Setters
void Alumno::set_nombre(string& nombre) {
    this->nombre = nombre;
}

void Alumno::set_apellido(string& apellido) {
    this->apellido = apellido;
}

void Alumno::set_edad(int edad) {
    this->edad = edad;
}

void Alumno::set_matricula(string& matricula) {
    this->matricula = matricula;
}

void Alumno::set_promedio(float promedio) {
    this->promedio = promedio;
}

 string Alumno::toString() const {
     ostringstream oss;
    oss << nombre << " " << apellido << " (Mat: " << matricula << ", Edad: " << edad << ", Promedio: " << promedio << ")";
    return oss.str();
}