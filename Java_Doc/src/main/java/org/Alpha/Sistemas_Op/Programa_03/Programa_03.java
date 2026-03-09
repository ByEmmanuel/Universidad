package org.Alpha.Sistemas_Op.Programa_03;


/*
* Algoritmo de planificacion FCFS
* Basado en el diagrama de 5 estados
* Se admiten solo 5 estados en pendientes por el procesador
* */


/**
 * Pipeline de ejecucion
 * El usuario ingresa numero de procesos a ejecutar
 * Se crean -> se asignan sus atributos corresponientes
 * Se ordenan 
 * Se ingresan todos a una cola "A"
 * Solo 5 procesos de esa cola "A", pasan a la cola "B" y esos mismos se elminan de la cola A
 * Cada que termina un proceso de la cola "A",
 *       ingresa un proceso de la cola B con el tiempo de llegada = contador global (Reloj)
 * 
 * Se muestran los 5 estados por pantalla en secciones
 * 
 * Nuevos pero no admitidos por el procesador
 * Listos para ser ejecutados 
 * En ejecucion
 * Bloqueado
 * Interrupcion
 * Procesos terminados
 * 
 */

import java.util.*;
import java.util.concurrent.atomic.AtomicReference;



public class Programa_03 extends AbstractProcesos implements SoInterface{

    /**
     * COLORES
     * 
     */
    static final String RESET  = "\033[0m";
    static final String BOLD   = "\033[1m";
    static final String CYAN   = "\033[36m";
    static final String GREEN  = "\033[32m";
    static final String YELLOW = "\033[33m";
    static final String RED    = "\033[31m";
    static final String BLUE   = "\033[34m";
    static final String PURPLE = "\033[35m";
    static final String WHITE  = "\033[37m";

    private static final Object monitor = new Object();
    private static volatile boolean pausa = false;



    private static PriorityQueue<Procesos> colaNuevos = new PriorityQueue<>(
            Comparator.comparingInt(Procesos::getPID)
    );
    private static Queue<Procesos> colaListos = new LinkedList<>();
    private static Queue<Procesos> colaBloqueados = new LinkedList<>();
    private static AtomicReference<Procesos> enEjecucion = new AtomicReference<>();
    private static ArrayList<Procesos> listaTerminados = new ArrayList<>();

    private static final short ticksTiempoMilis = 300;
    private static int indiceParaNuevos = 0;
    private static int contadorGlobalProcesos = 0;
    private static int procesosListos = 5;



    // definitivo
    private static void llenarProcesos(int nProcesos){
        // esto esta más facil ahora, solo hay que llenar la cola de procesos y los primeros 5 son en nuevo
        //esto les va a poner "Nuevo" a todos los procesos
        for (int i = 0; i < nProcesos; i++) {
            Procesos p = new Procesos();
            p.setEstado("Nuevo");
            colaNuevos.add(p);
        }
    }

    // Solo se va a ejecutar los 5 procesos admitidos por el procesador
    private static void etiquetarProcesos(){
        // etiquetar los primeros 5 con tiempo de llegada de 0
        // y con estados de listo, los demas son nuevos
        // cada 5 procesos se estara

        /*
        * Algoritmo
        * Los primeros 5 procesos, tendran etiqueta de listos, listos para ser atendidos pero aun no en ejecucion por el sistema
        * todos los demas tendran etiqueta de "NUEVO"
        * Algunos procesos tendran la etiqueta de ejecucion
        * Algunos procesos tendran la etiqueta de bloqueado ( I/O por el usuario ) y se desbloquearan en 8 ticks de tiempo
        * Algunos procesos tendran la etiqueta de terminado
        * */
        // Esto le pone "Listo" solo al numero de procesosPrioritarios; = 5

        // int procesosPrioritarios = 5;
        // for (int i = 0; i < procesosPrioritarios; i++) {
        //     if (i < colaProcesos.size()){
        //         Procesos p = colaProcesos.get(i);
        //         p.setEstado("Listo");
        //         colaProcesosPrioritario.addLast(p);
        //     }
        // }

        // llenar la cola de procesos la primera vez
        int pos = 0;

        while (colaListos.size() < 5){
            if (!colaProcesos.isEmpty()){
                Procesos p = colaProcesos.poll();
                colaListos.add(p);
            }
        }

    }

    // private static void ejecutarProcesos(){

    //     while (!colaProcesosPrioritario.isEmpty()){
    //         clearScreen();
    //         imprimirProcesos();
    //         try{Thread.sleep(ticksTiempoMilis);}catch (InterruptedException ex){
    //             System.out.println("Ocurrio un problema en el hilo");}

    //         Procesos p = colaProcesosPrioritario.getFirst();
    //         p.setEstado("Ejecucion");
    //         p.setTiempoMax(p.getTiempoMax()-1);

    //         if (p.getTiempoMax() <= 0){
    //             p.setEstado("Terminado");
    //             colaProcesosPrioritario.removeFirst();

