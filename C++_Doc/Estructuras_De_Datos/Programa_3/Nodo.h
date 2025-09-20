//
// Created by Jesus Emmanuel Garcia on 9/17/25.
//

#ifndef NODO_H
#define NODO_H

#include "Alumno.h"

class Nodo {
public:
    Nodo* siguiente;
    Nodo* anterior;
    Alumno* tipo_dato;
    Nodo();
    Nodo(Alumno* tipo_dato);
    Nodo(Alumno* tipo_dato, Nodo* siguiente);

    /*Nodo* get_siguiente();
    Nodo* get_anterior();*/
    Alumno* get_tipoDato_actual();
};



#endif //NODO_H
