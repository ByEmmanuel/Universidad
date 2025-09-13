//
// Created by Jesus Emmanuel Garcia on 8/27/25.
//

#include "Lista.h"
#include "Nodo.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Lista* lista = new Lista();

    int opc_usr;
    while (true) {
        cout << "\nIngrese una opcion: \n";
        string opciones[13] = {
            "1. Inicializar",
            "2. Insertar al inicio",
            "3. Insertar al final",
            "4. Insertar en posicion",
            "5. Buscar",
            "6. Eliminar",
            "7. Eliminar todo",
            "8. Vacia",
            "9. Mostrar todo",
            "10. Primero",
            "11. Ultimo",
            "12. Siguiente",
            "13. Tamanho"
        };
        for (auto opcion : opciones) {
            cout << opcion << endl;
        }
        cin >> opc_usr;

        if (opc_usr < 1 || opc_usr > 13) {
            return 0;
        }

        switch (opc_usr) {
            case 1: { // Inicializar
                lista->push_up(new Nodo(new Alumno(101, 9.2, "Juan", 20, 4)));
                lista->push_up(new Nodo(new Alumno(102, 8.5, "Ana", 21, 4)));
                lista->push_up(new Nodo(new Alumno(103, 9.8, "Luis", 19, 3)));
                lista->push_up(new Nodo(new Alumno(104, 7.9, "Maria", 22, 5)));
                cout << "Lista inicializada.\n";
                break;
            }
            case 2: { // Insertar al inicio
                lista->push_up(new Nodo(new Alumno(105, 9.0, "Carlos", 20, 4)));
                break;
            }
            case 3: { // Insertar al final
                lista->push_bottom(new Nodo(new Alumno(106, 8.7, "Sofia", 21, 4)));
                break;
            }
            case 4: { // Insertar en posicion
                lista->insert_at(0,new Nodo(new Alumno(111, 9.6, "Gabriel", 20, 3)));
                break;
            }
            case 5: { // Buscar
                cout << "El objeto esta en: "
                     //<< lista->index_of(new Nodo(new Alumno(108, 9.1, "Valeria", 22, 5)))
                     << "\n";
                break;
            }
            case 6: { // Eliminar
                lista->pop_up();
                cout << "Se elimino un elemento del inicio\n";
                break;
            }
            case 7: { // Eliminar todo
                lista->clear_all();
                cout << "Lista vaciada.\n";
                break;
            }
            case 8: { // Vacia
                cout << (lista->size() == 0 ? "Lista vacia\n" : "Lista con elementos\n");
                break;
            }
            case 9: { // Mostrar todo
                lista->print_elements();
                break;
            }
            case 10: { // Primero
                lista->_first_element();
                break;
            }
            case 11: { // Ultimo
                lista->_last_element();
                break;
            }
            case 12: { // Siguiente (auxiliar)
                lista->print_aux_next();
                break;
            }
            case 13: { // Tamanho
                cout << "El tamaño es: " << lista->size() << "\n";
                break;
            }
            default: break;
        }
    }
}
