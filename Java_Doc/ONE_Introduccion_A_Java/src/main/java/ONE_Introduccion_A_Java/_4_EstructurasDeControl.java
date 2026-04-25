package src.main.java.ONE_Introduccion_A_Java;

/*
 *  Cuarto Archivo
 * Nombre: Tipos De Estructuras De Control
 * Autor: ByEmmanuel
 * Fecha: 20-09-2024
 * Descripcion: Tipos de Estructuras de control en Java
 * Estas estructuras de control definen para donde debe ir el rumbo del programa
 *
 */


public class _4_EstructurasDeControl {

    //Estructuras de control en Java

    //Definimos una variable global para el documento pero solo visible para el mismo el cual sera un array y le pasare slos valores mediante acceso a su indice
    private static final int[] arrayList = {1,2,3,4,5,6,7,8,9};

    public static void main(String[] args) {

        estructura_If(arrayList[0], arrayList[4]);
        estructura_SwitchCase(arrayList);
        estructura_For(arrayList);
        estructura_While();
        estructura_TryCatch();

    }



    //Si le pongo return el codigo hasta ahi se detiene
    //En cambio si no le pongo return se ejecutara todo bloque de codigo
    private static int estructura_If(int num1, int num2){

        //Estructura de control If

        if(num1 == num2){
            //Esto no se ejecuta
            System.out.println("Es verdadero");
            return 1;
        }else{
            if (num1 < num2){
                System.out.println("El numero es mayor");
                return 2;
            }
            if (num1 + 4 == num2){
                System.out.println("El numero es igual");
                return 3;
            }
            System.out.println("El nummero no es igual ");
            return 0;
        }

        
    }


    private static void estructura_SwitchCase(int[] array) {
    
        //Estructura de control Switch Case Que ejecutara el 4to caso

        switch (array[3]){
            case 1:
                System.out.println("El numero es 1");
                break;
            case 2:
                System.out.println("El numero es 2");
                break;
            case 3:
                System.out.println("El numero es 3");
                break;
            case 4:
                System.out.println("El numero es 4");
                break;
            default:
                System.out.println("El numero no es ninguno de los anteriores");
                break;
        }


    }

    private static void estructura_For(int [] array) {

        //Estructura de control For

        for (int i = 0; i < array.length; i++){
            System.out.println("El valor del array en la posicion " + i + " es: " + array[i]);
        }

        //For each 

        for (int i : array) {
            System.out.println("El valor del array es: " + i);
        }

    }

    private static void estructura_While() {
    
        //Estructura de control While

        int i = 0;

        // while (i < arrayList.length){
        //     System.out.println("El valor del array en la posicion " + i + " es: " + arrayList[i]);
        //     i++;
        // }

        do {
            System.out.println("El valor del array en la pos " + i + " es: " + arrayList[i]);
            i++;
        } while (i < arrayList.length);

    }



    private static void estructura_TryCatch(){

        //Estructura de control Try Catch

        try {
            int num = 10/0;
            System.out.println("El resultado de la division es: " + num);
        } catch (Exception e) {
            System.out.println("No se puede dividir por 0");
        }finally{
            System.out.println("Esto se ejecutara siempre");
        }

    }

}
