package org.Alpha.Algoritmos;

import java.util.ArrayList;

public class Merge_Sort {
    public static int[] MergeSort(int[] vector){
        int tamaño = vector.length;
        if (tamaño <= 1) return vector;
        int medio = tamaño / 2;
        int[] tmp_1 = new int[tamaño/2];
        int i = 0;
        for (i = 0; i < tamaño/2; i++){
            tmp_1[i] = vector[i];
        };

        int[] tmp_2 = new int[tamaño - medio];
        int j = 0;
        while (i < tamaño){
            tmp_2[j] = vector[i];
            i++;
            j++;
        }

        int[] izquierda = MergeSort(tmp_1);
        int[] derecha = MergeSort(tmp_2);

        return Merge(izquierda,derecha);
    }

    public static int[] Merge(int[] izq, int[] der){
        int[] resultado = new int[izq.length + der.length];
        int i = 0, j = 0, k = 0;

        while (i < izq.length && j < der.length){
            if (izq[i] <= der[j]){ // si izq en su parte dato es menor o igual que der en su parte dato
                resultado[k++] = izq[i++]; // agregamos izq al nuevo vector y izq = izq.sig
            }else{
                resultado[k++] = der[j++];  // agregamos der al nuevo vector y izq = izq.sig
            }
        }
        // estos while son por si un vector es mas grande que otro
        while (i < izq.length){
            resultado[k++] = izq[i++];
        }
        while (j < der.length){
            resultado[k++] = der[j++];
        }

        return resultado;

    }

    public static void main(String[] args) {

        int[] vector = {3,5,2,1,4,6,34,5,345,23,234};

        for (int a : vector){
            System.out.println(a);
        }

        vector = MergeSort(vector);

        System.out.println("  ");

        for (int a : vector){
            System.out.println(a);
        }


    }
}
