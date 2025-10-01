//
// Created by Jesus Emmanuel Garcia on 10/1/25.
//

#include "BubbleSort.h"

// el metodo bubbleSort debe estar inclouido en la propia TDA

// aqui ya cayo en el caso de que es menor
void BubbleSort::swap(Nodo* atras, Nodo* adelante){

    if (atras->anterior){
        //el de atras es mayor que el de adelante y tenemos que hacer un swap


        atras->anterior->siguiente = adelante;
        adelante->anterior = atras->anterior;
        atras->anterior = adelante;
        atras->siguiente = adelante->siguiente;
        adelante->siguiente = atras;
        if (adelante->siguiente){
            adelante->siguiente->anterior = atras;
        }
        //adelante->siguiente = atras
    }else{
        // algo
    }
}

void BubbleSort::sort(ListaDobleLigada* lista){
    int size_list = lista->size();
    int a = 0;
    Nodo* aux = lista->head;

    // si auxiliar tiene parte siguiente ( hay almenos 2 elementos )
    if (aux->siguiente){
        Nodo* aux_Adelantado = aux->siguiente;
        for (int i = 0; i < size_list; i++){
            while (aux_Adelantado){
                if (aux->get_tipoDato_actual() >= aux_Adelantado->get_tipoDato_actual()){
                    // swap
                    swap(aux, aux_Adelantado);
                }
                aux_Adelantado = aux_Adelantado->siguiente;
            }
            aux = aux->siguiente;
        }
    }

}
