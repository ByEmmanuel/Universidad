#pragma once
#ifndef Algoritmo_H
#include "Lista.h"

class Algoritmo{
private:
	Lista* l;
	Nodo* h;
	Nodo* t;
public:
	Algoritmo();
	~Algoritmo();

	void introducirElem(int);

	Nodo* dividir(Nodo*);
	Nodo* mergesort(Nodo*);
	Nodo* merge(Nodo*, Nodo*);
	Lista* getlista();
	void ordenarLista();

};



#endif // !Algoritmo_H


