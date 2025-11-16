#include "Grafo.h"
#include "Prim.h"
#include <iostream>
#include <string>

using namespace std;

void limpiar_pantalla() {
    system("clear");
}

void imprimir_menu() {
    limpiar_pantalla();
    cout << "\n========================================" << endl;
    cout << "         GESTOR DE GRAFOS" << endl;
    cout << "========================================" << endl;
    cout << "\n1) Insertar vertice" << endl;
    cout << "2) Insertar arista" << endl;
    cout << "3) Eliminar vertice" << endl;
    cout << "4) Eliminar arista" << endl;
    cout << "5) Imprimir grafo" << endl;
    cout << "6) Arbol minimo (PRIM)" << endl;
    cout << "7) Testeo - imprimir el grafo " << endl;
    cout << "0) Salir" << endl;
    cout << "\nSelecciona una opcion: ";
}

void pausa() {
    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void Testeo(){
    Grafo* grafo = new Grafo();

    grafo->insertar_vertice("A");
    grafo->insertar_vertice("B");
    grafo->insertar_vertice("C");
    grafo->insertar_vertice("D");
    
    grafo->insertar_arista("A", "B", 10);
    grafo->insertar_arista("A", "C", 1);
    grafo->insertar_arista("B", "C", 2);
    grafo->insertar_arista("C", "D", 3);


    grafo->imprimir_grafo();
}

void Testeo_Prim(){
    Grafo* grafo = new Grafo();

    grafo->insertar_vertice("A");
    grafo->insertar_vertice("B");
    grafo->insertar_vertice("C");
    grafo->insertar_vertice("D");
    grafo->insertar_vertice("E");
    grafo->insertar_vertice("F");
    grafo->insertar_vertice("G");

    grafo->insertar_arista("A", "B", 10);
    grafo->insertar_arista("A", "C", 1);
    grafo->insertar_arista("B", "C", 2);
    grafo->insertar_arista("C", "D", 3);
    grafo->insertar_arista("B", "D", 5);
    grafo->insertar_arista("D", "E", 4);
    grafo->insertar_arista("C", "E", 8);
    grafo->insertar_arista("E", "F", 6);
    grafo->insertar_arista("F", "G", 7);
    grafo->insertar_arista("A", "G", 9);

    Prim* prim = new Prim();
    prim->calcular(grafo, "A");
    
    
    grafo->imprimir_grafo();
    cout << "--------------- PRIM ---------------" << endl;
    prim->imprimir_arbol();
}

int main() {
    Grafo* grafo = new Grafo();
    int opcion_usr = -1;
    
    while (opcion_usr != 0) {
        imprimir_menu();
        cin >> opcion_usr;
        cin.ignore();
        
        switch (opcion_usr) {
            
            case 1: {
                limpiar_pantalla();
                cout << "\n--- INSERTAR VERTICE ---\n" << endl;
                
                string nombre_vertice;
                cout << "Ingresa el nombre del vertice: ";
                getline(cin, nombre_vertice);
                
                if (nombre_vertice.empty()) {
                    cout << "\nError: El nombre no puede estar vacio." << endl;
                } else if (grafo->existe_vertice(nombre_vertice)) {
                    cout << "\nError: El vertice '" << nombre_vertice << "' ya existe." << endl;
                } else {
                    grafo->insertar_vertice(nombre_vertice);
                    cout << "\nVertice '" << nombre_vertice << "' insertado correctamente." << endl;
                }
                
                pausa();
                break;
            }
            
            case 2: {
                limpiar_pantalla();
                cout << "\n--- INSERTAR ARISTA ---\n" << endl;
                
                string origen, destino;
                int peso;
                
                cout << "Ingresa vertice origen: ";
                getline(cin, origen);
                
                cout << "Ingresa vertice destino: ";
                getline(cin, destino);
                
                cout << "Ingresa el peso de la arista: ";
                cin >> peso;
                
                if (origen.empty() || destino.empty()) {
                    cout << "\nError: Los nombres no pueden estar vacios." << endl;
                } else if (peso <= 0) {
                    cout << "\nError: El peso debe ser mayor a 0." << endl;
                } else if (!grafo->existe_vertice(origen)) {
                    cout << "\nError: El vertice origen '" << origen << "' no existe." << endl;
                } else if (!grafo->existe_vertice(destino)) {
                    cout << "\nError: El vertice destino '" << destino << "' no existe." << endl;
                } else if (grafo->existe_arista(origen, destino)) {
                    cout << "\nError: La arista '" << origen << "' -> '" << destino << "' ya existe." << endl;
                } else {
                    grafo->insertar_arista(origen, destino, peso);
                    cout << "\nArista '" << origen << "' -> '" << destino << "' (peso: " << peso << ") insertada correctamente." << endl;
                }
                
                pausa();
                break;
            }
            
            case 3: {
                limpiar_pantalla();
                cout << "\n--- ELIMINAR VERTICE ---\n" << endl;
                
                grafo->imprimir_vertices();
                
                string nombre_vertice;
                cout << "Ingresa el nombre del vertice a eliminar: ";
                getline(cin, nombre_vertice);
                
                if (nombre_vertice.empty()) {
                    cout << "\nError: El nombre no puede estar vacio." << endl;
                } else if (!grafo->existe_vertice(nombre_vertice)) {
                    cout << "\nError: El vertice '" << nombre_vertice << "' no existe." << endl;
                } else {
                    grafo->eliminar_vertice(nombre_vertice);
                    cout << "\nVertice '" << nombre_vertice << "' eliminado correctamente." << endl;
                }
                
                pausa();
                break;
            }
            
            case 4: {
                limpiar_pantalla();
                cout << "\n--- ELIMINAR ARISTA ---\n" << endl;
                
                grafo->imprimir_grafo();
                
                string origen, destino;
                cout << "Ingresa vertice origen: ";
                getline(cin, origen);
                
                cout << "Ingresa vertice destino: ";
                getline(cin, destino);
                
                if (origen.empty() || destino.empty()) {
                    cout << "\nError: Los nombres no pueden estar vacios." << endl;
                } else if (!grafo->existe_arista(origen, destino)) {
                    cout << "\nError: La arista '" << origen << "' -> '" << destino << "' no existe." << endl;
                } else {
                    grafo->eliminar_arista(origen, destino);
                    cout << "\nArista '" << origen << "' -> '" << destino << "' eliminada correctamente." << endl;
                }
                
                pausa();
                break;
            }
            
            case 5: {
                limpiar_pantalla();
                cout << "\n--- INFORMACION DEL GRAFO ---\n" << endl;
                
                if (grafo->cantidad_vertices_total() == 0) {
                    cout << "El grafo esta vacio. Agrega vertices primero." << endl;
                } else {
                    grafo->imprimir_grafo();
                }
                
                pausa();
                break;
            }
            
            case 6: {
                limpiar_pantalla();
                cout << "\n--- ARBOL RECUBRIDOR MINIMO (PRIM) ---\n" << endl;
                
                if (grafo->cantidad_vertices_total() == 0) {
                    cout << "Error: El grafo esta vacio." << endl;
                } else if (grafo->cantidad_vertices_total() == 1) {
                    cout << "Error: Se necesitan al menos 2 vertices." << endl;
                } else {
                    grafo->imprimir_vertices();
                    
                    string origen;
                    cout << "Ingresa el vertice de inicio para Prim: ";
                    getline(cin, origen);
                    
                    if (origen.empty()) {
                        cout << "\nError: El nombre no puede estar vacio." << endl;
                    } else if (!grafo->existe_vertice(origen)) {
                        cout << "\nError: El vertice '" << origen << "' no existe." << endl;
                    } else {
                        Prim* prim = new Prim();
                        prim->calcular(grafo, origen);
                        prim->imprimir_arbol();
                    }
                }
                
                pausa();
                break;
            }
            case 7:{
                Testeo();
                pausa();
                break;
            }
            case 8:{
                Testeo_Prim();
                pausa();
                break;
            }
            case 0: {
                limpiar_pantalla();
                cout << "\nHasta luego." << endl;
                cout << "\n" << endl;
                break;
            }
            
            
            default: {
                limpiar_pantalla();
                cout << "\nOpcion no valida. Selecciona una opcion valida (0-6)." << endl;
                pausa();
                break;
            }
        }
    }
    
    return 0;
}