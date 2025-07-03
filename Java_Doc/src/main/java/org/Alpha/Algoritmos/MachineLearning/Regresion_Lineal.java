package org.Alpha.Algoritmos.MachineLearning;

public class Regresion_Lineal {


    // y = mx + b
    // y` = íx + `b
    //Ax + By + C = 0
    // VEC-r(t) = VEC-P + t * VEC-V
    Regresion_Lineal(){

    }

    public static int[] vector_resultante(int[] vector_1, int[] vector_2_, int escalar){
        int[] resultado = new int[vector_2_.length];

        for (int i = 0; i < vector_2_.length; i++) {
            vector_2_[i] *= escalar;
        }

        for (int i = 0; i < vector_1.length; i++) {
            resultado[i] = (vector_1[i] += vector_2_[i]);
        }

        return vector_1;
    }

    public static void imprimir_vector(int[] vector){
        for (int i = 0; i < vector.length; i++) {
            System.out.println(vector[i]);
        }
    }


    public static void main(String[] args) {

        int[] a = {3,4};
        int[] b = {1,3};
        int[] c = {};
        int[] d = {};
        int[] e = {};
        int[] f = {};

        imprimir_vector(a);
        imprimir_vector(vector_resultante(a,b, 2));
        imprimir_vector(a);
    }

}
