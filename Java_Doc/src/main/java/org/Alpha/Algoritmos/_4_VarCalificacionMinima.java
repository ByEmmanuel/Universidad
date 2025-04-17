package org.Alpha.Algoritmos;

import java.util.*;

public class _4_VarCalificacionMinima {
    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
        Map<String, Integer> tabla = new HashMap<>();
        ArrayList<Integer> lista = new ArrayList<>();

        boolean bandera = false;
        int total = 0;

        if (!bandera){
            tabla.put("Examenes",40);
            tabla.put("Tareas",40);
            tabla.put("Exposicion",10);
            tabla.put("Portafolio",10);
        }

        while(bandera){
            if (total != 100 && total < 101) {
                System.out.println("Ingrese Criterio: ");
                String var1 = teclado.next();
                System.out.println("Ingrese Porcentaje");
                Integer var2 = teclado.nextInt();

                total = total + var2;
                lista.add(var2);
                tabla.put(var1,var2);
            }else {
                bandera = false;
            }

            System.out.println("El total es: " + total);

        };

        /*for (Integer i : lista){
            System.out.println(i);
        }

        for (Map.Entry<String, Integer> entrada : tabla.entrySet()) {
            System.out.println(entrada.getKey() + ": " + entrada.getValue());
        }*/
        //Integer calificacionMinima = teclado.nextInt();
        Map<String, List<Integer>> combinaciones = generarFactores(tabla, 60);

        for (Map.Entry<String, List<Integer>> objeto : combinaciones.entrySet()){
            System.out.println("Valores De los factores; " + objeto);
        }
    }

    private static Map<String, List<Integer>> generarFactores(Map<String, Integer> tabla, int calificacionMinima){

        Map<String, List<Integer>> tabla2 = new Hashtable<>();
        for (Map.Entry<String, Integer> entrada : tabla.entrySet()) {
            List<Integer> factores = new ArrayList<>();
            for (int i = entrada.getValue(); i > 0; i = i - 5){
                tabla2.put(entrada.getKey(), factores);
                factores.add(i);
            }


            System.out.println(entrada.getKey() + ": " + entrada.getValue());

        }

        /*
        * Crear una funcion que de los factoresCompletos de el valor del criterio x
        * es decir para 40
        * 35 , 30 , 25 , 20 , 15 , 10 ... , 0;
        * Esos numeros meterlos en otro array con el valor previo de la llave (Criterio)
        *
        * ahora tendre
        * Criterio ;
        * x1 : 40
        * x1 : 35
        * x1 : 30
        * ...
        * x1 : 0
        * */

        //buscarCombinaciones(lista, calificacionMinima);

        return tabla2;
    }

    private static void buscarCombinaciones(List<HashMap<String, Integer>> lista, Integer calificacionMinima){

    }

}
