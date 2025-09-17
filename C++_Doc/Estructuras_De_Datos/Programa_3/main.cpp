//
// Created by Jesus Emmanuel Garcia on 9/17/25.
//

#include "Lista.h"
#include "Nodo.h"

int main(){
    ListaDobleLigada* lista = new ListaDobleLigada();

    lista->push_top(new Nodo(10));
    lista->push_top(new Nodo(203));
    lista->push_top(new Nodo(345));
    lista->push_top(new Nodo(4545));

}