#include "Algoritmo.h"
#include "Lista.h"
#include <iostream>

int main()
{
    
    Algoritmo* alg = new Algoritmo();
    Lista* lista = alg->getlista();

    lista->introducirElem(15);
    lista->introducirElem(1);
    lista->introducirElem(65);
    lista->introducirElem(6);
    lista->introducirElem(2);
    lista->introducirElem(125);
    lista->introducirElem(12);
    lista->introducirElem(45);
    lista->introducirElem(20);
    lista->introducirElem(12);
    lista->introducirElem(89);
    lista->introducirElem(63);
    lista->introducirElem(3);
    lista->introducirElem(7);
    lista->introducirElem(45);
    lista->introducirElem(89);
    lista->introducirElem(69);
    lista->introducirElem(72);
    lista->introducirElem(46);
    lista->introducirElem(0);
    lista->introducirElem(27);

    lista->imprimirLista();

	std::cout << std::endl << "Lista ordenada: \n" << std::endl;


    alg->ordenarLista();
    
    lista->imprimirLista();

    
}
