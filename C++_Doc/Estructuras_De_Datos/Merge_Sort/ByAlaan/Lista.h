
#ifndef Lista_H
#define Lista_H
#include "Nodo.h"

class Lista {
private:
	Nodo* h;
	Nodo* t;


public:
	Lista();
	~Lista();
	void imprimirLista();
	int tamanio();
	Nodo* geth();
	Nodo* gett();
	void seth(Nodo*);
	void sett(Nodo*);
	void introducirElem(int valor);
};


#endif // !Lista_H

