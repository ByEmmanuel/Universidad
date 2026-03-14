package org.Alpha.Sistemas_Op.Programa_03;

import java.io.FileInputStream;
import java.util.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;

public class Programa_03 extends AbstractProcesos implements SoInterface {

    // ── Colores ───────────────────────────────────────────────────────────────
    static final String RESET  = "\033[0m";
    static final String BOLD   = "\033[1m";
    static final String CYAN   = "\033[36m";
    static final String GREEN  = "\033[32m";
    static final String YELLOW = "\033[33m";
    static final String RED    = "\033[31m";
    static final String BLUE   = "\033[34m";
    static final String PURPLE = "\033[35m";
    static final String WHITE  = "\033[37m";

    // ── Colas ─────────────────────────────────────────────────────────────────
    private static PriorityQueue<Procesos> colaNuevos = new PriorityQueue<>(
            Comparator.comparingInt(Procesos::getPID)
    );
    private static Queue<Procesos>           colaListos    = new LinkedList<>();
    private static Queue<Procesos>           colaBloqueados= new LinkedList<>();
    private static AtomicReference<Procesos> enEjecucion   = new AtomicReference<>();
    private static ArrayList<Procesos>       listaTerminados = new ArrayList<>();

    // ── Control ───────────────────────────────────────────────────────────────
    static final AtomicBoolean pausado  = new AtomicBoolean(false);
    static final AtomicBoolean terminar = new AtomicBoolean(false);
    static volatile char teclaPresionada = 0;

    private static final short ticksTiempoMilis      = 350;
    private static int         contadorGlobalProcesos = 0;

    // ── Llenar cola de nuevos ─────────────────────────────────────────────────
    private static void llenarProcesos(int nProcesos) {
        for (int i = 0; i < nProcesos; i++) {
            Procesos p = new Procesos();
            p.setEstado("Nuevo");
            colaNuevos.add(p);
        }
    }

    // ── Tick principal: admitir, despachar, ejecutar ──────────────────────────
    private static void tickProcesos() {
        // Admitir nuevos → listos (máx 4 en memoria: listos + ejecucion + bloqueados)
        while (colaListos.size() <= 5 && !colaNuevos.isEmpty()) {
            int enMemoria = colaListos.size()
                          + colaBloqueados.size()
                          + (enEjecucion.get() != null ? 1 : 0);
            if (enMemoria >= 5) break;
            Procesos p = colaNuevos.poll();
            p.setTiempoLlegada(contadorGlobalProcesos);
            p.setTickEntroListos(contadorGlobalProcesos);
            p.setEstado("Listo");
            colaListos.add(p);
        }

        Procesos p = enEjecucion.get();

        // Despachar si no hay proceso en ejecución
        if (p == null && !colaListos.isEmpty()) {
            p = colaListos.poll();

            // Acumular tiempo de espera desde que entró a listos
            p.acumularEspera(contadorGlobalProcesos - p.getTickEntroListos());

            // Registrar primera atención (tiempo de respuesta)
            if (p.isPrimeraVez()) {
                p.setTRespuesta(contadorGlobalProcesos - p.getTiempoLlegada());
                p.setPrimeraVez(false);
            }

            p.setEstado("Ejecucion");
            enEjecucion.set(p);
        }

        // Avanzar ejecución
        if (p != null) {
            p.setEstado("Ejecucion");
            p.setTiempoEjecucion(p.getTiempoejecucion() + 1);

            if (p.getTiempoejecucion() >= p.getTiempoMaxEjecucion()) {
                // Terminó normalmente
                p.setTFinalizacion(contadorGlobalProcesos + 1);
                p.setEstado("Terminado");
                listaTerminados.add(p);
                enEjecucion.set(null);
            }
        }
    }

    // ── Tick bloqueados ───────────────────────────────────────────────────────
    private static void tickBloqueados() {
        Iterator<Procesos> it = colaBloqueados.iterator();
        while (it.hasNext()) {
            Procesos p = it.next();
            p.setTiempoBloqueado(p.getTiempoBloqueado() - 1);
            if (p.getTiempoBloqueado() <= 0) {
                it.remove();
                p.setTiempoBloqueado(8);       // resetear para futuros bloqueos
                p.setTickEntroListos(contadorGlobalProcesos);
                p.setEstado("Listo");
                colaListos.add(p);
            }
        }
    }

    // ── Interrupciones ────────────────────────────────────────────────────────
    static synchronized void interrumpirIO() {
        Procesos bloqueado = enEjecucion.get();
        if (bloqueado == null) return;
        enEjecucion.set(null);
        bloqueado.setTiempoBloqueado(8);
        bloqueado.setEstado("Bloqueado");
        colaBloqueados.add(bloqueado);
    }

