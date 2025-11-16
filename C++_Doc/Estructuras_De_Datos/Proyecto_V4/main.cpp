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
    cout << "7) Agregar sucursal" << endl;
    cout << "8) Ver info sucursal" << endl;
    cout << "9) Testeo - imprimir el grafo " << endl;
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
            case 7: {
                limpiar_pantalla();
                cout << "\n--- AGREGAR SUCURSAL ---\n" << endl;
                
                string nombre, direccion, telefono, horario;
                
                cout << "Nombre de la sucursal: ";
                getline(cin, nombre);
                
                cout << "Direccion: ";
                getline(cin, direccion);
                
                cout << "Telefono: ";
                getline(cin, telefono);
                
                cout << "Horario (ej: 08:00-20:00): ";
                getline(cin, horario);
                
                if (nombre.empty() || direccion.empty() || telefono.empty() || horario.empty()) {
                    cout << "\nError: Todos los campos son obligatorios." << endl;
                } else {
                    Sucursal* nueva_sucursal = new Sucursal(nombre, direccion, telefono, horario);
                    grafo->insertar_vertice_sucursal(nombre, nueva_sucursal);
                    cout << "\nSucursal '" << nombre << "' agregada correctamente." << endl;
                }
                
                pausa();
                break;
            }

            case 8: {
                limpiar_pantalla();
                cout << "\n--- VER INFORMACION DE SUCURSAL ---\n" << endl;
                
                grafo->imprimir_vertices();
                
                string nombre;
                cout << "Nombre de la sucursal: ";
                getline(cin, nombre);
                
                if (!nombre.empty()) {
                    grafo->imprimir_info_sucursal(nombre);
                }
                
                pausa();
                break;
            }

            case 9: {
                limpiar_pantalla();
                cout << "\n--- DATOS DE PRUEBA - PAQUETERIA ---\n" << endl;
                
                Sucursal* s1 = new Sucursal("CENTRO", "Calle Principal 100", "555-0001", "08:00-20:00");
                Sucursal* s2 = new Sucursal("NORTE", "Avenida Norte 250", "555-0002", "08:00-20:00");
                Sucursal* s3 = new Sucursal("SUR", "Calle Sur 150", "555-0003", "08:00-20:00");
                Sucursal* s4 = new Sucursal("ESTE", "Carrera Este 300", "555-0004", "08:00-20:00");
                Sucursal* s5 = new Sucursal("OESTE", "Avenida Oeste 200", "555-0005", "08:00-20:00");
                Sucursal* s6 = new Sucursal("AEROPUERTO", "Ruta Aeropuerto KM 5", "555-0006", "06:00-22:00");
                Sucursal* s7 = new Sucursal("PUERTO", "Paseo Puerto 500", "555-0007", "07:00-19:00");
                Sucursal* s8 = new Sucursal("ZONA_INDUSTRIAL", "Poligono Industrial 10", "555-0008", "08:00-18:00");
                
                grafo->insertar_vertice_sucursal("CENTRO", s1);
                grafo->insertar_vertice_sucursal("NORTE", s2);
                grafo->insertar_vertice_sucursal("SUR", s3);
                grafo->insertar_vertice_sucursal("ESTE", s4);
                grafo->insertar_vertice_sucursal("OESTE", s5);
                grafo->insertar_vertice_sucursal("AEROPUERTO", s6);
                grafo->insertar_vertice_sucursal("PUERTO", s7);
                grafo->insertar_vertice_sucursal("ZONA_INDUSTRIAL", s8);
                
                grafo->insertar_arista("CENTRO", "NORTE", 12);
                grafo->insertar_arista("CENTRO", "SUR", 15);
                grafo->insertar_arista("CENTRO", "ESTE", 18);
                grafo->insertar_arista("CENTRO", "OESTE", 14);
                
                grafo->insertar_arista("NORTE", "AEROPUERTO", 25);
                grafo->insertar_arista("NORTE", "ZONA_INDUSTRIAL", 22);
                grafo->insertar_arista("NORTE", "ESTE", 20);
                
                grafo->insertar_arista("SUR", "PUERTO", 30);
                grafo->insertar_arista("SUR", "OESTE", 16);
                grafo->insertar_arista("SUR", "ZONA_INDUSTRIAL", 28);
                
                grafo->insertar_arista("ESTE", "AEROPUERTO", 28);
                grafo->insertar_arista("ESTE", "ZONA_INDUSTRIAL", 24);
                grafo->insertar_arista("ESTE", "PUERTO", 35);
                
                grafo->insertar_arista("OESTE", "PUERTO", 32);
                grafo->insertar_arista("OESTE", "ZONA_INDUSTRIAL", 26);
                grafo->insertar_arista("OESTE", "AEROPUERTO", 29);
                
                grafo->insertar_arista("AEROPUERTO", "ZONA_INDUSTRIAL", 30);
                grafo->insertar_arista("AEROPUERTO", "PUERTO", 45);
                
                grafo->insertar_arista("PUERTO", "ZONA_INDUSTRIAL", 40);
                
                cout << "Datos de prueba cargados.\n" << endl;
                grafo->imprimir_grafo();
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