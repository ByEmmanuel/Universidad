package org.Alpha.Algoritmos;

import java.util.Random;

public class Multiplicacion_De_Matrices {

    public static void main(String[] args) {

        int[][] matriz_1_ = {
                {2,3,34,4,5,5,6,7},
                {34,35,46,34,36},
                {1,2,3,4,5,6,7,8,9}
        };

        int[][] matriz_2_ = {
                {2,3,34,4,5,5,6,7},
                {34,35,46,34,36},
                {1,2,3,4,5,6,7,8,9}
        };

        int[][] matriz_1A_ = {
                       /*Col*/
                /*Fil */{1 , 2},
                        {4 , 5},

        };
        int[][] matriz_2A_ = {

                {5 , 6},
                {7 , 8},
                //{9 , 10}
        };

        int[][] matriz_5x5_A = {
                {1, 2, 3, 4, 5},
                {5, 4, 3, 2, 1},
                {1, 1, 1, 1, 1},
                {2, 3, 2, 3, 2},
                {9, 8, 7, 6, 5}
        };

        int[][] matriz_5x5_B = {
                {1, 0, 2, 0, 1},
                {0, 1, 0, 2, 0},
                {1, 0, 1, 0, 1},
                {0, 2, 0, 1, 0},
                {1, 0, 2, 0, 1}
        };
        // La multiplicacion seria 1 X 5 + 2 X 7 , 1 X 6 + 2 X 8 == 5 + 14 , 6 + 16     == 19 , 22
        //                         4 X 5 + 5 X 7 , 4 X 6 + 5 X 8 == 20 + 35 , 24 + 40   == 55 , 64

        //System.out.println(multiplicado(matriz_1_,matriz_2_));
        //imprimir_Matriz((multiplicado(matriz_1A_,matriz_2A_)));

        imprimir_Matriz((multiplicado(matriz_5x5_A,matriz_5x5_B)));
        //imprimir_Matriz(generarMatrizAleatoria(50,50));
    }

    public static int[][] multiplicado(int[][] matriz_A, int [][] matriz_B ){
        //Limitante, tiene que ser la multiplicacion N X M , la matriz A debe compartir filas o columnas para poder ser multiplicada
        //esto me lo corrigio gpt
        int[][] resul = new int[matriz_A.length][matriz_B.length];
        System.out.println(matriz_A.length);
        //mia version
        //int[][] resul = new int[matriz_A.length][matriz_B.length];
        int suma = 0;
        int ind_A_ = 0;
        //int ind_B_ = 0;
        int i ;
        imprimir_Matriz(resul);
        System.out.println("Operaciones Totales : " + (matriz_B.length + matriz_B.length ) * 2);
        //esto multiplicado x2

        for (i = 0; i < matriz_B.length; i++) {
            //Corresponde a fila [] y columna []
            int a = 0;
            int b = 0;
            for (int j = 0; j < matriz_A.length; j++){
                 for (int k = 0; k < matriz_B.length; k++) {
                    //System.out.printf("A%d ",matriz_A[i][k]);
                    ///System.out.printf("%d %d %d \n",i, j, k);
                    a += matriz_A[i][k] * matriz_B[k][j];
                    //System.out.printf("B%d ",matriz_B[k][j]);
                    //System.out.println(" b : " + b);
                 }
                 resul[j][i] = a;
                 //System.out.println(" Multiplicacion: " + a);
                 a=0;
            }
        }
            System.out.println();
            System.out.println();
        return resul;
    }

    public static void imprimir_Matriz(int[][] lista){
            for (int i = 0; i < lista.length; i++){
                for (int j = 0; j < lista.length; j++ ){
                    System.out.printf("%d " , lista[j][i]);
                }
                System.out.println();
            }

    }

    public static int[][] generarMatrizAleatoria(int filas, int columnas) {
        int[][] matriz = new int[filas][columnas];
        Random rand = new Random();
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                matriz[i][j] = rand.nextInt(10); // numeros entre 0 y 9
            }
        }
        return matriz;
    }

}
