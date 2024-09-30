package ONE_Introduccion_A_Java;

/*
*  Quinto Archivo
* Nombre: Operadores Y Operadores Matematicos
* Autor: ByEmmanuel
* Fecha: 25-09-2024
* Descripcion: Tipos de Operadores en Java
* Los operadores son simbolos que permiten realizar operaciones sobre variables y valores
* Los operadores en C++ se dividen en varios tipos:
*  - aritmeticos,
*  - relacionales,
*  - logicos,
*  - de asignacion,
*  - de incremento y decremento,
*  - de bits
*  - y condicionales
*/


public class _5_Operadoeres {

    private static CalcularTiempo tiempo = new CalcularTiempo();

    public static void main(String[] args) {

        tiempo.init();
        
        // Operadores Aritmeticos
        int a = 10;
        int b = 20;
        int c = 25;
        int d = 25;
        
        System.out.println("Operadores Aritmeticos\n");
        System.out.println("a + b = " + (a + b) );
        System.out.println("a - b = " + (a - b) );
        System.out.println("a * b = " + (a * b) );
        System.out.println("b / a = " + (b / a) );
        System.out.println("b % a = " + (b % a) );
        System.out.println("c % a = " + (c % a) );
        
        // Operadores Relacionales
        System.out.println("\nOperadores Relacionales\n");
        System.out.println("a == b = " + (a == b) );
        System.out.println("a != b = " + (a != b) );
        System.out.println("a > b = " + (a > b) );
        System.out.println("a < b = " + (a < b) );
        System.out.println("b >= a = " + (b >= a) );
        System.out.println("b <= a = " + (b <= a) );
        
        // Operadores Logicos
        boolean x = true;
        boolean y = false;
        
        System.out.println("\nOperadores Logicos\n");
        System.out.println("x && y = " + (x&&y) );
        System.out.println("x || y = " + (x||y) );
        System.out.println("!(x && y) = " + !(x&&y) );
        
        // Operadores de Asignacion
        System.out.println("\nOperadores de Asignacion\n");
        a += b;
        System.out.println("a += b = " + a );
        a -= b;
        System.out.println("a -= b = " + a );
        a *= b;
        System.out.println("a *= b = " + a );
        a /= b;
        System.out.println("a /= b = " + a );
        a %= b;
        System.out.println("a %= b = " + a );
        
        // Operadores de Incremento y Decremento
        a = 10;
        b = 100;
        
        System.out.println("\nOperadores de Incremento y Decremento\n");
        System.out.println("a++ = " + (a++) );
        System.out.println("b-- = " + (b--) );
        
        // Operadores de Bits
        a = 60; /* 60 = 0011
                    1100 */
        b = 13; /* 13 = 0000
                    1101 */
        c = 0; 

        c = a & b; /* 12 = 0000
                        1100 */
        System.out.println("\nOperadores de Bits\n");
        System.out.println("a & b = " + c );

        c = a | b; /* 61 = 0011
                        1101 */
        System.out.println("a | b = " + c );

        c = a ^ b; /* 49 = 0011
                        0001 */
        System.out.println("a ^ b = " + c );

        c = ~a; /* -61 = 1100
                        0011 */
        System.out.println("~a = " + c );

        tiempo.end();
        tiempo.retornarTiempo();

    }
    
}
