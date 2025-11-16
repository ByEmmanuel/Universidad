//
// Created by Jesus Emmanuel Garcia on 11/15/25.
//

#include "Grafo.h"
#include <iostream>

using namespace std;

Grafo::Grafo() : vertices(nullptr), cantidad_vertices(0) {}

Grafo::~Grafo() {
    NodoVertice* actual = vertices;
    while (actual != nullptr) {
        NodoVertice* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

NodoVertice* Grafo::buscar_nodo_vertice(std::string nombre) {
    NodoVertice* actual = vertices;
    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void Grafo::insertar_vertice(std::string nombre) {
    if (existe_vertice(nombre)) {
        cout << "El vértice " << nombre << " ya existe." << endl;
        return;
    }

    NodoVertice* nuevo = new NodoVertice(nombre);

    if (vertices == nullptr) {
        vertices = nuevo;
    } else {
        NodoVertice* actual = vertices;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    cantidad_vertices++;
}

void Grafo::eliminar_vertice(std::string nombre) {
    if (vertices == nullptr) return;

    // Eliminar aristas que apunten a este vértice
    NodoVertice* actual = vertices;
    while (actual != nullptr) {
        actual->aristas->eliminar(nombre);
        actual = actual->siguiente;
    }

    // Eliminar el vértice
    if (vertices->nombre == nombre) {
        NodoVertice* temp = vertices;
        vertices = vertices->siguiente;
        delete temp;
        cantidad_vertices--;
        return;
    }

    actual = vertices;
    while (actual->siguiente != nullptr) {
        if (actual->siguiente->nombre == nombre) {
            NodoVertice* temp = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            delete temp;
            cantidad_vertices--;
            return;
        }
        actual = actual->siguiente;
    }
}

void Grafo::insertar_arista(std::string origen, std::string destino, int peso) {
    NodoVertice* nodo_origen = buscar_nodo_vertice(origen);
    NodoVertice* nodo_destino = buscar_nodo_vertice(destino);

    if (nodo_origen == nullptr || nodo_destino == nullptr) {
        cout << "Uno o ambos vértices no existen." << endl;
        return;
    }

    if (nodo_origen->aristas->buscar(destino) != nullptr) {
        cout << "La arista ya existe." << endl;
        return;
    }

    nodo_origen->aristas->insertar(destino, peso);
}

void Grafo::eliminar_arista(std::string origen, std::string destino) {
    NodoVertice* nodo_origen = buscar_nodo_vertice(origen);

    if (nodo_origen == nullptr) {
        cout << "El vértice origen no existe." << endl;
        return;
    }

    nodo_origen->aristas->eliminar(destino);
}

int Grafo::obtener_peso_arista(std::string origen, std::string destino) {
    NodoVertice* nodo_origen = buscar_nodo_vertice(origen);

    if (nodo_origen == nullptr) return -1;

    NodoArista* arista = nodo_origen->aristas->buscar(destino);
    if (arista != nullptr) {
        return arista->peso;
    }
    return -1;
}

bool Grafo::existe_vertice(std::string nombre) {
    return buscar_nodo_vertice(nombre) != nullptr;
}

bool Grafo::existe_arista(std::string origen, std::string destino) {
    NodoVertice* nodo = buscar_nodo_vertice(origen);
    if (nodo == nullptr) return false;
    return nodo->aristas->buscar(destino) != nullptr;
}

int Grafo::cantidad_vertices_total() {
    return cantidad_vertices;
}

int Grafo::obtener_grado_salida(std::string vertice) {
    NodoVertice* nodo = buscar_nodo_vertice(vertice);
    if (nodo == nullptr) return -1;
    return nodo->aristas->tamaño();
}

int Grafo::obtener_grado_entrada(std::string vertice) {
    int grado = 0;
    NodoVertice* actual = vertices;

    while (actual != nullptr) {
        if (actual->nombre != vertice && actual->aristas->buscar(vertice) != nullptr) {
            grado++;
        }
        actual = actual->siguiente;
    }
    return grado;
}

void Grafo::imprimir_grafo() {
    cout << "\n========== GRAFO ==========" << endl;
    NodoVertice* actual = vertices;

    while (actual != nullptr) {
        cout << "Vértice: " << actual->nombre;
        cout << " | Grado entrada: " << obtener_grado_entrada(actual->nombre);
        cout << " | Grado salida: " << obtener_grado_salida(actual->nombre) << endl;

        cout << "  Aristas: ";
        if (actual->aristas->esta_vacia()) {
            cout << "ninguna";
        } else {
            actual->aristas->imprimir();
        }

        actual = actual->siguiente;
    }
    cout << "=========================\n" << endl;
}

void Grafo::imprimir_vertices() {
    cout << "\nVértices del grafo:" << endl;
    NodoVertice* actual = vertices;
    int contador = 1;

    while (actual != nullptr) {
        cout << contador << ". " << actual->nombre << endl;
        actual = actual->siguiente;
        contador++;
    }
    cout << endl;
}

void Grafo::imprimir_aristas(std::string vertice) {
    NodoVertice* nodo = buscar_nodo_vertice(vertice);

    if (nodo == nullptr) {
        cout << "El vértice no existe." << endl;
        return;
    }

    cout << "\nAristas del vértice " << vertice << ":" << endl;
    if (nodo->aristas->esta_vacia()) {
        cout << "  No hay aristas." << endl;
    } else {
        nodo->aristas->imprimir();
    }
    cout << endl;
}
