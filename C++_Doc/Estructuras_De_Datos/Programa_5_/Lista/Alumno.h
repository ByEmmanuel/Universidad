//
// Created by Jesus Emmanuel Garcia on 9/17/25.
//

#ifndef ALUMNO_H
#define ALUMNO_H

#include <string>
using namespace  std;

class Alumno {
private:
    string nombre;
    string apellido;
    int edad;
    string matricula;
    float promedio;

public:
    Alumno();
    Alumno(string nombre,   string apellido, int edad,   string matricula, float promedio);
    Alumno(  string nombre,   string matricula);

    ~Alumno();

    string get_nombre() ;
    string get_apellido();
    int get_edad() ;
    string get_matricula();
    float get_promedio();


    void set_nombre(string& nombre);
    void set_apellido(string& apellido);
    void set_edad(int edad);
    void set_matricula(string& matricula);
    void set_promedio(float promedio);

    string toString() const;
};

#endif //ALUMNO_H