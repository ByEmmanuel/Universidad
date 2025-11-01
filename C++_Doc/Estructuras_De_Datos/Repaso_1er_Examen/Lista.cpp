#include "Nodo.h"
#include <iostream>


using namespace std;


class Listona{
    Nodo* head; //cabezona
    //Nodo* tail;
public: 
Listona();

void BurbujaMejorada();
void Bubble();
void insert_up(int dato);
void insert_down();
void insert_at(int dato);
 bool is_empty();
 int size();
 bool delete_at();
 bool delete_up();
 bool delete_down();
 bool is_equals();
 int search_obj();
 void print_all();

// buscar
// eliminar todo
};

 inline Listona::Listona(){
     head = nullptr;
 };

inline void Listona::insert_up(int dato){
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

        // h -> 2 -> 4
        // 10
        // 10 -> 2 -> 4
        
    }
    //this->head = aux;
}

inline void Listona::Bubble(){
  int tamaño = size();
    cout << " tamaño " << tamaño << endl;
    int cantidad_iteraciones = 0;
    for (int i = 0; i <= tamaño; i++){
    Nodo* aux = head;
    while (aux->sig){
        if (aux->dato >= aux->sig->dato){
            // swap
            int dato_siguiente = aux->dato;
            // 1 -> 2       2 -> 2
            aux->dato = aux->sig->dato;
            aux->sig->dato = dato_siguiente;
        }
        cantidad_iteraciones++;
        aux = aux->sig;
        }
    }
  cout << "cantdad iteraciones = " << cantidad_iteraciones;
}


inline void Listona::BurbujaMejorada() {
    bool flag;
    int cantidad_iteraciones = 0;
    do{
    Nodo* aux = head;
    flag = false;
    while (aux->sig && aux) {
        if (aux->dato > aux->sig->dato) {
            int temp = aux->dato;
            aux->dato = aux->sig->dato;
            aux->sig->dato = temp;
            flag = true;                
        }
        aux = aux->sig;
        cantidad_iteraciones++;
        
    }
}while(flag);
    cout << "cantdad iteraciones = " << cantidad_iteraciones;
}

inline void Listona::insert_down(){

}

inline bool Listona::is_empty(){

}

inline int Listona::size(){
    Nodo* aux = head;
    int contador = 1;
    while (aux){
        aux = aux->sig;
        contador++;
    }
    return contador;
}

inline bool Listona::delete_at(){

}

inline bool Listona::delete_up(){

}

inline bool Listona::is_equals(){
    
}

inline int search_obj(){
    
}

inline void Listona::print_all(){
    Nodo* aux = head;
    while(aux){
        cout << aux->dato << "->";
        aux = aux->sig;
    }
}






/*
 public static void bubbleSort(int tempArray[]) {
            
            //bubble sort code goes here (you code it) 
            
            // loop to control number of passes
            for (int pass = 1; pass < tempArray.length; pass++) {
                System.out.println(pass);
                // loop to control number of comparisions for length of array - 1
                for (int element = 0; element < tempArray.length - 1; element++) {
                    
                    // compare side-by-side elements and swap tehm if
                    // first element is greater than second elemetn swap them
                    if (tempArray [element] > tempArray [element + 1]) {
                        swap (tempArray, element, element + 1);
                        
                    }
                }
            }
        }
     
       public static void swap(int[] tempArray2,int first, int second) {
            
           //swap code goes here (you code it) 
           
           int hold; // temporary holding area for swap
           
           hold = tempArray2 [first];
           tempArray2 [first] = tempArray2 [second];
           tempArray2 [second] = hold;
           
        }*/