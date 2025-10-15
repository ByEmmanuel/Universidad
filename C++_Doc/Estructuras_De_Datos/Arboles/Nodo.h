#ifndef NODO_H
#define NODO_H

#include "Nodo.h"


class Nodo{
    public:
        Nodo();
        int valor;
        Nodo* izq;
        Nodo* der;


        Nodo(int dato);
        Nodo(Nodo* izq, Nodo* der);

        Nodo(int valor, Nodo* izq, Nodo* der);

        virtual ~Nodo();






    protected:

    private:
};

#endif // NODO_H
