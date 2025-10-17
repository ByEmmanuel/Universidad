#include <iostream>
#include "Arbol.h"


using namespace std;
/// crear funcion insertar
void funNum(int i){
    if (i < 1000000){
        cout << i << ",";
        funNum(i + 1);
        cout << " " ;
        funNum(i + 2);

    }
}

int main(){
   Arbol* arbol = new Arbol();

   arbol->insertar(1, arbol->raiz);
    arbol->insertar(5, arbol->raiz);
   arbol->insertar(8, arbol->raiz);
   arbol->insertar(78, arbol->raiz);
   arbol->insertar(345, arbol->raiz);
   arbol->insertar(2, arbol->raiz);
   arbol->insertar(23, arbol->raiz);
   arbol->insertar(124, arbol->raiz);
   arbol->insertar(34, arbol->raiz);
   arbol->insertar(56, arbol->raiz);
   arbol->insertar(45, arbol->raiz);
    arbol->insertar(0, arbol->raiz);
    arbol->insertar(7, arbol->raiz);

   arbol->mostrar(arbol->raiz);

       return 0;
}
