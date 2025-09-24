//
// Created by Jesus Emmanuel Garcia on 9/22/25.
//
#include <iostream>
using namespace std;
inline int merge_sort(int vector[],int medio){
    int vector_izq[] = {};
    for (int i = 0; i < medio; i++){
        vector_izq[i] = vector[i];
    }

    int vector_der[] = {};
    for (int i = sizeof(vector) -1; i >= medio; i--){
        vector_der[i] = vector[i];
    }

}

inline int merge_sort(int vector[], int izq, int der, int medio){
    //if (izq > der) return vector[izq];
    int cantidad_elementos_izq = (sizeof(vector)/sizeof(vector[0]) / 2;i

    int vector_izq[medio-der] = {};
    for (int i = 0; i < medio; i++){
        vector_izq[i] = vector[i];
        cout << vector[i] << endl;
    }

    int vector_der[medio-] = {};
    for (int i = size(vector) -1; i >= medio; i--){
        vector_der[i] = vector[i];
        cout << vector[i] << endl;
    }

    std::cout << "vector izq" << endl;
    for (const int a : vector_izq){
        cout << a << endl;
    }
    std::cout << "vector der" << endl;
    for (const int a : vector_der){
        cout << a << endl;
    }
}

int main(){

    int vector_a[10] = {5,6,4,2 ,2,34,3456,754,234,623};

    std::cout << "Tamaño vector: " << size(vector_a) << endl;

    int resultado[] = {};

    int tamaño = sizeof(vector_a);
    int medio = tamaño/ 2;
    int izq = 0;
    int der = tamaño-1;
    merge_sort(vector_a, izq, der, medio);

    /*for (int i = tamaño; i >= 0; i--){
        resultado[i] = merge_sort(vector_a, izq, der, medio);
    }

    for (int i = tamaño; i >= 0; i--){
        std::cout << resultado[i] << std::endl;
    }*/
}
