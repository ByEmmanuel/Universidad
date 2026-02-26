package org.Alpha.Sistemas_Op.Programa_03;

/*
* Algoritmo de planificacion FCFS
* Basado en el diagrama de 5 estados
* Se admiten solo 5 estados en pendientes por el procesador
* */

import java.util.*;

public class Programa_03 extends AbstractProcesos implements SoInterface{
    private static ArrayList<Procesos> colaProcesos = new ArrayList<>();
    int contadorGlobalProceos = 0;
    int procesosListos = 5;

    private static void llenarProcesos(int nProcesos){
        // esto esta más facil ahora, solo hay que llenar la cola de procesos y los primeros 5 son en nuevo
        for (int i = 0; i < nProcesos; i++) {
            colaProcesos.add(new Procesos());
        }
    }

    private static void etiquetarProcesos(){
        // etiquetar los primeros 5 con tiempo de llegada de 0
        // y con estados de listo, los demas son nuevos
        // cada 5 procesos se estara
        colaProcesos.sort(Comparator.comparingInt(Procesos::getPID));

        /*
        * Algoritmo
        * Los primeros 5 procesos, tendran etiqueta de listos, listos para ser atendidos pero aun no en ejecucion por el sistema
        * todos los demas tendran etiqueta de "NUEVO"
        * Algunos procesos tendran la etiqueta de ejecucion
        * Algunos procesos tendran la etiqueta de bloqueado ( I/O por el usuario ) y se desbloquearan en 8 ticks de tiempo
        * Algunos procesos tendran la etiqueta de terminado
        * */
    }


    public static void main(String[] args) {

        int nProcesos = 0;
        while (true){
            System.out.println("Ingrese numero de PROCESOS: ");
            try{
                nProcesos = teclado.nextInt();
                if (nProcesos == -1){
                    modoTest();
                }
                if (nProcesos > 0) break;
            } catch (InputMismatchException ex){
                System.out.println("Introduce un numero valido de procesos");
                teclado.next();
            }
        }

        teclado.nextLine();
        llenarProcesos(nProcesos);
        etiquetarProcesos();

    }




    int tiempoDelay = 500;
    private static void modoTest(){
        llenarProcesos(24);
    }
}
