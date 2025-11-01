#include "Arbol.h"
#include <iostream>

Arbol::Arbol(){

}

void Arbol::mostrar(Nodo* raiz_sub_arbol){
    if (raiz_sub_arbol == nullptr)return;
	mostrar(raiz_sub_arbol->izq);
    std::cout << raiz_sub_arbol->valor << std::endl;
	mostrar(raiz_sub_arbol->der);

}

/*
void Arbol::insertar(int valor, Nodo* aux){
	Nodo* tmp = new Nodo(valor);

	if (raiz == nullptr){
		// crear el arbol
		this->raiz = tmp;
	}else{
		if (valor < aux->valor){
			if (aux->izq == nullptr){
				// crear la parte izq
				aux->izq = tmp;
			}else{
				insertar(valor, aux->izq);
			}
		}else{
			if (aux->der == nullptr){
				// insertar en la derecha
				aux->der = tmp;
			}else{
				insertar(valor, aux->der);
			}
		}
	}
}
*/

// esta es la mejor version de las 3
void Arbol::insertar(int valor, Nodo* aux){
	Nodo* tmp = new Nodo(valor);

	if (raiz == nullptr){
		// crear el arbol
		this->raiz = tmp;
		return;
	}

	if (valor < aux->valor){
		if (aux->izq == nullptr){
			// crear la parte izq
			aux->izq = tmp;
		}else{
			insertar(valor, aux->izq);
		}
	}else{
		if (aux->der == nullptr){
			// insertar en la derecha
			aux->der = tmp;
		}else{
			insertar(valor, aux->der);
		}
	}
};

void Arbol::insertar(int valor){
	insertar(valor,this->raiz);
};

Arbol::~Arbol(){

}
