//
// Created by Jesus Emmanuel Garcia on 9/19/25.
//

#include "Lista.h"
#include "Nodo.h"
#include "Alumno.h"
#include <iostream>
#include <string>

using namespace std;

inline Alumno* crearAlumno() {
    string nombre, apellido, matricula;
    int edad;
    float promedio;

    cout << "Ingrese nombre: ";
    cin >> nombre;
    cout << "Ingrese apellido: ";
    cin >> apellido;
    cout << "Ingrese edad: ";
    cin >> edad;
    cout << "Ingrese matricula: ";
    cin >> matricula;
    cout << "Ingrese promedio: ";
    cin >> promedio;

    return new Alumno(nombre, apellido, edad, matricula, promedio);
}

int main() {
    ListaDobleLigada* lista = new ListaDobleLigada();
    int opc_usr;

    while (true) {
        cout << "\nIngrese una opcion: \n";
        string opciones[14] = {
            "1. Inicializar (con algunos alumnos de prueba)",
            "2. Insertar al inicio",
            "3. Insertar al final",
            "4. Insertar en posicion",
            "5. Buscar",
            "6. Eliminar",
            "7. Eliminar todo",
            "8. Vacia",
            "9. Mostrar de head -> tail",
            "10. Primero",
            "11. Ultimo",
            "12. Anterior",
            "13. Siguiente",
            "14. Tamanho"
        };
        for (auto opcion : opciones) {
            cout << opcion << endl;
        }
        cout << "0. Salir\n";
        cin >> opc_usr;

        if (opc_usr == 0) {
            cout << "Saliendo del programa...\n";
            break;
        }

        switch (opc_usr) {
            case 1: {
                lista->push_top(new Nodo(new Alumno("Juan", "Perez", 20, "A101", 9.2)));
                lista->push_bottom(new Nodo(new Alumno("Ana", "Lopez", 21, "A102", 8.5)));
                lista->push_bottom(new Nodo(new Alumno("Luis", "Gomez", 19, "A103", 9.8)));
                lista->push_bottom(new Nodo(new Alumno("Maria", "Hernandez", 22, "A104", 7.9)));
                cout << "Lista inicializada con alumnos de prueba.\n";
                break;
            }
            case 2: {
                // Insertar al inicio
                Alumno* nuevo = crearAlumno();
                lista->push_top(new Nodo(nuevo));
                break;
            }
            case 3: {
                // Insertar al final
                Alumno* nuevo = crearAlumno();
                lista->push_bottom(new Nodo(nuevo));
                break;
            }
            case 4: {
                // Insertar en posicion
                int pos;
                cout << "Ingrese posicion: ";
                cin >> pos;
                Alumno* nuevo = crearAlumno();
                lista->insert_at(pos, new Nodo(nuevo));
                break;
            }
            case 5: {
                // Buscar
                int pos;
                cout << "Ingrese posicion: ";
                cin >> pos;
                Nodo* encontrado = lista->search(pos);
                if (encontrado) {
                    cout << "Elemento en " << pos << ": "
                         << encontrado->get_tipoDato_actual()->toString() << endl;
                } else {
                    cout << "No encontrado.\n";
                }
                break;
            }
            case 6: {
                // Eliminar
                int pos;
                cout << "Ingrese posicion a eliminar: ";
                cin >> pos;
                if (lista->delete_nodo(pos)) {
                    cout << "Elemento eliminado.\n";
                } else {
                    cout << "No se pudo eliminar.\n";
                }
                break;
            }
            case 7: {
                // Eliminar todo
                lista->delete_all();
                cout << "Lista vaciada.\n";
                break;
            }
            case 8: {
                // Vacia
                cout << (lista->is_empty() ? "Lista vacia\n" : "Lista con elementos\n");
                break;
            }
            case 9: {
                // Mostrar todo
                lista->print_head_to_tail();
                break;
            }
            case 10: {
                // Primero
                lista->top();
                break;
            }
            case 11: {
                // Ultimo
                lista->last();
                break;
            }
            case 12: {
                // Anterior
                lista->previous();
                break;
            }
            case 13: {
                // Siguiente
                lista->next();
                break;
            }
            case 14: {
                // Tamaño
                lista->size();
                break;
            }
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
    return 0;
}