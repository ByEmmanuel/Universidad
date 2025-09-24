//
// Created by Jesus Emmanuel Garcia on 9/19/25.
//

#include "Lista.h"
#include "Nodo.h"
#include "Alumno.h"
#include <iostream>
#include <string>
#include "MergeSort.h"

using namespace std;


int main(){
    ListaDobleLigada* lista = new ListaDobleLigada();

    lista->push_top(10);
    lista->push_top(23);
    lista->push_top(5);
    lista->push_top(42);
    lista->push_top(17);
    lista->push_top(8);
    lista->push_top(31);
    lista->push_top(4);
    lista->push_top(29);
    lista->push_top(11);

    lista->push_top(19);
    lista->push_top(37);
    lista->push_top(6);
    lista->push_top(28);
    lista->push_top(14);
    lista->push_top(2);
    lista->push_top(33);
    lista->push_top(9);
    lista->push_top(21);
    lista->push_top(1);

    std:: cout << "Lista sin ordenar " << endl;

    lista->print_head_to_tail();

    lista = MergeSort(lista);

    std:: cout << "Lista ordenada " << endl;

    lista->print_head_to_tail();

  return 0;
}