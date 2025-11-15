//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//


#include "Lista.h"
#include <vector>
#include <iostream>

#include "Grafo.h"

using namespace std;
int main(){

    Lista<int>* lista = new Lista<int>();

    lista->insert(10);
    lista->insert(23);
    lista->insert(345);
    cout << "Tamaño: " << lista->size() << endl;
    lista->insert(5);
    lista->insert(34534534);
    lista->insert(20);

    lista->insert_at(0,24);
    lista->insert_at(0,23);
    lista->insert_at(0,2);
    lista->insert_at(lista->size()+1,2);
    lista->insert_at(lista->size()+1,3);
    lista->insert_at(lista->size()+1,4);

    lista->insert_at(4,4);

    lista->print_all();
    cout << "Tamaño: " << lista->size() << endl;

    std::vector<int>* list = new std::vector<int>;
    list->push_back(10);
    list->push_back(23);
    list->push_back(34);
    list->push_back(324);



    /*for (int i = 0; i < list->size(); i++){
        cout << list->at(i) << endl;
    }*/

    // Grafo

    Grafo<int>* grafo = new Grafo<int>();
    grafo->insert("A", 10);
    grafo->insert("A", 23);


}