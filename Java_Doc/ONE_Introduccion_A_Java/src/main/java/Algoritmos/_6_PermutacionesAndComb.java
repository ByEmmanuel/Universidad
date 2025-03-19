package Algoritmos;

import java.util.Scanner;

/*
*
* Determina un programa que use Permutacion o combinacion de un objeto dado
*
* */
public class _6_PermutacionesAndComb {

    public static void main(String[] args) {

        Scanner teclado = new Scanner(System.in);
        boolean bandera = true;


        while (bandera){
            System.out.println("Nota: En una permutacion se permiten objetos repetidos¡");
            System.out.println("Seleccione Opcion; \n 1: Permutacion \n2: Combinacion");

            if(teclado.nextInt() == 1){
                System.out.println("Ingrese numero maximo de objetos");
                int num1 = teclado.nextInt();
                System.out.println("Ingrese numero minimo de Permutas");
                int num2 = teclado.nextInt();

                System.out.println("Permutaciones; " + Permutaciones(num1,num2));
                System.out.println("Combinaciones; " + Combinaciones(num1,num2));


            }
        }
    }

    public static int Permutaciones(int num1, int num2){
        int resultado = 1;
        for (int i = 0; i < num2; i++){
            resultado *= num1 -i;
        }
        return resultado;
    }

    public static int Combinaciones(int num1, Integer num2){
        int resultado = 1;

        for (int i = 0; i < num2; i++){
            resultado *= num1 -i;
        }
        int rFactorial = 1;
        for(int i = 0; i < num2; i++){
            rFactorial *= num2-i;
        }
        return resultado/rFactorial;
    }
}
