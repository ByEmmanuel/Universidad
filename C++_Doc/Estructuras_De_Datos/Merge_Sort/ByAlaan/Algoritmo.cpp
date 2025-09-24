
#include "Algoritmo.h"
#include <iostream>

Algoritmo::Algoritmo() {
	l = new Lista();
	h = nullptr;
	t = nullptr;

}

Algoritmo::~Algoritmo() {
	delete l;
}

Lista* Algoritmo::getlista() {
	return l;
}

Nodo* Algoritmo::dividir(Nodo* h) {
	Nodo* rapido= h;
	Nodo* lento= h;
	while (rapido && rapido->getsig() && rapido->getsig()->getsig() && lento->getsig())	{
		rapido = rapido->getsig()->getsig();
		lento = lento->getsig();
	}
	Nodo* division = lento->getsig();
	lento->setsig(nullptr); ////////////posible fallo lento->getsig()->setsig(nullptr);
	if (division)
		division->setant(nullptr);
	return division;
}

Nodo* Algoritmo::mergesort(Nodo* h) {
	if (!h || !h->getsig())
		return h;

	Nodo* division = dividir(h);

	h = mergesort(h);
	division = mergesort(division);

	return merge(h, division);
}

Nodo* Algoritmo::merge(Nodo* h, Nodo* division) {
	if (!h)
		return division;
	if (!division)
		return h;
	if (h->getDato() <= division->getDato()) {
		h->setsig(merge(h->getsig(), division));
		if (h->getsig()) h->getsig()->setant(h);
		h->setant(nullptr);  // la cabeza no tiene anterior
		return h;
	}
	else {
		division->setsig(merge(h, division->getsig()));
		if (division->getsig()) division->getsig()->setant(division);
		division->setant(nullptr);
		return division;
	}


}


void Algoritmo::ordenarLista() {
	Nodo* nuevaCabeza = mergesort(l->geth());
	l->seth(nuevaCabeza);

	// Actualiza la cola recorriendo desde la nueva cabeza
	Nodo* nuevaCola = nuevaCabeza;
	while (nuevaCola && nuevaCola->getsig()) {
		nuevaCola = nuevaCola->getsig();
	}
	l->sett(nuevaCola);
}

