
#include "Lista.h"
#include <iostream>



Lista::Lista() {
	h = nullptr;
	t = nullptr;

}
Lista::~Lista() {
	delete h,t;

}

void Lista::imprimirLista() {
	Nodo* aux = h;
	if (h != nullptr) {
		while (aux) {
			std::cout << aux->getDato() << " -> ";
			aux = aux->getsig();
		}
	}
	else {
		std::cout << "Lista vacia" << std::endl;
	}
}


void Lista::introducirElem(int valor) {
	Nodo* tmp = new Nodo(valor, nullptr, nullptr);
	if (h == nullptr)
		t= h = tmp;

	else {
		tmp->setsig(nullptr);
		t->setsig(tmp);
		tmp->setant(t);
		t = tmp;
	}
}


int Lista::tamanio() {
	int cont = 0;
	Nodo* aux = geth();
	while (aux) {
		cont++;
		aux = aux->getsig();
	}
	return cont;
}

Nodo* Lista::geth() {
	return h;
}

Nodo* Lista::gett() {
	return t;
}

void Lista::seth(Nodo* h) {
	this->h = h;
}

void Lista::sett(Nodo* t) {
	this->t = t;
}