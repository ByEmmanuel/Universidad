package org.ONE_Introduccion_A_Java;
import java.lang.reflect.Array;
import java.util.*;


/**
 *  Descripción: Este Es una despcripcion para los diferentes estrucuturas de datos en java como lo son los arrays, listas y colas
 *  Existen diferentes tipos de estructuras de datos en java, como lo son los
 *  arrays, listas, colas, pilas, linkedlist, Hashmap, entre otros
 *
 *  Fecha de creación: 20/09/2024
 *  Autor: @ByEmmanuel
 *
 *  1 Arrays:
 *
 *      Tamaño fijo.
 *      Acceso rápido por índice.
 *      No pueden crecer o reducirse dinámicamente.
 *
 *  2 Listas (List):
 *
 *      Tamaño dinámico.
 *      Permiten duplicados y mantienen el orden de inserción.
 *      Implementaciones comunes: ArrayList, LinkedList.
 *
 *  3 Colas (Queue):
 *
 *      Estructura FIFO (First In, First Out).
 *      Implementaciones comunes: LinkedList, PriorityQueue.
 *      Métodos clave: offer(), poll(), peek().
 */



public class _3_Arrays {

    private static CalcularTiempo calcularTiempo = new CalcularTiempo();

    //esto es un array de 5 elementos
    private static final int[] array = new int[50000];
    // esta es una lista
    private static final List<Integer> lista = new ArrayList<>();
    // Esta es un cola que dependiendo el tipo especificamente sale el primero o el ultimmo
    private static final Queue<Integer> cola = new PriorityQueue<>();

    public static void main(String[] args) {
        calcularTiempo.init();


        for (int i = 0; i < array.length  ; i++) {
            array[i] = i;
            System.out.println(array[i]);
        }

        Integer num = 123;
        lista.add(num);

        //Imprime el elemmento buscado (En este caso es el indice)
        System.out.println(lista.get(0));

        //lista.add(Usuario);

        cola.add(1);
        cola.add(233);
        int tamñocola = cola.size();
        System.out.println( "Tamaño de la cola; " + tamñocola);


        calcularTiempo.end();
        calcularTiempo.retornarTiempo();
    }


}
