/**
 * Realizar un programa que eleve un número al cuadrado y al cubo en c,
 * c++ o python sin utilizar librerías establecidas.
 * 
 */

#include <iostream>

using namespace std;

// x ^ x
inline int opcion_1_(int base){
    return pow(base,base);
}

// x ^ y
inline float opcion_2_(float base, float exponente){
    return powf(base,exponente);
}

// x ^ 2
inline float opcion_3_(float base){
    return powf(base,2);
}
int main(){

    cout << "Elevar el mismo numero: " << opcion_1_(9) << endl;
    cout << "Elevar x a y exponente: "  << opcion_2_(2, 3) << endl;
    cout << "Elevar x al cuadrado: " << opcion_3_(12) << endl;

 return 0;
};