//
// Created by Jesus Emmanuel Garcia on 29/10/24.
// Codigo 221410985
// Crear un programa que imprima las tablas de verdad de las compuertas and or y la negación de ambas compuertas en lenguaje c,
// c++ o python sin utilizar librerías existentes.

#include <iostream>
using namespace std;

inline bool compuertaAND(bool valor_1_, bool valor_2_){
    //si los 2 valores juntos son true siempre sera true
    if (valor_1_ and valor_2_){
        return true;
    }
}
inline bool compuertaOR(bool valor_1_, bool valor_2_){
    // si alguno de los 2 valores es true, la condicion siempre sera true
    if (valor_1_ or valor_2_){
        return true;
    }

}


int main(){
    bool var = true;
    bool var2 = false;
    if (compuertaAND(var, var) == 1){
        cout << "El valor es Verdadero" << endl;
    }else{
        cout << "El valor es Falso" << endl;
    }

    if (compuertaOR(var2, var2) == 1){
        cout << "El valor Es Verdadero" << endl;
    }else{
        cout << "El valor es Falso" << endl;
    }

    return 0;
}
