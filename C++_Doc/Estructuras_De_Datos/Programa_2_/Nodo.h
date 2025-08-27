#ifndef NODO_H
#define NODO_H

class Nodo{
public:
    int valor;
    Nodo* siguiente = nullptr;
    Nodo(){}
    Nodo(int valor);
};

#endif // NODO_H
