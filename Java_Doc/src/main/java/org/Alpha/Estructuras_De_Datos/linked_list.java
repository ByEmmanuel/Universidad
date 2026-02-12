package org.Alpha.Estructuras_De_Datos;
class Nodo {
    Nodo sig;
    int valor;

    Nodo(){}
    Nodo(int valor){
        this.valor = valor;
    }

    Nodo(Nodo sig, int valor){
        this.sig = sig;
        this.valor = valor;
    }




}

class List{
    Nodo head;
    Nodo tail;

    void init(int valor){
        this.head = new Nodo(valor);
        head.sig = null;
        tail = head;
    }
    // aqui van los metodos de la clase Nodo
    // ADT

    void eliminar(){

    }

    void agregar(Nodo nodo){

    }

    void agregar(int valor){
        Nodo aux = new Nodo(valor);
        if(this.head == null){
            this.head = aux;
            tail = head;
            return;
        }
        this.tail.sig = aux;
        tail = tail.sig;
    }

    void agregar_inicio(int valor){
        Nodo aux = new Nodo(valor);
        if (head != null) {
            aux.sig = head;
        }
        this.head = aux;
    }

    void printAll(){
        Nodo aux = head;
        while(aux != null){
            System.out.println(aux.valor);
            aux = aux.sig;

        }
    }

    void deleteNodo(int valor){
        Nodo aux = head;

        // si esta al inicio
        if(head.valor == valor){
            head = head.sig;
            return;
        }

        // si esta en posicion
        while (aux.sig != null){
            if (aux.sig.valor == valor){
                aux.sig = aux.sig.sig;
                return;
            }
            aux = aux.sig;
        }

        // si esta al final
        aux.valor = valor;

    }

    void agregar_final(int valor){
        Nodo aux = head;
        while (aux.sig != null){
            aux = aux.sig;
        }
        aux.sig = new Nodo(valor);

    }

}

public class linked_list {
    public static void main(String[] args) {
       List lista = new List();
       lista.init(20);
        lista.agregar(20);
        lista.agregar(10);
        lista.agregar(15);
        lista.deleteNodo(20);
        lista.deleteNodo(20);
        lista.deleteNodo(15);

        lista.agregar_inicio(9192);
        lista.agregar_inicio(98);
        lista.agregar_final(21);
        lista.agregar_final(12);


        lista.printAll();

    }
}
