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

void Lista::print_elements() const{
    if (head == nullptr){
        cout << "La lista esta vacia" << "\n";
        return;
    }
    Nodo* dummy = head;
    cout << "Print Elements : " << "\n";
    while (dummy != nullptr){
        Alumno* alumno = dummy->get_alumno();
        cout << "Codigo" << alumno->codigo1() << "   ";
        cout << "Edad" << alumno->edad1() <<  "   ";
        cout << "Nombre" << alumno->nombre1() <<  "   ";
        cout << "Promedio" << alumno->promedio1() <<  "   ";
        cout << "Semestre" << alumno->semestre1() << endl;
        dummy = dummy->siguiente;
    }
}

//Retornar indice
// Esto retorna un nodo ( objeto ) con el valor del indice a buscar
Nodo* Lista::index_of(int codigo_alumno) {
    int contador = 0;
    Nodo* tmp = head;
    while (tmp) {
        if (tmp->get_alumno()->codigo1() == codigo_alumno ) {
            return tmp;
        }
        contador++;
        tmp = tmp->siguiente;
    }
    return nullptr;
}

void Lista::_first_element() const{
    if (head == nullptr) return;
    cout << "First element " << "\n";
    Alumno* alumno = head->get_alumno();
    cout << "Codigo" << alumno->codigo1() << "   ";
    cout << "Edad" << alumno->edad1() <<  "   ";
    cout << "Nombre" << alumno->nombre1() <<  "   ";
    cout << "Promedio" << alumno->promedio1() <<  "   ";
    cout << "Semestre" << alumno->semestre1() << endl;
};

void Lista::_last_element() const{
    Nodo* tmp = head;
    while (tmp->siguiente){
        tmp = tmp->siguiente;
    }
    cout << "Last element " << "\n";
    Alumno* alumno = tmp->get_alumno();
    cout << "Codigo" << alumno->codigo1() << "   ";
    cout << "Edad" << alumno->edad1() <<  "   ";
    cout << "Nombre" << alumno->nombre1() <<  "   ";
    cout << "Promedio" << alumno->promedio1() <<  "   ";
    cout << "Semestre" << alumno->semestre1() << endl;
};


void Lista::print_aux() const{
    if (aux){
        cout << "Aux Value  " << aux->get_alumno()->nombre1() << "\n";
    }else{
        cout << "Aux Has no value" << "\n";
    }
}

void Lista::print_aux_next() const{
    if (aux->siguiente){
        cout << "Aux Next Value  " << aux->siguiente->get_alumno()->nombre1() << "\n";
    }else{
        cout << "Aux Next Has no value" << "\n";
    }
}

int Lista::size() {
    Nodo* nodo = head;
    if (!head){
        return 0;
    }
    int contador = 1;
    while (nodo->siguiente != nullptr) {
        if (nodo->siguiente){
        nodo = nodo->siguiente;
        contador++;
        }else{
            break;
        }
    }
    return contador ;
}

bool Lista::insert_at(int posicion, Nodo* nodo){
    if (posicion < 0)return false;

    if (posicion == 0){
        nodo->siguiente = head;
        head = nodo;
        return true;
    }

    // este metodo siempre  devolvera true sin importar el resultado
    if (posicion == size() -1){
        Nodo* tmp = head;
        while (tmp->siguiente){
            tmp = tmp->siguiente;
        }
        tmp->siguiente = nodo;
        return true;
    }

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

bool Lista::remove(int indice) {
    Nodo* dummy = head;
    int contador = 0;
    Nodo* tmpR = dummy;

    if (indice == 0){
        head = dummy->siguiente;
        delete dummy;
        return true;
    }


    while (dummy->siguiente){
        dummy = dummy->siguiente;
        if (dummy->siguiente){
            tmpR = dummy;
        }
        contador++;
    }
    if (contador == indice){

        tmpR->siguiente = nullptr;
        delete tmpR->siguiente;
        return true;
    }

    return false;
};

void Lista::contemplate_aux(){
    Nodo* dummy = aux;

    while (dummy) {
        cout << dummy->get_alumno()->nombre1() << "\n";
        dummy = dummy->siguiente;
    }
}
//Eliminar arriba ( en el head )
void Lista::pop_up(){
    if (head->siguiente){
        Nodo* tmp = head;
        head = tmp->siguiente;
        delete tmp;
    }
}

void Lista::pop_bottom(){
    if (head->siguiente){
        Nodo* tmp = head;
        Nodo* tmpR = tmp;
        while (tmp->siguiente){
            tmpR = tmp;
            tmp = tmp->siguiente;
        }
        tmpR->siguiente = nullptr;
    }
}

void Lista::clear_all(){
    while (head){
        Nodo* tmp = head;
        head = head->siguiente;
        delete tmp;
    }
}

void Lista::print_reverse(){
    // size n
    int tamaño = size()-1;

    Nodo* tmp = head;

    while (tamaño >= 0){
        for (int i = 0; i < tamaño; i++){
            if (tmp->siguiente){
                tmp = tmp->siguiente;
            }
        }
        cout << "Print Reverse: " << tmp->get_alumno()->nombre1() << "\n";
        tamaño--;
        tmp = head;
    }
}