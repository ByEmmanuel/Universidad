package org.Alpha.Interaccion_Humano_C;

import java.util.InputMismatchException;
import java.util.Scanner;

public class _001_Test {

    static void bin_01(){
        int resul = 0;
        int resul_2 = 0;
        for (int i = 0; i < 9; i++) {
            resul = (int) Math.pow(2,i);
            //System.out.println(resul );
            resul_2 += (int) Math.pow(2,i);
            System.out.printf("%d, 2 a la %d \n",resul, i);
        }
        System.out.println(resul_2);
    }

    static void binario_decimal(int num){
        if (num == 0) return;
        System.out.printf("%d \n", Integer.valueOf(num));

    }

    public static void main(String[] args){
        //bin_01();

        Scanner teclado = new Scanner(System.in);
        System.out.println("Ingrese numero binario para codificar");

        int num = 0b0;
        try{
            num = teclado.nextByte();

        }catch (InputMismatchException e){
            System.out.println("El formato contiene mas de n bits");
        }

        binario_decimal(num);

    }
}
