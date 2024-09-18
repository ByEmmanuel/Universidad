//Este es el paquete donde se encuentra la clase Java (Es decir, esta clase)
package ONE_Introduccion_A_Java;

/**
 *  Descripción: Este es un programa de prueba para aprender las bases de JAVA
 *  Y PRINCIPALMENTE ESTA DISEÑADO PARA APRENDER JAVA Y C++, A la vez que aprendemos para no confundirn conceptos
 *  entre los dos lenguajes de programación
 *
 *  Fecha de creación: 10/09/2024
 *  Autor: @ByEmmanuel
 */


public class _1_PrimerTest {
    public static void main(String[] args) {

        CalcularTiempo calcularTiempo = new CalcularTiempo();
        calcularTiempo.init();

        System.out.println("Hello world!");

        System.out.println("Suma " + suma(2, 6));
        System.out.println("Resta " + resta(2, 6));
        System.out.println("Multiplicación " + multiplicacion(2, 6));
        System.out.println("División " + division(6, 2));

        calcularTiempo.end();
        calcularTiempo.retornarTiempo();
        
    }

    private static int suma(int a, int b){
        return a + b;
    }
    private static int resta(int a, int b){
        return a - b;
    }
    private static int multiplicacion(int a, int b){
        return (a * b);
    }
    private static int division(int a, int b){
        return  (a/b);
    }
}


