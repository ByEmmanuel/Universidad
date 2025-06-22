package org.Alpha.Algoritmos;

import java.math.*;
import java.util.Scanner;

public class Rentabilidades_Pasivas {

    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        // Es casi imposible obtener mayores rentabilidades a 2% por mes
        System.out.println("Ingresa Rentabilidad mensual 0-2");
        double rentabilidad = scanner.nextDouble();
        System.out.println("Ingresa Capital a calcular");
        double capital = scanner.nextDouble();

        System.out.println(calcular(capital, rentabilidad/100 , 12));
        //System.out.println(calcular(50000, 0.01 , 10));
    }

    public static double calcular(double cantidad, double rentabilidad, int periodo_meses){
        rentabilidad += 1;
        /*double respuesta = rentabilidad;
        System.out.println(respuesta);
        for (int i = 1; i < periodo_meses ; i++ ){
            //System.out.printf("Multiplicado : %d veces. ", i);
            respuesta = respuesta * rentabilidad;
        }
        //System.out.println("\n"+respuesta);*/
        final double resultado = Math.pow(rentabilidad,periodo_meses);
        //                  50000 * ((1+0.01)^12 -1)
        final double interes_Neto = cantidad * (resultado-1);
        System.out.printf("Resultado Interes: %f por el periodo: %d meses \n",interes_Neto, periodo_meses);
        System.out.printf("Resultado Interes por mes: %f \n",interes_Neto/periodo_meses);
        return cantidad * resultado;
    }
}
