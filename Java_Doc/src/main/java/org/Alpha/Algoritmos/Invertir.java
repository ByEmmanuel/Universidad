package org.Alpha.Algoritmos;

public class Invertir {

    static class Lista{
        Nodo head = null;
        // aux siempre va a apuntar al ultimo dato
        Nodo aux = null;

        void insertar(int valor){
            if (head == null){
                head = new Nodo(valor);
                aux = head;
            }else {
                aux.siguiente = new Nodo(valor);
                aux = aux.siguiente;
            }
        }

        void imprimir_lista(){
            Nodo aux_2 = head;

            while (aux_2 != null){
                System.out.print(aux_2.val + "\t");
                aux_2 = aux_2.siguiente;
            }
        }

        void invertir(){
            Nodo prebv = null;
            Nodo actual = head;
            while (actual != null){
                Nodo sig = actual.siguiente;
                actual.siguiente = prebv;
                prebv = actual;
                actual = sig;
            }
            this.head = prebv;
        }

    }

    static class Nodo{
        int val;
        Nodo siguiente;
        Nodo(int val){this.val = val;}
    }



    public static void main (String[] args){
        Lista lista = new Lista();
        lista.insertar(33);
        lista.insertar(53);
        lista.insertar(8);
        lista.insertar(5);
        lista.insertar(4);
        lista.insertar(1);
        lista.insertar(6);

        lista.imprimir_lista();
        System.out.println(" ");
        lista.invertir();
        lista.imprimir_lista();
    }


}
