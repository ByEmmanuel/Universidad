//
// Created by Jesus Emmanuel Garcia on 8/27/25.
//

#include "Lista.h"
#include "Nodo.h"
#include <iostream>

int main(){

    Lista* lista = new Lista();
    lista->push_up(new Nodo(20));
    lista->push_up(new Nodo(44));
    lista->push_up(new Nodo(55));
    lista->push_up(new Nodo(78));

    lista->push_up(new Nodo(90));

    lista->push_bottom(new Nodo(10));

    lista->push_up(new Nodo(100));

    /*  salida esperada
     *  100
     *  90
     *  78
     *  55
     *  44
     *  20
     *  10
     */

    lista->print_elements();
    lista->print_first_element();
    lista->print_last_element();
    lista->print_aux();
    lista->print_aux_next();


}