//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//


#include "Grafo.h"
#include <iostream>

using namespace std;

int main() {
    Grafo grafo;

    // Insertar vértices
    cout << "=== Insertando vértices ===" << endl;
    grafo.insertar_vertice("A");
    grafo.insertar_vertice("B");
    grafo.insertar_vertice("C");
    grafo.insertar_vertice("D");
    grafo.insertar_vertice("E");

    // Insertar aristas
    cout << "=== Insertando aristas ===" << endl;
    grafo.insertar_arista("A", "B", 10);
    grafo.insertar_arista("A", "C", 5);
    grafo.insertar_arista("B", "D", 15);
    grafo.insertar_arista("C", "D", 7);
    grafo.insertar_arista("D", "E", 3);
    grafo.insertar_arista("B", "E", 20);

    // Imprimir grafo
    grafo.imprimir_grafo();

    // Imprimir vértices
    grafo.imprimir_vertices();

    // Imprimir aristas específicas
    grafo.imprimir_aristas("A");
    grafo.imprimir_aristas("B");

    // Consultas
    cout << "=== Consultas ===" << endl;
    cout << "Total de vértices: " << grafo.cantidad_vertices_total() << endl;
    cout << "¿Existe arista A->B? " << (grafo.existe_arista("A", "B") ? "Sí" : "No") << endl;
    cout << "Peso de arista A->B: " << grafo.obtener_peso_arista("A", "B") << endl;
    cout << "Grado salida de A: " << grafo.obtener_grado_salida("A") << endl;
    cout << "Grado entrada de D: " << grafo.obtener_grado_entrada("D") << endl;

    // Eliminar arista
    cout << "\n=== Eliminando arista A->C ===" << endl;
    grafo.eliminar_arista("A", "C");
    grafo.imprimir_grafo();

    // Eliminar vértice
    cout << "\n=== Eliminando vértice E ===" << endl;
    grafo.eliminar_vertice("E");
    grafo.imprimir_grafo();

    return 0;
}