package org.Alpha.Algoritmos;

import java.util.Scanner;

public class Rentabilidades_Pasivas {

    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        // Es casi imposible obtener mayores rentabilidades a 2% por mes

        while (true){
            System.out.println("Ingresa opcion: ");
            int opciones = 4;
            String[] opcionesMenu = {"1 : Calcular % Gasto mensual","2 : Calcular Rentabilidad Mensual y anual ","",""};

            for (int i = 0; i < opciones; i++) {
                System.out.println(opcionesMenu[i]);
            }
            switch (scanner.nextInt()){
                case 1:
                    calcular_rentabilidad(scanner);
                    break;
                case 2:
                    calcular_porcentaje_gasto_mensual(scanner);
                    break;
                case 3:

                     break;
                case 4:

                    break;
                default:
                    System.out.println("Opcion no valida o cancelado");
                    System.exit(0);
                    return;
            }
        }
    }

    public static double calcular_rentabilidad(Scanner scanner){
        System.out.println("Ingresa Rentabilidad mensual 0-2");
        double rentabilidad = scanner.nextDouble() / 100;
        System.out.println("Ingresa Capital a calcular");
        double capital = scanner.nextDouble();

        System.out.println("Ingresa periodo en meses");
        int periodo_meses = scanner.nextInt();

        //System.out.println(calcular(capital, rentabilidad/100 , 12));

        rentabilidad += 1;

        final double resultado = Math.pow(rentabilidad,periodo_meses);
        //                  50000 * ((1+0.01)^12 -1)
        final double interes_Neto = capital * (resultado-1);
        System.out.printf("Resultado Interes: %f por el periodo: %d meses \n",interes_Neto, periodo_meses);
        System.out.printf("Resultado Interes por mes: %f \n",interes_Neto/periodo_meses);
        return capital * resultado;

    }

    public static double calcular_porcentaje_gasto_mensual(Scanner scanner){

        System.out.println("Ingrese Capital total");
        double cantidad_total = scanner.nextDouble();
        System.out.println("Ingresse gasto por mes");
        double gasto_mensual = scanner.nextDouble();
        System.out.println("Tu gasto mensual en % es " + gasto_mensual/cantidad_total * 100);
        return (gasto_mensual/ cantidad_total) * 100;
    }


}