    //             //inentar guardar el indice para acceder a la colaProcesos por el indice
    //             for (Procesos pp: colaProcesos){
    //                 if (pp.getEstado().contains("Nuevo")){
    //                     colaProcesosPrioritario.add(pp);
    //                     // break del segundo bucle a la primera coincidencia con "Nuevo"
    //                     break;
    //                 }
    //             }
    //         }

    //     }
    // }

    private static void ejecutarProcesos(){
        /**
         * imprimir detalles 
         * Nuevos
         * Listos
         * En ejecucion
         * Bloqueados
         */
        while (!colaNuevos.isEmpty() || !colaListos.isEmpty() || enEjecucion.get() != null || !colaBloqueados.isEmpty()){
            while (colaListos.size() <= 5 && !colaNuevos.isEmpty()) {
                // llenar la cola de listos
                Procesos p = colaNuevos.poll();
                p.setTiempoLlegada(contadorGlobalProcesos);
                p.setEstado("Listo");
                colaListos.add(p);
            }
            //Procesos p = colaListos.poll();
            enEjecucion.set(colaListos.poll());
            Procesos p = enEjecucion.get();

            if (p == null) continue;
            p.setEstado("Ejecucion");

            int tiempoEjecucion = p.getTiempoMax();
            while (tiempoEjecucion > 0) {
                imprimirDetallesProcesos();
                try {
                    Thread.sleep(ticksTiempoMilis);
                } catch (InterruptedException e) {
                    // TODO: handle exception
                    Thread.currentThread().interrupt();
                }
                tiempoEjecucion--;
                contadorGlobalProcesos++;
            }

            // ya acabo de procesar
            p.setEstado("Terminado");
            listaTerminados.add(p);
            enEjecucion.set(null);
        }
    }    

    static String barra(String titulo, String color) {
        return color + BOLD + "══════════════════════════════════════════════════\n"
                + "  " + titulo + "\n"
                + "══════════════════════════════════════════════════" + RESET;
    }

    private static void imprimirDetallesProcesos(){
        clearScreen();

        System.out.println(BOLD + CYAN +
                "╔══════════════════════════════════════════════════╗\n" +
                "║       ALGORITMO           -        FCFS          ║\n" +
                "╚══════════════════════════════════════════════════╝" + RESET);
        System.out.printf(BOLD + "  🕐 Reloj: %d ticks%s\n", contadorGlobalProcesos, RESET);
        System.out.printf(WHITE + "  Teclas: [E] Bloquear  [W] Error  [P] Pausar  [C] Continuar%s\n\n", RESET);

        // NUEVOS
        System.out.println(barra("🆕 COLA DE NUEVOS  (" + colaNuevos.size() + " procesos)", YELLOW));
        if (colaNuevos.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            System.out.printf("  %-6s %-6s %-8s %-10s%n", "PID","TME","Llegada","Operación");
            for (Procesos p : colaNuevos)
                System.out.printf("  %-6d %-6d %-8d %-10s%n", p.getPID(), p.getTiempoMax(), p.getTiempoLlegada(), p.getOperacion());
        }
        System.out.println();

        // Listos
        System.out.println(barra("📋 COLA DE LISTOS  (" + colaListos.size() + " procesos)", GREEN));
        if (colaListos.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            System.out.printf("  %-6s %-6s %-8s %-10s%n", "PID","TME","Llegada","Operación");
            for (Procesos p : colaListos)
                System.out.printf("  %-6d %-6d %-8d %-10s%n", p.getPID(), p.getTiempoMax(), p.getTiempoLlegada(), p.getOperacion());
        }
        System.out.println();

        // Terminados
        System.out.println(barra("✅ PROCESOS TERMINADOS", PURPLE));
        if (listaTerminados.isEmpty()) {
            System.out.println("  (ninguno)");
        } else {
            System.out.printf("  %-6s %-14s %-8s%n", "PID","Operación","Resultado");
            for (Procesos p : listaTerminados)
                System.out.printf("  %-6d %-14s %-8s%n", p.getPID(), p.getOperacion(), p.getEstado());
        }

        // En ejecucion
        System.out.println(
            barra("En ejecucion", RED)
            );    

        Procesos p = enEjecucion.get();
        if (enEjecucion.get() == null) {
            System.out.println("No hay proceso en ejecucion");
        }else{
            System.out.printf("  %-6s %-6s %-8s %-10s%n", "PID","TME","Llegada","Operación");
            System.out.printf("  %-6d %-6d %-8d %-10s%n", p.getPID(), p.getTiempoMax(), p.getTiempoLlegada(), p.getOperacion());
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
        //etiquetarProcesos();
        //imprimirProcesos();
        ejecutarProcesos();

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

class Tiempo {
    private long inicio = 0;
    private long fin = 0;

    public void init() { inicio = System.nanoTime(); }
    public void end() { fin = System.nanoTime(); }
    public long calculateTime_milis() {
        return (long) ((fin - inicio) / 1_000_000.0);
    }
}