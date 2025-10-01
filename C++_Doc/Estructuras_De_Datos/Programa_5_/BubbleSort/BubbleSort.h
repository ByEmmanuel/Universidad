//
// Created by Jesus Emmanuel Garcia on 10/1/25.
//

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "../Lista/Lista.h"

class BubbleSort {
public:
    void swap(Nodo* menor, Nodo* mayor);
    void sort(ListaDobleLigada* lista);
};



#endif //BUBBLESORT_H
