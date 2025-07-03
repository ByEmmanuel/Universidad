package org.Alpha.Algoritmos;

import java.util.Random;

public class Multiplicacion_De_Matrices extends Throwable {

    public static void main(String[] args) {

        int[][] matriz_1_ = {
                // 1   2    3      4   5    6     7   8
                {2  ,  3 ,  34 ,   4,  5  , 5  ,  6  ,7},
                {34 , 35 ,  46 ,  34,  36 , 2  ,  3  ,4}
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

                {5 , 6, 1},
                {7 , 8, 9},
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

        int[][] matriz_1B_ = {
            {2  ,  4  , 1 },
            {0  , -1  , 3 }
        };
        int[][] matriz_2B_ = {
                { 5 , 6 },
                { 7 , 8 }
        };
        // La multiplicacion seria 1 X 5 + 2 X 7 , 1 X 6 + 2 X 8 == 5 + 14 , 6 + 16     == 19 , 22
        //                         4 X 5 + 5 X 7 , 4 X 6 + 5 X 8 == 20 + 35 , 24 + 40   == 55 , 64

        //System.out.println(multiplicado(matriz_1_,matriz_2_));
        //imprimir_Matriz((multiplicado(matriz_1A_,matriz_2A_)));

        //imprimir_Matriz((multiplicado(matriz_2A_,matriz_1A_)));

        //imprimir_Matriz(multiplicado(matriz_1B_,matriz_2B_));

        //imprimir_Matriz(multiplicado(matriz_2B_,matriz_1B_));

        //imprimir_Matriz((multiplicado(matriz_5x5_A,matriz_5x5_B)));
        //imprimir_Matriz(transpuesta(matriz_1A_));
        //imprimir_Matriz(transpuesta(matriz_5x5_A));

        //imprimir_Matriz(transpuesta(matriz_1_));
        //imprimir_Matriz(generarMatrizAleatoria(5,2));
        int aleatorio = (int) (Math.random()*10);
        try {
            imprimir_Matriz(multiplicado(generarMatrizAleatoria(8,8),generarMatrizAleatoria(8, 8)));
        }catch (Exception ex){
            System.out.println("Ha ocurrido un error ; " + ex.getMessage());
        }
    }

    // mxn * n*p
    public static int[][] multiplicado(int[][] matriz_A, int [][] matriz_B ){
        if(matriz_A[0].length > matriz_B.length){
            System.out.println("A tiene mas columnas que filas de B");
            matriz_A = transpuesta(matriz_A);
        }else {
            System.out.printf("La matriz %dx%d no se puede multiplicar por la matriz %dx%d \n",matriz_A.length,matriz_A[0].length,matriz_B.length,matriz_B[0].length);

        }
        //Limitante, tiene que ser la multiplicacion N X M , la matriz A debe compartir filas o columnas para poder ser multiplicada
        //esto me lo corrigio gpt
        int[][] resul = new int[matriz_A.length][matriz_B[0].length];
        //mia version
        //int[][] resul = new int[matriz_A.length][matriz_B.length];

        int i ;
        int b = 1;
        imprimir_Matriz(resul);

        //
        System.out.println("Columnas: " + matriz_B[0].length);
        System.out.println("Operaciones Totales : " + (matriz_B.length + matriz_B[0].length ) * 2);
        //esto multiplicado x2
        // Las veces de A
        for (i = 0; i < matriz_A.length; i++) {
            //Corresponde a fila [] y columna []
            int a = 0;
            //las filas de B
            for (int j = 0; j < matriz_B[0].length; j++){
                 for (int k = 0; k < matriz_A[0].length; k++) {
                    //System.out.printf("A%d ",matriz_A[i][k]);
                    ///System.out.printf("%d %d %d \n",i, j, k);

                    //version que si sirve
                    //a += matriz_A[i][k] * matriz_B[k][j];

                     if (i >= matriz_A[0].length){
                         //a += matriz_A[i-b][k] * matriz_B[j][k];
                         //resul[i][j] = a;
                         b++;
                     }else {
                     }
                     a += matriz_A[i][k] * matriz_B[k][j];

                    //System.out.printf("B%d ",matriz_B[k][j]);
                    //System.out.println(" b : " + b);
                 }
                 resul[i][j] = a;
                 //System.out.println(" Multiplicacion: " + a);
                 a=0;
            }
        }
            System.out.println();
            System.out.println();
        return resul;
    }

    public static int[][] transpuesta(int[][] matriz_A){
        // System.out.println(matriz_A[0].length);
        int filas_A = matriz_A[0].length;
        int columnas_A = matriz_A.length;
        /*
        System.out.println(filas_A);
        System.out.println(columnas_A);
        */
        int[][] resultado = new int[filas_A][columnas_A];
        for (int i = 0; i < filas_A ; i++){
            for (int j = 0; j < columnas_A  ; j++) {
                resultado[i][j] = matriz_A[j][i];
            }
        }
        return resultado;
    }

    public static void imprimir_Matriz(int[][] lista) throws NullPointerException{
            for (int i = 0; i < lista.length; i++){
                for (int j = 0; j < lista[0].length; j++ ){
                    System.out.printf("%d " , lista[i][j]);
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
