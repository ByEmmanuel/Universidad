
#ifndef Nodo_H
#define Nodo_H

class Nodo {
private:
	int dato;
	Nodo* sig;
	Nodo* ant;

public:
	Nodo();
	Nodo(int);
	Nodo(int, Nodo*, Nodo*);
	~Nodo();

	int getDato();
	Nodo* getsig();
	Nodo* getant();
	void setsig(Nodo*);
	void setant(Nodo*);
};


#endif // !Nodo_H
