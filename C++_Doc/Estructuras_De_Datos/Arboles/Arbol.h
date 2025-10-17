#ifndef ARBOL_H
#define ARBOL_H

#include "Nodo.h"


class Arbol
{
    public:
        Arbol();
        Nodo* raiz;
        // esto inserta un nodo -> no en entero
        //void insertar(Nodo* nodo);
        void insertar(int valor, Nodo* raiz);
        void insertar(int valor);
        void mostrar(Nodo* raiz_sub_arbol);
        virtual ~Arbol();

    protected:

    private:
};

#endif // ARBOL_H
