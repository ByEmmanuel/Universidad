//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#ifndef LISTA_H
#define LISTA_H
#include "Nodo.h"
#include "string"


template <typename T>
class Lista {
    Nodo<T>* head;
    Nodo<T>* aux = head;
    // cada lista tiene su propia lista
    // cuidado con crear listas, crear solo las necesarias
    Lista<T>* listaInterna;

public:

    Lista();
    void insert(T value);
    void insert_at(int pos, T value);
    void delete_at(int pos);
    Nodo<T>* search(T value);
    int size();
    bool is_empty();
    void print_all();
    Nodo<T>* get(int posicion);
    T* get_list(int pos);
    Nodo<T>* get(std::string posicion);



};

#include "Lista.tpp"



#endif //LISTA_H
