//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#ifndef GRAFO_H
#define GRAFO_H

#include "NodoVertice.h"
#include <string>

class Grafo {
private:
    NodoVertice* vertices;
    int cantidad_vertices;

    NodoVertice* buscar_nodo_vertice(std::string nombre);

public:
    Grafo();
    ~Grafo();

    void insertar_vertice(std::string nombre);
    void eliminar_vertice(std::string nombre);
    void insertar_arista(std::string origen, std::string destino, int peso);
    void eliminar_arista(std::string origen, std::string destino);

    int obtener_peso_arista(std::string origen, std::string destino);
    bool existe_vertice(std::string nombre);
    bool existe_arista(std::string origen, std::string destino);

    int cantidad_vertices_total();
    int obtener_grado_salida(std::string vertice);
    int obtener_grado_entrada(std::string vertice);

    void imprimir_grafo();
    void imprimir_vertices();
    void imprimir_aristas(std::string vertice);
};

#endif // GRAFO_H