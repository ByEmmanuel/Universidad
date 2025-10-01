//
// Created by Jesus Emmanuel Garcia on 9/19/25.
//

#include "Lista.h"
#include "Nodo.h"
#include "Alumno.h"
#include <iostream>
#include <string>

using namespace std;

int main(){


    int opc_usr = 0;

    cout << "Ingrese opcion" << endl;
    // menu iterativo
    ListaDobleLigada* lista = new ListaDobleLigada();

    lista->push_bottom(90);
    lista->push_bottom(100);
    lista->push_bottom(4);
    lista->push_bottom(8);
    lista->push_bottom(17);
    lista->push_bottom(33);
    lista->push_bottom(50);
    lista->push_bottom(0);
    lista->push_bottom(1);

    lista->print();



}