    static synchronized void terminarPorError() {
        Procesos p = enEjecucion.get();
        if (p == null) return;
        enEjecucion.set(null);
        p.setTerminadoPorError(true);
        p.setTFinalizacion(contadorGlobalProcesos);
        p.setEstado("Terminado");
        listaTerminados.add(p);
    }

    // ── Raw mode ──────────────────────────────────────────────────────────────
    private static void activarRawMode() throws Exception {
        new ProcessBuilder("/bin/sh", "-c", "stty -icanon -echo < /dev/tty")
                .inheritIO().start().waitFor();
    }

    private static void desactivarRawMode() throws Exception {
        new ProcessBuilder("/bin/sh", "-c", "stty sane < /dev/tty")
                .inheritIO().start().waitFor();
    }

    private static void iniciarLectorTecladoFileInput() {
        Thread hilo = new Thread(() -> {
            try {
                FileInputStream sc = new FileInputStream("/dev/tty");
                while (!terminar.get()) {
                    int c = sc.read();
                    if (c == -1) break;
                    teclaPresionada = Character.toUpperCase((char) c);
                }
                sc.close();
            } catch (Exception ignored) {}
        });
        hilo.setDaemon(true);
        hilo.start();
    }

    // ── Impresión ─────────────────────────────────────────────────────────────
    static String barra(String titulo, String color) {
        return color + BOLD
                + "══════════════════════════════════════════════════\n"
                + "  " + titulo + "\n"
                + "══════════════════════════════════════════════════" + RESET;
    }

    static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    private static void imprimirDetallesProcesos() {
        clearScreen();

        System.out.println(BOLD + CYAN +
                "╔══════════════════════════════════════════════════╗\n" +
                "║         ALGORITMO  -  FCFS  -  5 ESTADOS        ║\n" +
                "╚══════════════════════════════════════════════════╝" + RESET);
        System.out.printf(BOLD + "  Reloj: %d ticks%s\n", contadorGlobalProcesos, RESET);
        System.out.printf(WHITE + "  [E] Bloquear  [W] Error  [P] Pausar  [C] Continuar%s\n\n", RESET);

        if (pausado.get())
            System.out.println(RED + BOLD + "  ⏸  SISTEMA PAUSADO — presione C para continuar\n" + RESET);

        // NUEVOS
        System.out.println(barra("COLA DE NUEVOS  (" + colaNuevos.size() + " procesos)", YELLOW));
        if (colaNuevos.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            System.out.printf("  %-6s %-6s %-8s %-14s%n", "PID", "TME", "Llegada", "Operación");
            for (Procesos p : colaNuevos)
                System.out.printf("  %-6d %-6d %-8d %-14s%n",
                        p.getPID(), p.getTiempoMaxEjecucion(),
                        p.getTiempoLlegada(), p.getOperacionCompleta());
        }
        System.out.println();

        // LISTOS
        System.out.println(barra("COLA DE LISTOS  (" + colaListos.size() + " procesos)", GREEN));
        if (colaListos.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            System.out.printf("  %-6s %-6s %-8s %-12s %-14s%n",
                    "PID", "TME", "Llegada", "T.Ejecutado", "Operación");
            for (Procesos p : colaListos)
                System.out.printf("  %-6d %-6d %-8d %-12d %-14s%n",
                        p.getPID(), p.getTiempoMaxEjecucion(),
                        p.getTiempoLlegada(), p.getTiempoejecucion(),
                        p.getOperacionCompleta());
        }
        System.out.println();

        // BLOQUEADOS
        System.out.println(barra("COLA DE BLOQUEADOS  (" + colaBloqueados.size() + " procesos)", RED));
        if (colaBloqueados.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            System.out.printf("  %-10s %-6s %-6s %-8s%n", "T.Bloqueado", "PID", "TME", "Llegada");
            for (Procesos p : colaBloqueados) {
                if (p != null)
                    System.out.printf("  %-10d %-6d %-6d %-8d%n",
                            p.getTiempoBloqueado(), p.getPID(),
                            p.getTiempoMaxEjecucion(), p.getTiempoLlegada());
            }
        }
        System.out.println();

        // EN EJECUCIÓN
        System.out.println(barra("EN EJECUCIÓN", CYAN));
        Procesos ej = enEjecucion.get();
        if (ej == null) {
            System.out.println("  (ninguno)");
        } else {
            System.out.printf("  PID          : %d%n",  ej.getPID());
            System.out.printf("  Operación    : %s%n",  ej.getOperacionCompleta());
            System.out.printf("  TME          : %d%n",  ej.getTiempoMaxEjecucion());
            System.out.printf("  T.Ejecutado  : %d%n",  ej.getTiempoejecucion());
            System.out.printf("  T.Restante   : %d%n",  ej.getTiempoMaxEjecucion() - ej.getTiempoejecucion());
            System.out.printf("  T.Llegada    : %d%n",  ej.getTiempoLlegada());
            System.out.printf("  T.Respuesta  : %d%n",  ej.getTRespuesta());
            System.out.printf("  T.Espera     : %d%n",  ej.getTEspera());
        }
        System.out.println();

        // TERMINADOS
        System.out.println(barra("PROCESOS TERMINADOS", PURPLE));
        if (listaTerminados.isEmpty()) {
            System.out.println("  (ninguno)");
        } else {
            System.out.printf("  %-6s %-14s %-10s %-8s %-10s %-8s %-10s %-10s%n",
                    "PID", "Operación", "Resultado", "TLleg", "TFin", "TRetorno", "TRespuesta", "TEspera");
            for (Procesos p : listaTerminados)
                System.out.printf("  %-6d %-14s %-10s %-8d %-10d %-8d %-10d %-10d%n",
                        p.getPID(),
                        p.getOperacionCompleta(),
                        p.getResultado(),
                        p.getTiempoLlegada(),
                        p.getTFinalizacion(),
                        p.getTRetorno(),
                        p.getTRespuesta(),
                        p.getTEspera());
        }
    }

