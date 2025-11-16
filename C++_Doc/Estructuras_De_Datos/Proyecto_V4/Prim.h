#ifndef PRIM_H
#define PRIM_H

#include "Grafo.h"
#include <string>

class Prim {
private:
    struct Arista {
        std::string origen;
        std::string destino;
        int peso;
    };
    
    Arista* aristas_mst;
    int cantidad_aristas_mst;
    int peso_total_mst;
    bool* visitado;
    int cantidad_vertices;
    
    void liberar_memoria();

public:
    Prim();
    ~Prim();
    
    void calcular(Grafo* grafo, std::string origen);
    void imprimir_arbol();
    int obtener_peso_total();
};

#endif // PRIM_H