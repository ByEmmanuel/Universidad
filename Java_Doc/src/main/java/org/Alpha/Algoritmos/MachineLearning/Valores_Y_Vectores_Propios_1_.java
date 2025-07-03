package org.Alpha.Algoritmos.MachineLearning;

public class Valores_Y_Vectores_Propios_1_ {

    public static void main(String[] args) {
        // x^2 -3x + 2 == (x-2)(x-1) == X1 = 2, X2 = 1
        int[] _1_ = {1,-3,2};
        int[] _2_ = {2,-4,-6};
        int[] falla = {1, -2, 2};  // x² - 2x + 2 = 0


        imprimir(cuadratica(_1_));
        imprimir(cuadratica(_2_));
        imprimir(cuadratica(falla));
    }

    public static int[] cuadratica(int [] ecuacion){
        int[] resultados = new int[2];

        // (-b +- raiz(b^2 - 4ac))/2a

        int b = ecuacion[1];
        int discriminante = (int) Math.pow(b,2);
        discriminante -= (4 * ecuacion[0] * ecuacion[2]);
        discriminante = (int) Math.sqrt(discriminante);


        int a = 1;
        int c = 0;
        for (int i = 0; i < 2; i++) {
            c = (-ecuacion[1] + a*discriminante)/(2 * ecuacion[0]) ;
            resultados[i] = c;
            a*=-1;
        }

        return resultados;
    }

    public static void imprimir(int[] valores){
        for (int i = 0; i < valores.length; i++) {
            System.out.printf("X_%d : %d\n",i,valores[i]);
        }
    }
}
