#include <iostream>
#include "Arbol.h"


using namespace std;
/// crear funcion insertar

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
    arbol->insertar(0);
    arbol->insertar(45);
    arbol->insertar(7);

    arbol->mostrar(arbol->raiz);

    cout << "SUmatoria" << endl;

    int veces_i = 0;

    cin >> veces_i;
    int resultado = 0;
    for (int i = 0; i <= veces_i; i++){
        // sumar los n numeros de la entrada i
        resultado+= i;
    }
    cout << "Resultado sumatoria: " << resultado << endl;

    cout << "Sin ciclos " <<((veces_i)/2)*(veces_i+1) << endl;

    char abecedario = 97;

    for (int i = 0; i < 26; i++){
        cout << (char)abecedario << endl;
        abecedario++;
    }

    return 0;
}
