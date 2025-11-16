//
// Created by Jesus Emmanuel Garcia on 8/27/25.
//

#include "Grafo.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Grafo* grafo = new Grafo();
    grafo->insertar_vertice("A");
    grafo->insertar_vertice("B");
    grafo->insertar_vertice("C");
    grafo->insertar_vertice("D");
    grafo->insertar_vertice("E");


    /*grafo->insertar_arista("A", "B", 10);
    grafo->insertar_arista("A", "B", 10);
    grafo->insertar_arista("A", "B", 10);*/



    grafo->print_vertices();
}