#include <iostream>
#include <string>
#include "Grafo.h"

using namespace std;

Grafo::Grafo(){
    this->cantidad_vertices = 0;
    this->vertice_h = nullptr;
}

NodoVertice* Grafo::buscar_nodo_vertice(string nombre_ver){
    // buscar de toda la vida
    NodoVertice* tmp = vertice_h;
    while (tmp){
        if (tmp->nombre == nombre_ver){
            return tmp;
        }
        tmp = tmp->sig;
    }
    return nullptr;
};

void Grafo::insertar_vertice(string nombre_ver){
    if(existe_vertice(nombre_ver)){
        cout << "El vertice " << nombre_ver << " Ya existe " << endl;
        return;
    }

    NodoVertice* nuevo = new NodoVertice(nombre_ver);

    if (vertice_h == nullptr){
        this->vertice_h = nuevo;
        return;
    }else{
        NodoVertice* act = vertice_h;
        // act->sig != nullptr 
        while (act->sig){
            act = act->sig;
        }
        act->sig = nuevo;
    }
    cantidad_vertices++;
};


// primero tengo que eliminar las listas de vertices que tiene cada NodoArista
void Grafo::eliminar_vertice(string nombre){
    // tengo 2 opciones, hacerlo recursivo o con un while
    // pero las razones de ser de los grafos y arboles es su recursividad zzzz

    // no existe lista de Aristas
    if (vertice_h == nullptr)return;

    // elimina las aristas de cada vertice que contengan esa arista
    NodoVertice* act = vertice_h;
    while (act){
        act->aristas->eliminar(nombre);
        act = act->sig;
    }

    // eliminar vertice 
    // eliminacion de toda la vida
    
    act = vertice_h;
    while (act->sig){
        // a borrar el siguiente del actual
        if(act->sig->nombre == nombre){
            NodoVertice* a_borrar = act->sig;
            act->sig = act->sig->sig;
            delete a_borrar;
            cantidad_vertices--;
            return;
        }
        act = act->sig;
    }    
};

void Grafo::insertar_arista(string origen, string destino,int peso){
    // verificar si existe origen y destino ( vertices )
    NodoVertice* nodo_origen = buscar_nodo_vertice(origen);
    NodoVertice* nodo_destino = buscar_nodo_vertice(destino);

    if (nodo_origen == nullptr || nodo_destino == nullptr) {
        cout << "Uno o ambos vértices no existen." << endl;
        return;
    }

    if (nodo_origen->aristas->buscar_por_destino(destino) != nullptr) {
        cout << "La arista ya existe." << endl;
        return;
    }
    /**
     * nodo_origen
     * |
     * |
     * |----en su parte lista de aristas -> insertar ( destino )----
     */
    nodo_origen->aristas->insertar(destino,peso);
};

void Grafo::eliminar_arista(string origen, string destino){
    NodoVertice* nodo_origen = buscar_nodo_vertice(origen);

    if (nodo_origen){
        nodo_origen->aristas->eliminar(destino);
    }else{
        cout << "El nodo de origen no existe, intenta otro :p " << endl;
    }

};

int Grafo::obtener_peso_arista(string origen,string destino){
    // pueden existir los vertices pero no estar conectados
    NodoVertice* nodo_origen = buscar_nodo_vertice(origen);
    NodoVertice* nodo_destino = buscar_nodo_vertice(destino);

    // existen los 2
    if (nodo_origen && nodo_destino){
        // ver si estan conectados, solo basta con buscar uno para que el otro este conectado
        NodoArista* tmp = nodo_origen->aristas->buscar_por_destino(destino);
        // si estan conectados
        if (tmp)return tmp->peso;
    }
    return -1;
    
};


// funciones modulares
bool Grafo::existe_vertice(string nombre){
    return buscar_nodo_vertice(nombre) != nullptr;
};

// entre 2 vertices
bool Grafo::existe_arista(string origen, string destino){
    NodoVertice* tmp = buscar_nodo_vertice(origen);

    if(tmp == nullptr)return false;
    // existe arista
    return tmp->aristas->buscar_por_destino(destino) != nullptr;
}

int Grafo::cantidad_vertices_total(){
    return this->cantidad_vertices;
};


// el grado de salida es, apartir del vertice, contar todos las aristas que apunto como vertice
int Grafo::obtener_grado_salida(string vertice){
    NodoVertice* tmp = buscar_nodo_vertice(vertice);

    if (tmp)return tmp->aristas->size() - 1;
    return -1;
};

int Grafo::obtener_grado_entrada(string vertice_nombre){
    NodoVertice* tmp = this->vertice_h;

    int grado = 0;
    while (tmp){
        if(tmp->nombre != vertice_nombre && tmp->aristas->buscar_por_destino(vertice_nombre) ){
            grado++;
        }
        tmp = tmp->sig;
    }
    return grado;
};

void Grafo::imprimir_grafo(){

    // imprimir 

    NodoVertice* tmp = vertice_h;

    while (tmp){
        cout << "Vertice: " << tmp->nombre << endl;

        cout << endl;

        tmp->aristas->imprimir();

        cout << endl;

        tmp = tmp->sig;
    }

};

void Grafo::imprimir_vertices() {
    cout << "\nVértices del grafo:" << endl;
    NodoVertice* actual = vertice_h;
    int contador = 1;

    while (actual != nullptr) {
        cout << contador << ". " << actual->nombre << endl;
        actual = actual->sig;
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
    if (nodo->aristas->is_empty()) {
        cout << "  No hay aristas." << endl;
    } else {
        nodo->aristas->imprimir();
    }
    cout << endl;
}


