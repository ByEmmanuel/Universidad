//
// Created by Jesus Emmanuel Garcia on 10/23/25.
//
// definir diccionario morse

#include "../Arboles/Arbol.h"

inline Arbol* morse(){
    Arbol* arbol = new Arbol;
    // codigo ascci de la a a la z
    int abecedario = 97;
    for (int i = 0; i < 26; i++){
        arbol->insertar(abecedario);
        abecedario++;
    }

    








    return arbol;
}