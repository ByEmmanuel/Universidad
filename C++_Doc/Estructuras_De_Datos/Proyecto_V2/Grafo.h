//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#ifndef GRAFO_H
#define GRAFO_H

#include <string>

#include "Lista.h"
#include "Lista_vertices.h"
using namespace std;

class Grafo {

public:
    Lista_vertices* list_adj;
    Grafo();
    ~Grafo();

    void insertar_vertice(const std::string& vertice);
    void insertar_arista(string origen, string destino, int peso);
    void print_vertices();


};

#endif //GRAFO_H
