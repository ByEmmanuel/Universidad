#ifndef NODO_H
#define NODO_H

#include "Alumno.h"
class Nodo{
private:
    Alumno* alumno;
public:
    // tipo de dato

    Nodo* siguiente = nullptr;
    Nodo(){}
    Nodo(Nodo* nodo);
    Nodo(Nodo* nodo, Alumno* alumno);
    Nodo(Alumno* alumno);

    void set_alumno(Alumno* alumno) {
        this->alumno = alumno;
    }

    Alumno* get_alumno(){
        return this->alumno;
    }
};

#endif // NODO_H
