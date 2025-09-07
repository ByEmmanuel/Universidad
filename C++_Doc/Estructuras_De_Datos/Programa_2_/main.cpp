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
    lista->push_up(new Nodo(20));
    lista->push_up(new Nodo(44));
    lista->push_up(new Nodo(55));
    lista->push_up(new Nodo(78));

    cout << "El tamaño es: " << lista->size() << "\n";

    lista->push_up(new Nodo(90));

    lista->push_bottom(new Nodo(10));

    lista->push_up(new Nodo(100));

    /*  salida esperada
     *  100
     *  90
     *  78
     *  55
     *  44
     *  20
     *  10
     */

    lista->print_elements();
    lista->_first_element();
    lista->_last_element();
    lista->print_aux();
    lista->print_aux_next();

    cout << "El objeto esta en: " << lista->index_of(new Nodo(100))->valor << "\n";
    cout << "El objeto esta en: " << lista->index_of(new Nodo(78))->valor << "\n";

    // esta linea me causa un error porque estoy intentando acceder a una direccion invalida
    // Eso deberia de causar un index_out_of_bounds o null_pinter_excepcion
    /*
     *try {
        cout << "El objeto esta en: " << lista->index_of(new Nodo(109))->valor << "\n";
    }catch (exception ex) {
        cout << ex.what() << "\n";
    }
    */

    cout << "El tamaño es: " << lista->size() << "\n";

    cout << "Recorrer auxiliar: " << "\n";

    lista->contemplate_aux();

    cout << "Print Hacia adelante: " << "\n";
    lista->print_elements();
    cout << "Print Hacia Atras: " << "\n";
    lista->print_reverse();


    cout << "insert at 0 " << "\n";
    lista->insert_at(0,new Nodo(1));

    cout << "El tamaño es: " << lista->size() << "\n";

    lista->print_elements();

    cout << "\nBorrando 2 elementos de la lista " <<"\n\n" ;

    lista->pop_up();
    lista->pop_up();

    /**
     * Debe  borrar 1 y 100
     */
    cout << "El tamaño es: " << lista->size() << "\n";
    lista->print_elements();

    lista->pop_bottom();

    cout << "\nDelete bottom" << "\n";

    cout << "El tamaño es: " << lista->size() << "\n";
    lista->print_elements();

    lista->pop_bottom();
    lista->pop_up();

    /**
     * Debe imprimir 78 - 55 - 44
     */

    cout << "El tamaño es: " << lista->size() << "\n";
    lista->print_elements();

    cout << "El tamaño es: PRINT REVERSA " << lista->size() << "\n";
    lista->print_reverse();


    cout << "\n\n" ;
    cout << "Insert at n-1 ( ultimo ) " << "\n";
    lista->insert_at(lista->size()-1,new Nodo(47));
    lista->print_elements();
    cout << "Remove From Index ( n - 1 ) " << "\n";
    lista->remove(lista->size() -1);
    cout << "El tamaño es: " << lista->size() << "\n";
    lista->print_elements();

    cout << "Remove From Index ( n - 1 ) " << "\n";
    lista->remove(lista->size() -1);
    cout << "El tamaño es: " << lista->size() << "\n";
    lista->print_elements();


    cout << "Remove From Index ( 0 ) " << "\n";
    lista->remove(0);
    lista->print_elements();

    cout << "Remove From Index ( 2 ) " << "\n";

    //lista->remove(2);

    //lista->print_elements();

    lista->clear_all();
    lista->print_elements();

}