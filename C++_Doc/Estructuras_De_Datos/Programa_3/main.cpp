//
// Created by Jesus Emmanuel Garcia on 9/17/25.
//

#include <iostream>
#include "Lista.h"
#include "Nodo.h"

using namespace std;

int main(){
    ListaDobleLigada* lista = new ListaDobleLigada();

    lista->push_bottom(new Nodo(10));
    lista->push_bottom(new Nodo(203));
    lista->push_bottom(new Nodo(345));
    lista->push_bottom(new Nodo(4545));


    lista->print_tail_to_head();

    lista->push_top(new Nodo(4));
    lista->push_top(new Nodo(0234));

    lista->push_bottom(new Nodo(1909));

    cout << "" << endl;

    lista->print_head_to_tail();

    cout << "" << endl;
    lista->print();
}