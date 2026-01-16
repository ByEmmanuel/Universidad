package org.Alpha.Algoritmos;

public class _Bubble_sort {

    static void exchange_sort(int[] lista ){
        for (int i = 0; i < lista.length; i++){
            for (int j = 0; j < lista.length; j++){
                // tomar posiciones -> esto se puede roducir despues
                int a = lista[i];
                int b = lista[j];
                // cambio
                if (a < b){
                    lista[i] = b;
                    lista[j] = a;
                }
            }
        }


        for(int entero : lista){
            System.out.println(entero);
        }
    }

    // esto no es bubble
    static void dont_bubble(int[] lista){
        for (int i = 0; i < lista.length; i++) {
            for (int j = 0; j < lista.length; j++) {
                // swap
                if (lista[i] < lista[j]){
                    int a = lista[i];
                    int b = lista[j];

                    lista[j] = a;
                    lista[i] = b;
                }
            }
        }

        System.out.println("BUBBLEEE");
        for(int entero : lista){
            System.out.println(entero);
        }
    }


    // este es bubble -> el proposito de bubble es que el mayor (i) lo mande hasta atras (burbujee)
    // y hace que compare a los de al lado siempre (i+1)
    // los algoritmos arriba no son estables a pesar de que puedan funcionar
    static void bubble(int[] lista){
        for (int i = 0; i < lista.length ; i++) {
            for (int j = 0; j < lista.length-1; j++) {
                if(lista[j] > lista[j+1]){
                    int a = lista[j];
                    lista[j] = lista[j+1];
                    lista[j+1] = a;
                }
            }
        }

        System.out.println("-----------------buble i guesss-------");
        for (int x : lista){
            System.out.println(x);
        }
    }

    public static void main(String[] args) {
        int[] lista_ = {2,5,3,34,45,2,2,34,4,54,3,23,423,4234};
        //exchange_sort(lista_);
        //dont_bubble(lista_);
        //bubble(lista_);
        bubble(lista_);
    }
}
