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
    int tipo_dato;
    Nodo();
    Nodo(int tipo_dato);
    Nodo(int tipo_dato, Nodo* siguiente);

    /*Nodo* get_siguiente();
    Nodo* get_anterior();*/
    int get_tipoDato_actual();
};



#endif //NODO_H
