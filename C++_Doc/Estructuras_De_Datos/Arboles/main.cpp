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

   arbol->insertar(1);
    arbol->insertar(5);
   arbol->insertar(8);
   arbol->insertar(78);
   arbol->insertar(345);
   arbol->insertar(2);
   arbol->insertar(23);
   arbol->insertar(124);
   arbol->insertar(34);
   arbol->insertar(56);
   arbol->insertar(45);

   arbol->mostrar(arbol->raiz);

       return 0;
}