    // ── Reporte final ─────────────────────────────────────────────────────────
    private static void reporteFinal() {
        clearScreen();
        System.out.println(BOLD + CYAN +
                "╔══════════════════════════════════════════════════════════════════╗\n" +
                "║                    REPORTE FINAL DE SIMULACIÓN                  ║\n" +
                "╚══════════════════════════════════════════════════════════════════╝" + RESET);
        System.out.printf("  Tiempo total: %d ticks%n%n", contadorGlobalProcesos);

        System.out.printf(BOLD + "  %-6s %-14s %-10s %-6s %-6s %-8s %-8s %-8s %-8s %-8s%n" + RESET,
                "PID", "Operación", "Resultado",
                "TLleg", "TFin", "TRetorno", "TResp", "TEspera", "TServicio", "Estado");
        System.out.println("  " + "─".repeat(100));

        for (Procesos p : listaTerminados) {
            System.out.printf("  %-6d %-14s %-10s %-6d %-6d %-8d %-8d %-8d %-8d %-8s%n",
                    p.getPID(),
                    p.getOperacionCompleta(),
                    p.getResultado(),
                    p.getTiempoLlegada(),
                    p.getTFinalizacion(),
                    p.getTRetorno(),
                    p.getTRespuesta(),
                    (p.getTRetorno() - p.getTServicio()),
                    p.getTServicio(),
                    p.isTerminadoPorError()
                            ? RED + "ERROR" + RESET
                            : GREEN + "NORMAL" + RESET);
        }

        System.out.println("\n" + BOLD + "  Leyenda:" + RESET);
        System.out.println("  TLleg     = Tiempo de Llegada");
        System.out.println("  TFin      = Tiempo de Finalización");
        System.out.println("  TRetorno  = TFin - TLleg");
        System.out.println("  TResp     = Primera atención - TLleg");
        System.out.println("  TEspera   = Ticks esperando en cola de Listos");
        System.out.println("  TServicio = Ticks dentro del CPU");
    }

    // ── Main ──────────────────────────────────────────────────────────────────
    public static void main(String[] args) {

        int nProcesos = 0;
        while (true) {
            System.out.println("Ingrese número de PROCESOS: ");
            try {
                nProcesos = teclado.nextInt();
                if (nProcesos == -1) { llenarProcesos(24); break; }
                if (nProcesos > 0) break;
            } catch (InputMismatchException ex) {
                System.out.println("Introduce un número válido.");
                teclado.next();
            }
        }
        teclado.nextLine();

        try { activarRawMode(); } catch (Exception ignored) {}
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            try { desactivarRawMode(); } catch (Exception ignored) {}
        }));

        llenarProcesos(nProcesos);
        iniciarLectorTecladoFileInput();

        boolean simulacionTerminada = false;

        while (!simulacionTerminada) {

            imprimirDetallesProcesos();

            try { Thread.sleep(ticksTiempoMilis); }
            catch (InterruptedException ignored) {}

            // Leer tecla
            char tecla = teclaPresionada;
            teclaPresionada = 0;

            switch (tecla) {
                case 'I':
                    if (!pausado.get()) interrumpirIO();
                    break;
                case 'E':
                    if (!pausado.get()) terminarPorError();
                    break;
                case 'P': pausado.set(true);  break;
                case 'C': pausado.set(false); break;
            }

            if (!pausado.get()) {
                tickProcesos();
                tickBloqueados();
                contadorGlobalProcesos++;
            }

            boolean todo = colaNuevos.isEmpty()    &&
                           colaListos.isEmpty()    &&
                           enEjecucion.get() == null &&
                           colaBloqueados.isEmpty();
            if (todo) simulacionTerminada = true;
        }

        terminar.set(true);
        reporteFinal();
    }
}