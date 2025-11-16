#ifndef NODO_H
#define NODO_H

#include <string>

class Nodo{
public:
    int peso;
    std::string vertice_num;
    Nodo* sig = nullptr;
    Nodo(){}
    Nodo(int peso);
    Nodo(int peso, std::string vertice_num);
    Nodo(std::string vertice);

};

#endif // NODO_H
