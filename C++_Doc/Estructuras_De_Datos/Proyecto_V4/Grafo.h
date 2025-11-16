#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include "NodoVertice.h"

using namespace std;

class Grafo{
private:
    // recordando que cada vertice tiene una lista interna
    NodoVertice* vertice_h;
    int cantidad_vertices;

    NodoVertice* buscar_nodo_vertice(string nombre);
    
public:
    Grafo();
    ~Grafo();

    void insertar_vertice(string nombre_ver);
    void eliminar_vertice(string nombre);
    
    void insertar_arista(string origen, string destino,int  peso);
    void eliminar_arista(string origen, string destino);
    
    int obtener_peso_arista(string origen,string destino);

    bool existe_vertice(string nombre);
    bool existe_arista(string origen, string destino);

    int cantidad_vertices_total();
    int obtener_grado_salida(string vertice);
    int obtener_grado_entrada(string vertice);

    void imprimir_grafo();
    void imprimir_vertices();
    void imprimir_aristas(string vertice);

    NodoVertice* get_vertices();

    void insertar_vertice_sucursal(std::string nombre, Sucursal* sucursal);
    Sucursal* obtener_sucursal(std::string nombre);
    void imprimir_info_sucursal(std::string nombre);

};

#endif GRAFO_H