//
// Created by Jesus Emmanuel Garcia on 10/1/25.
//

#include "BubbleSort.h"
#include <iostream>

// el metodo bubbleSort debe estar inclouido en la propia TDA

// aqui ya cayo en el caso de que es menor
void BubbleSort::swap(Nodo* actual, Nodo* adelante){
    // el actual se va ir para arriba ->
    // y el de adelante = tipo de dato actual
    int dato_adelante = adelante->get_tipoDato();
    //int dato_actual = actual->get_tipoDato();

    adelante->set_tipoDato(actual->get_tipoDato());
    actual->set_tipoDato(dato_adelante);
}

void BubbleSort::sort(ListaDobleLigada* lista){
    int size_list = lista->size();
    int a = 0;

    // si auxiliar tiene parte siguiente ( hay almenos 2 elementos )
    if (size_list > 1) {
        for (int i = 0; i < size_list; i++) {
            Nodo* aux = lista->head;
            while (aux->siguiente) {
                // si es mayor el tipo de dato actual lo va a mandar para atras ->
                if (aux->get_tipoDato() > aux->siguiente->get_tipoDato()) {
                    // swap
                    // actual = 10 , sig = 9
                    //swap(aux, aux->siguiente);
                    int actual = aux->get_tipoDato();
                    aux->set_tipoDato(aux->siguiente->get_tipoDato());
                    aux->siguiente->set_tipoDato(actual);
                }
                aux = aux->siguiente;
                std::cout << "si " << std::endl;
            }
        }
    }

}
