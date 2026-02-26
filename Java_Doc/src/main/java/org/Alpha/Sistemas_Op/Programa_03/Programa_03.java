//package org.Alpha.Sistemas_Op.Programa_03;

/*
* Algoritmo de planificacion FCFS
* Basado en el diagrama de 5 estados
* Se admiten solo 5 estados en pendientes por el procesador
* */

import java.util.*;

class Tiempo {
    private long inicio = 0;
    private long fin = 0;

    public void init() { inicio = System.nanoTime(); }
    public void end() { fin = System.nanoTime(); }
    public long calculateTime_milis() {
        return (long) ((fin - inicio) / 1_000_000.0);
    }
}

public class Programa_03 extends AbstractProcesos implements SoInterface{
    private static ArrayList<Procesos> colaProcesos = new ArrayList<>();
    private static ArrayDeque<Procesos> colaProcesosPrioritario = new ArrayDeque<>();
    private static final short ticksTiempoMilis = 300;
    private static int tiempoTranscurridoTicks= 0;
    private static int indiceParaNuevos = 0;
    int contadorGlobalProceos = 0;
    int procesosListos = 5;

    private static void llenarProcesos(int nProcesos){
        // esto esta más facil ahora, solo hay que llenar la cola de procesos y los primeros 5 son en nuevo
        //esto les va a poner "Nuevo" a todos los procesos
        for (int i = 0; i < nProcesos; i++) {
            Procesos p = new Procesos();
            colaProcesos.add(p);
            p.setEstado("Nuevo");
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
        // Esto le pone "Listo" solo al numero de procesosPrioritarios; = 5
        int procesosPrioritarios = 5;
        for (int i = 0; i < procesosPrioritarios; i++) {
            if (i < colaProcesos.size()){
                Procesos p = colaProcesos.get(i);
                p.setEstado("Listo");
                colaProcesosPrioritario.addLast(p);
            }
        }
    }

    private static void ejecutarProcesos(){

        while (!colaProcesosPrioritario.isEmpty()){
            // actualizar el tiempo gloobal
            //
            tiempoTranscurridoTicks+=ticksTiempoMilis;
            clearScreen();
            imprimirProcesos();
            try{Thread.sleep(ticksTiempoMilis);}catch (InterruptedException ex){
                System.out.println("Ocurrio un problema en el hilo");}

            Procesos p = colaProcesosPrioritario.getFirst();
            p.setEstado("Ejecucion");
            p.setTiempoMax(p.getTiempoMax()-1);

            if (p.getTiempoMax() <= 0){
                p.setEstado("Terminado");
                colaProcesosPrioritario.removeFirst();

                //inentar guardar el indice para acceder a la colaProcesos por el indice
                for (Procesos pp: colaProcesos){
                    if (pp.getEstado().contains("Nuevo")){
                        colaProcesosPrioritario.add(pp);
                        // break del segundo bucle a la primera coincidencia con "Nuevo"
                        break;
                    }
                }
            }

        }


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
        imprimirProcesos();
        ejecutarProcesos();

    }

    private static void imprimirProcesos(){
        for (Procesos p: colaProcesos){
            System.out.printf("\nPID: %d | TME: %d | Operacion: %s | Valor A: %d, Valor B: %d | Estado: %s"
                    ,p.getPID(), p.getTiempoMax(), p.getOperacion(), p.getOperadores()[0], p.getOperadores()[1], p.getEstado());
        }
    }

    static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    int tiempoDelay = 500;
    private static void modoTest(){
        llenarProcesos(24);
    }


}
