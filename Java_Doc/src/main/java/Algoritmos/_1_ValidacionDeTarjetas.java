/* Este algoritmo representa la validacion si una tarjeta es valida o no
*   El uso de este algoritmo es para fines educacionales y eticos y solo se busca aprender
*   Este algoritmo es famosamente Algoritmo De Lunh, Matematicamente aun no se lo que es
*
*   Autor @ByEmmanuelYT
*   Fecha 28/09/24
* */

package Algoritmos;

import ONE_Introduccion_A_Java.CalcularTiempo;

import java.util.ArrayList;
import java.util.Scanner;

public class _1_ValidacionDeTarjetas {

    private static final CalcularTiempo tiempo = new CalcularTiempo();
    static Scanner teclado = new Scanner(System.in);
    private static int desglozeArray;
    private static ArrayList<Integer> mainArray = new ArrayList<>();
    private static ArrayList<Integer> subArray = new ArrayList<>();
    static int sumaDeDigitos = 0;

    public static void main(String[] args) {

        System.out.println("Ingrese Numero De Tarjeta ( 16 Digitos )");

        //Desactivado para fines de testeo
        //Long numeroDeTarjeta = Long.valueOf(teclado.nextLong());
        long numeroDeTarjeta = 401085137324153L;

        String numeroDeTarjetaString = Long.toString(numeroDeTarjeta);

        tiempo.init();

        if (numeroDeTarjetaString.matches("^\\d{16}$")){
            System.out.println("La tarjeta es valida");
            System.out.println(numeroDeTarjetaString.length() + "\nLa longitud del primer Numero es : " + numeroDeTarjetaString.length());
        }else{
            System.out.println("La tarjeta es invalida");
        }

        //Funcion para desglozar mi Long (Numero de tarjeta)

        for (int i = 0; i < numeroDeTarjetaString.length(); i++) {
            desglozeArray = numeroDeTarjetaString.charAt(i) - '0';

            System.out.println("Numero la tarjeta " + desglozeArray);
            System.out.println("Numero la tarjeta " + numeroDeTarjetaString.charAt(i));

            //Aqui hace 16 sub arrays y los inserta en el array principal
            mainArray.add(desglozeArray);
            subArray.add(desglozeArray);

            System.out.println("Esto deberia ser 16 : " + mainArray.size());
        }

        MultiplicarDigitos();
        sumarElementos();

        //Funcion para Multiplicar Los digitos (array[i] + 1 (Osea cada 2 digitos))

        tiempo.end();
        tiempo.retornarTiempo();
    }

    private static ArrayList<Integer> MultiplicarDigitos() {

        for (int i = 0; i < mainArray.size(); i+=2) {

            System.out.println("Numero en la lista " + mainArray.get(i));
            Integer multiplicar = mainArray.get(i) * 2;

            System.out.println("El valor multiplicado * 2 Es : " + multiplicar);
            mainArray.set(i,multiplicar);

            if (multiplicar.toString().matches("^\\d{2}$")) {
                System.out.println("El digito es de 2 cifras : " +  multiplicar);
                String valores = multiplicar.toString();
                int valorUNO = valores.charAt(0) - '0';
                int valorDOS = valores.charAt(1) - '0';
                sumaDeDigitos = valorUNO + valorDOS;


                System.out.println("La suma de los dos digitos Dezglosados es : " + sumaDeDigitos);
                mainArray.set(i,sumaDeDigitos);
            }



            //Esto deberia darme todos los numeros segundos del primer array
            // 1234567890123456

            // La salida deberia ser 1 3 5 7 9 1 3 5
            //                     o 2 4 6 8 0 2 4 6
            //System.out.println("Segundo digito es : " + array.get(i));
        }

        return new ArrayList<>();
    }

    private static void sumarElementos(){
        int suma = 0;
        /*for (Integer integer : mainArray) {
        }*/
        for (int i = 0; i < mainArray.size(); i++) {
            suma = suma + mainArray.get(i);
        }
        System.out.println(mainArray.size());
        System.out.println(suma);

    }

    private static void leerMainArray(){
        for (int j = 0; j < mainArray.size(); j++) {
            System.out.println("El mainArray Es : " + mainArray.get(j));
        }
    }
    /* segundo array
    *  salida esperada
    *
    * */


}
