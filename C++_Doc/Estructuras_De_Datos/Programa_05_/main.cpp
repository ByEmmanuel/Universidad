#include "Lista.cpp"
#include <iostream>

using namespace std;

int main(){
    int tope = 100;
    int cantidad = 10;

    Lista* lista_1 = new Lista();
    Lista* lista_2 = new Lista();
    Lista* lista_3 = new Lista();

    for (int i = 0; i < cantidad; i++) {
        int numero_generado = rand() % tope;
        lista_1->insert_up(numero_generado);
    }

    for (int i = 0; i < cantidad; i++) {
        int numero_generado = rand() % tope;
        lista_2->insert_up(numero_generado);
    }

    for (int i = 0; i < cantidad; i++) {
        int numero_generado = rand() % tope;
        lista_3->insert_up(numero_generado);
    }

    cout << "\n-------Lista 1-----------" << endl;
    lista_1->print_all();
    cout << "\n--------Burbuja----------" << endl;
    lista_1->Bubble();
    cout << "\n----------------------------" << endl;

    cout << "\n-------Lista 2-----------" << endl;
    lista_2->print_all();
    cout << "\n--------Merge----------" << endl;
    lista_2 = lista_2->Merge_Sort(lista_2);
    lista_2->print_all();
    cout << "\n----------------------------" << endl;

    cout << "\n-------Lista 3-----------" << endl;
    lista_3->print_all();
    cout << "\n--------Shell Sort----------" << endl;
    lista_3->Shell_Sort();
    lista_3->print_all();
    cout << "\n----------------------------" << endl;

    return 0;

}