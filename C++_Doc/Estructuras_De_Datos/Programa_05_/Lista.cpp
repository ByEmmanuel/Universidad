#include "Nodo.h"
#include <iostream>


using namespace std;


class Lista{
    Nodo* head;
private:
Lista* Merge(Lista* izq, Lista* der);
public:
Lista();
void Bubble();
void Shell_Sort();
Lista* Merge_Sort(Lista* lista);
void insert_up(int dato);
void insert_down(int dato);
void print_all();
int size();
Nodo* search(int posicion);
};

inline Lista::Lista(){
    head = nullptr;
};

inline void Lista::insert_up(int dato){
    Nodo* aux = new Nodo(dato);
    // si head == null ( vacia ) -> inicia desde dato
    if(head == nullptr){
        head = aux;
        head->sig = nullptr;
        aux = head;
    } // 1 -> 2 -> 3
    else{
        aux->sig = head;
        head = aux;
    }
    //this->head = aux;
}

inline void Lista::insert_down(int valor){
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->sig = nullptr;

    // Si la lista está vacía, el nuevo nodo será la cabeza
    if (!head){
        head = nuevo;
        return;
    }
    // recorrer hasta el ultimo nodo
    Nodo* aux = head;
    while (aux->sig){
        aux = aux->sig;
    }
    aux->sig = nuevo;
}

inline int Lista::size(){
    Nodo* aux = head;
    int contador = 0;
    while (aux){
        aux = aux->sig;
        contador++;
    }
    return contador;
}

inline void Lista::print_all(){
    Nodo* aux = head;
    while(aux){
        cout << aux->dato << "->";
        aux = aux->sig;
    }
}

inline Nodo* Lista::search(int posicion){
    // validar posicion
    if (posicion < 0 || posicion >= size()) return nullptr;
    Nodo* aux = head;
    int index = 0;
    while (aux) {
        if (index == posicion) {
            return aux;
        }
        aux = aux->sig;
        index++;
    }
    return nullptr;
}

// ALGORITMOS DE ORDENAMIENTO // BUBBLE -> SHELL SORT -> MERGE SORT

inline void Lista::Bubble(){
  int tamaño = size();
    cout << " tamaño " << tamaño << endl;
    int cantidad_iteraciones = 1;
    for (int i = 0; i < tamaño; i++){
    Nodo* aux = head;
    while (aux->sig){
        if (aux->dato >= aux->sig->dato){
            // swap
            int dato_siguiente = aux->dato;
            // 2 -> 1 // 1 -> 1 // 1 -> 2
            aux->dato = aux->sig->dato;
            aux->sig->dato = dato_siguiente;
        }
        cantidad_iteraciones++;
        aux = aux->sig;
        }
    }
  cout << "cantdad iteraciones = " << cantidad_iteraciones;
}

// este algoritmo es mucho mas facil de
inline void Lista::Shell_Sort() {
    int n = size();
    // Si la lista está vacía o tiene un solo elemento, no hay nada que ordenar
    if (n <= 1) return;

    // Generar los intervalos de Shell Sort
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            // Obtener el dato en la posicion i
            int temp = search(i)->dato;
            int j = i;

            // Realizar el intercambio de elementos segun el intervalo (gap)
            while (j >= gap && search(j - gap)->dato > temp) {
                search(j)->dato = search(j - gap)->dato;
                j -= gap;
            }
            search(j)->dato = temp;
        }
    }
}



inline Lista* Lista::Merge(Lista* izq, Lista* der){
    Lista* resultado = new Lista();
    Nodo* aux_izq = izq->head;
    Nodo* aux_der = der->head;


    while (aux_izq && aux_der){
        if (aux_izq->dato <= aux_der->dato){
            resultado->insert_down(aux_izq->dato);
            aux_izq = aux_izq->sig;
        }else{
            resultado->insert_down(aux_der->dato);
            aux_der = aux_der->sig;
        }
    }

    // agregar los que faltaron
    while (aux_izq){
        resultado->insert_down(aux_izq->dato);
        aux_izq = aux_izq->sig;
    }
    while (aux_der){
        resultado->insert_down(aux_der->dato);
        aux_der = aux_der->sig;
    }

    return resultado;
}

inline Lista* Lista::Merge_Sort(Lista* lista){
    if (!lista || !lista->head) return lista;
    int tamaño = lista->size();

    if (tamaño <= 1) return lista;
    Lista* izq = new Lista();
    Lista* der = new Lista();

    Nodo* aux = lista->head;
    int i = 0;
    while (i < tamaño/2){
        izq->insert_down(aux->dato);
        aux = aux->sig;
        i++;
    }

    while (aux){
        der->insert_down(aux->dato);
        aux = aux->sig;
    }

    Lista* izq_merge = Merge_Sort(izq);
    Lista* der_merge = Merge_Sort(der);

    Lista* result = Merge(izq_merge, der_merge);

    // no poner esto me causa memory leaks
    delete izq;
    delete der;
    // esto me causaba que al eliminar las sub-listas, el resultado estuviera lleno de datos "vacios"
    //delete izq_merge;
    //delete der_merge;

    return result;
}