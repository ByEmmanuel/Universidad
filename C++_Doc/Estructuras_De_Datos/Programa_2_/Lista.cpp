//
// Created by Jesus Emmanuel Garcia on 8/27/25.
//

#include "Lista.h"
#include <iostream>
using namespace std;

void Lista::push_bottom(Nodo* nodo){
    if (head == nullptr){
            head = nodo;
            head->siguiente = nullptr;
            aux = head;
    }else{
        Nodo* temp = aux;
        while (temp->siguiente){
            temp = temp->siguiente;
        }
        temp->siguiente = nodo;
        nodo->siguiente = nullptr;
    }
}

void Lista::push_up(Nodo* nodo){
    if (head == nullptr){
        head = nodo;
        head->siguiente = nullptr;
        aux = head;
    }else{
        nodo->siguiente = head;
        head = nodo;
    }
}


/*
 *void Lista::push_bottom(Nodo* nodo){
    Nodo* tmp = aux;
    nodo->siguiente = nullptr;
    if (aux){
        cout << "aux value: " << aux->valor << "\n";
    }
    if (tmp){
        cout << "tmp value: " << tmp->valor << "\n";
    }
    /*
     *
     * Logica
     * Nodo ya tiene un valor asignado
     * mientras tmp no sea null
     * el link al siguiente nodo (valor) es igual a aux ( primera posicion )
     * y tmp se actualiza al siguiente nodo
     #1#
    if (aux == nullptr){
        aux = nodo;
        head = nodo;
    }else{
        Nodo* tmp = aux;
        while (tmp->siguiente){
            tmp = tmp->siguiente;
        }
        tmp->siguiente = nodo;
    }
}
*/

void Lista::print_elements() const{
    Nodo* dummy = head;
    while (dummy != nullptr){
        cout << "Print Elements : " << dummy->valor << "\n";
        dummy = dummy->siguiente;
    }
}

//Retornar indice
// Esto retorna un nodo ( objeto ) con el valor del indice a buscar
Nodo* Lista::index_of(Nodo* nodo) {
    int contador = 0;
    Nodo* tmp = head;
    while (tmp) {
        if (tmp->valor == nodo->valor ) {
            //cout << "El objeto esta en el indice: " << contador << "\n";
            return new Nodo(contador);
        }
        contador++;
        tmp = tmp->siguiente;
    }
    //cout << "El objeto no esta en la lista : ( " << nodo->valor << " )" << "\n";
    return nullptr;
}

void Lista::print_first_element() const{
    cout << "First element " << head->valor << "\n";
};

void Lista::print_last_element() const{
    Nodo* tmp = head;
    while (tmp->siguiente){
        tmp = tmp->siguiente;
    }
    cout << "Last element " << tmp->valor << "\n";
};


void Lista::print_aux() const{
    if (aux){
        cout << "Aux Value  " << aux->valor << "\n";
    }else{
        cout << "Aux Has no value" << "\n";
    }
}

void Lista::print_aux_next() const{
    if (aux->siguiente){
        cout << "Aux Next Value  " << aux->siguiente->valor << "\n";
    }else{
        cout << "Aux Next Has no value" << "\n";
    }
}

int Lista::size() {
    Nodo* nodo = head;
    int contador = 1;
    while (nodo != nullptr) {
        if (nodo->siguiente){
        nodo = nodo->siguiente;
        contador++;
        }else{
            break;
        }
    }
    return contador;
}

    /*
     * Logica
     al llegar al punto ( i )
     se insertara el nuevo elemento y los demas elementos se recorreran
     */

/*
bool Lista::insert_at(int posicion, Nodo* nodo){
    Nodo* tmp = head;
    int contador_lista = 0;
    while (tmp->siguiente != nullptr) {
        if (contador_lista == posicion) {
            Nodo* tmp_2_= tmp;
            head = nodo;
            while (tmp_2_->siguiente != nullptr) {
                head->siguiente = tmp;
                tmp_2_ = tmp_2_->siguiente;
            };
            //return true;
            break;
        }
        contador_lista++;
        tmp = tmp->siguiente;
    }
    return false;
}
*/
/*bool Lista::insert_at(int posicion, Nodo* nodo){
    if (posicion < 0)return false;
    Nodo* tmp = head;
    int contador_lista = 0;
    while (tmp->siguiente != nullptr) {
        if (contador_lista == posicion) {
            while (nodo->siguiente){
                nodo->siguiente = tmp;
                head->siguiente = nodo;
                //nodo = nodo->siguiente;
            }
            //aux = head;
            //return true;
            break;
        }
        //head = tmp->siguiente;
        tmp = tmp->siguiente;
        contador_lista++;
    }
    return false;
}*/

bool Lista::insert_at(int posicion, Nodo* nodo){
    if (posicion < 0)return false;
    Nodo* tmp = head;
    int contador = 0;
    while (tmp->siguiente){
        if (contador == posicion){
            break;
        }
        tmp = tmp->siguiente;
        contador++;
    }
    nodo->siguiente = tmp->siguiente;
    tmp->siguiente = nodo;

}

bool Lista::is_empty() const {
    return head == nullptr;
};
// no terminado
bool Lista::remove(int indice) {
    Nodo* dummy = head;
    int contador = 0;
    while (dummy->siguiente) {
        if (contador == indice) {
            Nodo* aux_2_ = dummy;
            while (aux->siguiente != nullptr) {
                head = aux_2_->siguiente;
                dummy = dummy->siguiente;
            }
            return true;
        }
        dummy = dummy->siguiente;
        contador++;
    }
    return false;
};

//no terminado
bool remove(Nodo* objeto) {

};


// este metodo no esta bien
// esto recorre todos los nodos anteriores
// aux apunta al ultimo elemento
void Lista::contemplate_aux(){
    Nodo* dummy = aux;

    while (dummy) {
        cout << dummy->valor << "\n";
        dummy = dummy->siguiente;
    }
}
//no terminado
void Lista::pop_up(){
    Nodo* dummy = head;
    if (head) {
        head = dummy->siguiente;
    }

}