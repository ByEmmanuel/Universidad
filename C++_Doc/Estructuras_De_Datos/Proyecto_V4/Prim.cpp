#include "Prim.h"
#include <iostream>
#include <climits>

using namespace std;

Prim::Prim() : aristas_mst(nullptr), cantidad_aristas_mst(0), peso_total_mst(0), visitado(nullptr), cantidad_vertices(0) {}

Prim::~Prim() {
    liberar_memoria();
}

void Prim::liberar_memoria() {
    if (aristas_mst != nullptr) {
        delete[] aristas_mst;
        aristas_mst = nullptr;
    }
    if (visitado != nullptr) {
        delete[] visitado;
        visitado = nullptr;
    }
}

void Prim::calcular(Grafo* grafo, string origen) {
    liberar_memoria();
    
    cantidad_vertices = grafo->cantidad_vertices_total();
    peso_total_mst = 0;
    cantidad_aristas_mst = 0;
    
    if (cantidad_vertices == 0) {
        cout << "El grafo esta vacio." << endl;
        return;
    }
    
    if (cantidad_vertices == 1) {
        cout << "Se necesitan al menos 2 vertices." << endl;
        return;
    }
    
    // Inicializar arrays
    visitado = new bool[cantidad_vertices];
    aristas_mst = new Arista[cantidad_vertices - 1];
    
    for (int i = 0; i < cantidad_vertices; i++) {
        visitado[i] = false;
    }
    
    // Obtener array de vertices
    NodoVertice** vertices_array = new NodoVertice*[cantidad_vertices];
    int contador = 0;
    NodoVertice* actual = grafo->get_vertices();
    
    while (actual != nullptr && contador < cantidad_vertices) {
        vertices_array[contador] = actual;
        contador++;
        actual = actual->sig;
    }
    
    // Buscar indice del vertice origen
    int indice_origen = -1;
    for (int i = 0; i < cantidad_vertices; i++) {
        if (vertices_array[i]->nombre == origen) {
            indice_origen = i;
            break;
        }
    }
    
    if (indice_origen == -1) {
        cout << "Vertice origen no encontrado." << endl;
        delete[] vertices_array;
        return;
    }
    
    // Marcar origen como visitado
    visitado[indice_origen] = true;
    
    // Algoritmo de Prim
    for (int i = 1; i < cantidad_vertices; i++) {
        int peso_minimo = INT_MAX;
        int indice_origen_minimo = -1;
        int indice_destino_minimo = -1;
        
        // Buscar arista minima que conecte visitado con no visitado
        for (int v = 0; v < cantidad_vertices; v++) {
            if (visitado[v]) {
                NodoArista* arista = vertices_array[v]->aristas->get_head();
                
                while (arista != nullptr) {
                    // Buscar indice del destino
                    int indice_dest = -1;
                    for (int j = 0; j < cantidad_vertices; j++) {
                        if (vertices_array[j]->nombre == arista->destino) {
                            indice_dest = j;
                            break;
                        }
                    }
                    
                    // Si no visitado y peso es menor
                    if (indice_dest != -1 && !visitado[indice_dest] && arista->peso < peso_minimo) {
                        peso_minimo = arista->peso;
                        indice_origen_minimo = v;
                        indice_destino_minimo = indice_dest;
                    }
                    
                    arista = arista->sig;
                }
            }
        }
        
        // Si encontro una arista
        if (indice_destino_minimo != -1) {
            visitado[indice_destino_minimo] = true;
            aristas_mst[cantidad_aristas_mst].origen = vertices_array[indice_origen_minimo]->nombre;
            aristas_mst[cantidad_aristas_mst].destino = vertices_array[indice_destino_minimo]->nombre;
            aristas_mst[cantidad_aristas_mst].peso = peso_minimo;
            cantidad_aristas_mst++;
            peso_total_mst += peso_minimo;
        }
    }
    
    delete[] vertices_array;
}

void Prim::imprimir_arbol() {
    cout << "\n--- ARBOL RECUBRIDOR MINIMO (PRIM) ---\n" << endl;
    cout << "Aristas del MST:" << endl;
    
    for (int i = 0; i < cantidad_aristas_mst; i++) {
        cout << aristas_mst[i].origen << " -- " << aristas_mst[i].destino 
             << " (peso: " << aristas_mst[i].peso << ")" << endl;
    }
    
    cout << "\nPeso total del MST: " << peso_total_mst << endl;
    cout << "Cantidad de aristas: " << cantidad_aristas_mst << endl;
    cout << "\n" << endl;
}

int Prim::obtener_peso_total() {
    return peso_total_mst;
}