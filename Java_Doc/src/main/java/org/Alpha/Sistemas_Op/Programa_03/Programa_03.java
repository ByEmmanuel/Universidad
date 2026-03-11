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
import java.util.concurrent.atomic.AtomicBoolean;
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
    static final AtomicBoolean pausado  = new AtomicBoolean(false);
    static final AtomicBoolean terminar = new AtomicBoolean(false);
    private static ArrayList<Procesos> listaTerminados = new ArrayList<>();

    private static final short ticksTiempoMilis = 350;
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

        // llenar la cola de procesos la primera vez
        int pos = 0;

        while (colaListos.size() < 5){
            if (!colaProcesos.isEmpty()){
                Procesos p = colaProcesos.poll();
                colaListos.add(p);
            }
        }

    }

    private static Thread ejecutarProcesosBloqueados = new Thread( () -> {
        
        while (true) {
        //Queue<Procesos> copiaColaBloqueados = new LinkedList<>(colaBloqueados);
            try{
                Thread.sleep(ticksTiempoMilis);
            }catch(InterruptedException ex){
                break;
            };

            synchronized (colaBloqueados){
                Iterator<Procesos> it = colaBloqueados.iterator();
                while(it.hasNext()){
                    Procesos p = it.next();
                    p.setTiempoBloqueado(p.getTiempoBloqueado()-1);
                        if (p.getTiempoBloqueado() <= 0) {
                            it.remove();
                            p.setEstado("Listo");
                            colaListos.add(p);
                        }
                }
            }
            
        }
    });

    /**
     * Cambio de pipeline ->
     * Ahora en el bucle principal del programa se ejecutaran los procesos por medios de "Ticks"
     * Para que los estados de bloqueados se muestren correctamente
     */
    private static void ejecutarProcesos(){
        /**
         * imprimir detalles 
         * Nuevos
         * Listos
         * En ejecucion
         * Bloqueados
         */

        // veamos si funciona
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

        if (p != null){
                p.setEstado("Ejecucion");

                int tiempoEjecucion = p.getTiempoMaxEjecucion();
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
        
            };
            
    
    }    

    private static void tickProcesos(){
        // esta condicional puede ser cambiada a un if
        while (colaListos.size() < 5 && !colaNuevos.isEmpty()) {
                // llenar la cola de listos
                Procesos p = colaNuevos.poll();
                p.setTiempoLlegada(contadorGlobalProcesos);
                p.setEstado("Listo");
                colaListos.add(p);
        }

        Procesos p = enEjecucion.get();
        if (p == null) {
            if (!colaListos.isEmpty()) {
                enEjecucion.set(colaListos.poll());    
            }
            System.out.println("La cola de listos esta vacia");
        }else{
            // ineficiente
            p.setEstado("Ejecucion");

            if (p.getTiempoejecucion() >= p.getTiempoMaxEjecucion()) {
                p.setEstado("Terminado");    
                listaTerminados.add(p);

                // Al terminar un proceso enviamos null para que al siguiente tick se forme un nuevo proceso
                enEjecucion.set(null);
                return;
            }
            p.setTiempoEjecucion(p.getTiempoejecucion()+1);
            
        }
    };



    private static void tickBloqueados(){
        Iterator<Procesos> it = colaBloqueados.iterator();
        while (it.hasNext()) {
            Procesos p = it.next();
            p.setTiempoBloqueado(p.getTiempoBloqueado()-1);
            if (p.getTiempoBloqueado() <= 0) {
                //colaBloqueados.poll();
                it.remove();
                colaListos.add(p);
            }
        }
        
    };

    static synchronized void interrumpirIO(){

        // El proceso en ejecucion se interrumpe
        Procesos bloqueado = enEjecucion.get();
        if (bloqueado == null) {
            System.out.println("NO HAY PROCESOS EN ESTADO DE BLOQUEADOS");
            return;
        }
        enEjecucion.set(null);
        colaBloqueados.add(bloqueado);
        //ej.entroListosEn = reloj.get(); // para calcular espera futura
        
    }

    static String barra(String titulo, String color) {
        return color + BOLD + "══════════════════════════════════════════════════\n"
                + "  " + titulo + "\n"
                + "══════════════════════════════════════════════════" + RESET;
    }

    static volatile char teclaPresionada = 0;
    static void iniciarLectorTeclado() {
        Thread t = new Thread(() -> {
            Scanner sc = new Scanner(System.in);
            while (!terminar.get()) {
                if (sc.hasNextLine()) {
                    String linea = sc.nextLine().trim().toUpperCase();
                    if (!linea.isEmpty()) {
                        teclaPresionada = linea.charAt(0);
                    }
                }
            }
        });
        t.setDaemon(true);
        t.start();
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
        iniciarLectorTeclado();

        //etiquetarProcesos();
        //imprimirProcesos();

        boolean simulacionTerminada = false;
        // !colaNuevos.isEmpty() || !colaListos.isEmpty() || enEjecucion.get() != null || !colaBloqueados.isEmpty()
        //ejecutarProcesosBloqueados.start();
        while (!simulacionTerminada){
            imprimirDetallesProcesos();
            
            try {
                Thread.sleep(ticksTiempoMilis);
            } catch (InterruptedException e) {
                // TODO: handle exception
            }

            char tecla = teclaPresionada;
            teclaPresionada = 0;

            switch (tecla) {
                case 'E': 
                if (pausado.get()) {
                    System.out.println("El sistema esta pausado no se puede bloquear un proceso ");
                    break;
                }else{
                    interrumpirIO();
                    break;
                }
                //case 'W': terminarPorError(); break;
                case 'P': pausado.set(true);  break;
                case 'C': pausado.set(false); break;
            }

            if (!pausado.get()) {
                //ejecutarProcesos();

                tickProcesos();
                tickBloqueados();
            }else{
                // try {
                //     monitor.wait();
                // } catch (InterruptedException e) {
                //     Thread.currentThread().interrupt();
                // }
                continue;
            }

            // if (pausado.get()) {
            //     System.out.println(YELLOW + BOLD + "PAUSADO  presione C + ENTER para continuar" + RESET);
            // }

            boolean todo = colaBloqueados.isEmpty() && colaListos.isEmpty()
            && enEjecucion.get() == null && colaBloqueados.isEmpty();
            if (todo) simulacionTerminada = true;
            contadorGlobalProcesos++;
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


    private static void imprimirDetallesProcesos(){
        clearScreen();

        System.out.println(BOLD + CYAN +
                "╔══════════════════════════════════════════════════╗\n" +
                "║       ALGORITMO           -        FCFS          ║\n" +
                "╚══════════════════════════════════════════════════╝" + RESET);
        System.out.printf(BOLD + "Reloj: %d ticks%s\n", contadorGlobalProcesos, RESET);
        System.out.printf(WHITE + "  Teclas: [E] Bloquear  [W] Error  [P] Pausar  [C] Continuar%s\n\n", RESET);

        // NUEVOS
        System.out.println(barra("COLA DE NUEVOS  (" + colaNuevos.size() + " procesos)", YELLOW));
        if (colaNuevos.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            System.out.printf("  %-6s %-6s %-8s %-10s%n", "PID","TME","Llegada","Operación");
            for (Procesos p : colaNuevos)
                System.out.printf("  %-6d %-6d %-8d %-10s%n", p.getPID(), p.getTiempoMaxEjecucion(), p.getTiempoLlegada(), p.getOperacion());
        }
        System.out.println();

        // Listos
        System.out.println(barra("COLA DE LISTOS  (" + colaListos.size() + " procesos)", GREEN));
        if (colaListos.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            System.out.printf("  %-6s %-6s %-8s %-10s%n", "PID","TME","Llegada","Operación");
            for (Procesos p : colaListos)
                System.out.printf("  %-6d %-6d %-8d %-10s%n", p.getPID(), p.getTiempoMaxEjecucion(), p.getTiempoLlegada(), p.getOperacion());
        }

        // Bloqueados
        System.out.println(barra("COLA DE BLOQUEADOS  (" + colaBloqueados.size() + " procesos)", RED));
        if (!colaBloqueados.isEmpty()) {
            System.out.printf("  %-8s %-6s %-6s %-8s %-10s%n", "T.Bloqueado", "PID", "TME", "Llegada", "Estado");
            for (Procesos p : colaBloqueados) {
                if (p != null) {
                    p.setEstado("BLOQUEADO");
                    System.out.printf("  %-8d %-8d %-11d %-13d %-15s%n",
                        p.getTiempoBloqueado(),
                        p.getPID(),
                        p.getTiempoMaxEjecucion(),
                        p.getTiempoLlegada(),
                        p.getEstado()
                    );
                }
            }
        }


        System.out.println();

        // Terminados
        System.out.println(barra("PROCESOS TERMINADOS", PURPLE));
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
            System.out.printf("  %-6d %-6d %-8d %-10s%n", p.getPID(), p.getTiempoMaxEjecucion(), p.getTiempoLlegada(), p.getOperacion());
        }
        


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