/* Este algoritmo representa la validacion si una tarjeta es valida o no
 *   El uso de este algoritmo es para fines educacionales y eticos y solo se busca aprender
 *   Este algoritmo es famosamente Algoritmo De Lunh, Matematicamente aun no se lo que es
 *
 *   Autor @ByEmmanuelYT
 *   Fecha 28/09/24
 *   Complejidad del algoritmo (Segun yo O(N) o O(log n))
 *   Complejidad del algoritmo segun chatGPT O(1)
 * */

package Algoritmos;

import ONE_Introduccion_A_Java.CalcularTiempo;

import java.util.ArrayList;
import java.util.Scanner;

public class _1_ValidacionDeTarjetas {

    private static final CalcularTiempo tiempo = new CalcularTiempo();
    static Scanner teclado = new Scanner(System.in);
    private static ArrayList<Integer> mainArray = new ArrayList<>();
    static int sumaDeDigitos = 0;

    public static void main(String[] args) {

        System.out.println("Ingrese Numero De Tarjeta ( 16 Digitos )");

        //Desactivado para fines de testeo
        //Long numeroDeTarjeta = Long.valueOf(teclado.nextLong());
        long numeroDeTarjeta = 4208319964063131L;

        String numeroDeTarjetaString = Long.toString(numeroDeTarjeta);

        tiempo.init();
        /*if (numeroDeTarjetaString.contains("\\")) {
            numeroDeTarjetaString = numeroDeTarjetaString.replace(" ", "");
            System.out.println(numeroDeTarjetaString);
        }*/
        /*
         *  Valida Si La Tarjeta es de 16 digitos
         *  en un principio si la tarjeta no es de 16 digitos esto deberia cerrarse o no continuar
         * */
        if (numeroDeTarjetaString.matches("^\\d{16}$")){
            System.out.println("La tarjeta es valida");
            System.out.println(numeroDeTarjetaString.length() + "\nLa longitud del primer Numero es : " + numeroDeTarjetaString.length());
        }else {
            System.out.println("La tarjeta es invalida");
        }

        /* Funcion para desglozar mi Long (Numero de tarjeta)
         *  al buscar un caracter en x posicion, devuelve un caracter ascii
         *  El " - '0' " Se utiliza para convertir los caracteres de ascii a enteros
         *   y se añaden los elementos ya desglozados a un array como 16 subarrays
         * */

        for (int i = 0; i < numeroDeTarjetaString.length(); i++) {
            int desglozeArray = numeroDeTarjetaString.charAt(i) - '0';

            //System.out.println("Numero la tarjeta " + desglozeArray);
            System.out.println("Numero la tarjeta " + numeroDeTarjetaString.charAt(i));

            //Aqui hace 16 sub arrays y los inserta en el array principal
            mainArray.add(desglozeArray);

            //System.out.println("Esto deberia ser 16 : " + mainArray.size());
        }

        MultiplicarDigitos();
        sumarElementos();

        //Metodo utilizado solo para testeo
        //leerMainArray();

        //Funcion para Multiplicar Los digitos (array[i] + 1 (Osea cada 2 digitos))

        tiempo.end();
    }


    /*
     * Esta funcion se utiliza para multiplicar los digitos x 2 cada 2 elementos
     * si el numero es de 2 digitos se suman
     * */
    private static void MultiplicarDigitos() {

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

    }

    /*
     * Esta funcion se utiliza para sumar los elementos de todos los subarrays
     * */
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
    /* segundo array 3312672360047267L
     *  3312 6723 6004 7267
     *  salida esperada
     *  array modificado
     *  3 1 6 2 6 0 7 6
     *  primera leida        Segunda Salida
     *
     *  3 * 2 = 6        3 * 2 = 6
     *  3 * 1 = 3        3 * 1 = 3
     *  1 * 2 = 2        1 * 2 = 2
     *  2 * 1 = 2        2 * 1 = 2
     *
     *  6 * 2 = 12       6 * 2 = 3
     *  7 * 1 = 7        7 * 1 = 7
     *  2 * 2 = 4        2 * 2 = 4
     *  3 * 1 = 3        3 * 1 = 3
     *
     *  6 * 2 = 12       6 * 2 = 3
     *  0 * 1 = 0        0 * 1 = 0
     *  0 * 2 = 0        0 * 2 = 0
     *  4 * 1 = 4        4 * 1 = 4
     *
     *  7 * 2 = 14       7 * 2 = 5
     *  2 * 1 = 2        2 * 1 = 2
     *  6 * 3 = 3        6 * 2 = 3
     *  7 * 1 = 7        7 * 1 = 7
     *                   suma segunda leida 6+3+2+2+3+7+4+3+3+0+0+4+5+2+3+7 =
     * */


}