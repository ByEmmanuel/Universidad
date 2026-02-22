//package org.Alpha.Sistemas_Op.Programa_02;

/*
* Programa 2. Simular el procesamiento por lotes con Multiprogramación.
* */

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Scanner;

public class Programa_02 {
    private static ArrayDeque<Lotes> colaLotes = new ArrayDeque<>();
    private static ArrayList<String> procesosCompletados = new ArrayList<>();

    private static void llenarProcesos(int numProcesos){

        int contadorProcesos = 0;
        int numProcesosPorLote = 5;

        Lotes l = new Lotes();
        ArrayList<Procesos> procesos = new ArrayList<>();

        int lotes = Math.floorDiv(numProcesos, numProcesosPorLote);

        int procesosPares = lotes * numProcesosPorLote;

        for (int i = 0; i < lotes; i++) {
            for (int j = 0; j < numProcesosPorLote; j++) {
                procesos.add(new Procesos());

                clearScreen();


                for (Procesos p : procesos){
                    System.out.printf("\nProceso N: %d || Tiempo estimado: %d || Operacion: %s || Valor A: %d || Valor B: %d",p.getPID(), p.getTiempoMax(), p.getOperacion(), p.getValores()[0], p.getValores()[1]);
                }


                try { Thread.sleep((int) ( Math.random()  * 1400 )); } catch (InterruptedException e) { }
                contadorProcesos++;
            }
            l.setListaProcesos(procesos);
            colaLotes.add(l);
            // cambiar el puntero de datos
            l = new Lotes();
            procesos = new ArrayList<>();
        }
        mostrarProcesosEnCola();

        if (contadorProcesos < numProcesos){
            // esto es menor que numProcesosPorLote
            procesos = new ArrayList<>();
            for (int i = contadorProcesos; i < numProcesos; i++) {
                procesos.add(new Procesos());
            }
            Lotes l_2 = new Lotes();
            l_2.setListaProcesos(procesos);
            colaLotes.add(l_2);
        }

        ordenarProcesos();
    }

    private static void ordenarProcesos(){
        int contadorLotes = 0;
        for (Lotes l : colaLotes){
            System.out.printf("\nLote numero : %d \n", contadorLotes);
            l.ordenarProcesos();
            l.comprobarOrdenamiento();
            contadorLotes++;
        }
    }

    private static void ejecutarProcesos(){
        for (Lotes l : colaLotes){
            for(Procesos p : l.getListaProcesos()){
                p.run();
                //System.out.println(p.getResultado_operacion());
            }
        }
    }

    public static void mostrarProcesosEnCola(){
        clearScreen();
        for (Lotes l : colaLotes){
            ArrayList<Procesos> lista = l.getListaProcesos();
            for (Procesos p : lista){
                // limpiar la pantalla, mostrar procesos acumulandose
                System.out.printf("\nProceso N: %d || Tiempo estimado: %d || Operacion: %s || Valor A: %d || Valor B: %d",p.getPID(), p.getTiempoMax(), p.getOperacion(), p.getValores()[0], p.getValores()[1]);
            }
        }
    }

    // Limpia la terminal en Arch Linux / Bash
    static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    public static void main(String[] args) {

        Scanner teclado = new Scanner(System.in);


        int numProcesos;


        while (true){
            try {
                System.out.println("Introduce numero de procesos: ");
                numProcesos = teclado.nextInt();
                if (numProcesos > 0) break;
            }catch (RuntimeException e){
                System.out.println("Introduce un numero valido de procesos");
                teclado.next();
            }
        }

        llenarProcesos(numProcesos);
        ejecutarProcesos();

        //System.out.println(numProcesos);
    }
}