//
// Created by Jesus Emmanuel Garcia on 8/27/25.
//

#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"


class Lista {
private:
    Nodo* head = nullptr;
    Nodo* aux = head;

public:
    virtual ~Lista() = default;

    Lista();
    virtual void insert(Nodo* value);
    virtual void insert_at(int pos, Nodo* value);
    virtual void delete_at(int pos);
    virtual Nodo* search(std::string value);
    virtual int size();
    virtual bool is_empty();
    virtual void print_all();
    virtual Nodo* get(int posicion);
    //virtual Nodo* get_list(int pos);
    virtual Nodo* get(std::string posicion);

};



#endif //LISTA_H
