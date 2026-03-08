package org.Alpha.Sistemas_Op.Programa_03.AIHelps;

import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.*;

public class SimuladorProcesos {

    // ── Colores ANSI ──────────────────────────────────────────────────────────
    static final String RESET  = "\033[0m";
    static final String BOLD   = "\033[1m";
    static final String CYAN   = "\033[36m";
    static final String GREEN  = "\033[32m";
    static final String YELLOW = "\033[33m";
    static final String RED    = "\033[31m";
    static final String BLUE   = "\033[34m";
    static final String PURPLE = "\033[35m";
    static final String WHITE  = "\033[37m";

    // ── Constantes ────────────────────────────────────────────────────────────
    static final int MAX_EN_MEMORIA   = 4;   // listos + ejecución + bloqueados
    static final int TIEMPO_BLOQUEADO = 8;

    // ── Estado compartido ─────────────────────────────────────────────────────
    static final Queue<Proceso>    colaNew       = new LinkedList<>();
    static final Queue<Proceso>    colaListos    = new LinkedList<>();
    static final List<Proceso>     colaBloqueados= new ArrayList<>();
    static final List<Proceso>     terminados    = new ArrayList<>();
    static final AtomicReference<Proceso> enEjecucion = new AtomicReference<>(null);

    static final AtomicInteger reloj    = new AtomicInteger(0);
    static final AtomicBoolean pausado  = new AtomicBoolean(false);
    static final AtomicBoolean terminar = new AtomicBoolean(false);

    static int pidCounter = 1;

    // =========================================================================
    //  CLASE Proceso
    // =========================================================================
    static class Proceso {
        int pid;
        int tme;                 // Tiempo Máximo Estimado
        int transcurrido;        // tiempo dentro del CPU en total
        int tiempoBloqueado;     // contador en cola bloqueados
        boolean primeraVez;      // ¿ya fue atendido?

        // Para la operación aritmética
        int  op1, op2;
        char operador;

        // Tiempos de planificación
        int tLlegada;
        int tFinalizacion;
        int tRespuesta   = -1;
        int tEspera;
        int tServicio;
        boolean error    = false;
        boolean terminadoNormal = false;

        // Para calcular espera correctamente
        int entroListosEn;       // reloj cuando entró a listos (última vez)
        int acumEspera = 0;

        Proceso(int pid, int tme, int op1, char operador, int op2, int tLlegada) {
            this.pid       = pid;
            this.tme       = tme;
            this.op1       = op1;
            this.operador  = operador;
            this.op2       = op2;
            this.tLlegada  = tLlegada;
            this.primeraVez= true;
            this.entroListosEn = tLlegada;
        }

        String operacionStr() {
            return op1 + " " + operador + " " + op2;
        }

        String resultado() {
            if (error) return "ERROR";
            try {
                double r;
                switch (operador) {
                    case '+': r = op1 + op2; break;
                    case '-': r = op1 - op2; break;
                    case '*': r = op1 * op2; break;
                    case '/': r = (double) op1 / op2; break;
                    default:  r = 0;
                }
                if (operador == '/' && op2 == 0) return "ERROR (div/0)";
                // Si el resultado es entero, mostrar sin decimal
                if (r == (long) r) return String.valueOf((long) r);
                return String.format("%.2f", r);
            } catch (Exception e) {
                return "ERROR";
            }
        }
    }

    // =========================================================================
    //  Generación de procesos
    // =========================================================================
    static Proceso generarProceso(int tLlegada) {
        Random rnd = new Random();
        int tme = 6 + rnd.nextInt(15);  // 6..20

        // Operación aleatoria sin error aritmético (sin div/0)
        char[] ops = {'+', '-', '*', '/'};
        char op;
        int a, b;
        do {
            op = ops[rnd.nextInt(4)];
            a  = rnd.nextInt(100) + 1;
            b  = rnd.nextInt(100) + 1;
        } while (op == '/' && b == 0);

        return new Proceso(pidCounter++, tme, a, op, b, tLlegada);
    }

    // =========================================================================
    //  Utilidades de pantalla
    // =========================================================================
    static void limpiarPantalla() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    static String barra(String titulo, String color) {
        return color + BOLD + "══════════════════════════════════════════════════\n"
                + "  " + titulo + "\n"
                + "══════════════════════════════════════════════════" + RESET;
    }

    static synchronized void mostrarPantalla() {
        limpiarPantalla();

        System.out.println(BOLD + CYAN +
                "╔══════════════════════════════════════════════════╗\n" +
                "║      SIMULADOR DE CINCO ESTADOS - FCFS          ║\n" +
                "╚══════════════════════════════════════════════════╝" + RESET);
        System.out.printf(BOLD + "  🕐 Reloj: %d ticks%s\n", reloj.get(), RESET);
        System.out.printf(WHITE + "  Teclas: [E] Bloquear  [W] Error  [P] Pausar  [C] Continuar%s\n\n", RESET);

        // ── NUEVOS ──────────────────────────────────────────────────────────
        System.out.println(barra("🆕 COLA DE NUEVOS  (" + colaNew.size() + " procesos)", YELLOW));
        if (colaNew.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            System.out.printf("  %-6s %-6s %-8s %-10s%n", "PID","TME","Llegada","Operación");
            for (Proceso p : colaNew)
                System.out.printf("  %-6d %-6d %-8d %-10s%n", p.pid, p.tme, p.tLlegada, p.operacionStr());
        }

        // ── LISTOS ──────────────────────────────────────────────────────────
        System.out.println(barra("📋 COLA DE LISTOS", BLUE));
        if (colaListos.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            System.out.printf("  %-6s %-6s %-12s%n", "PID","TME","T.Transcurrido");
            for (Proceso p : colaListos)
                System.out.printf("  %-6d %-6d %-12d%n", p.pid, p.tme, p.transcurrido);
        }

        // ── EJECUCIÓN ───────────────────────────────────────────────────────
        System.out.println(barra("▶️  EN EJECUCIÓN", GREEN));
        Proceso ej = enEjecucion.get();
        if (ej == null) {
            System.out.println("  (ninguno)");
        } else {
            System.out.printf("  PID: %d%n", ej.pid);
            System.out.printf("  Operación      : %s%n", ej.operacionStr());
            System.out.printf("  TME            : %d%n", ej.tme);
            System.out.printf("  T. Ejecutado   : %d%n", ej.transcurrido);
            System.out.printf("  T. Restante    : %d%n", ej.tme - ej.transcurrido);
            System.out.printf("  T. Llegada     : %d%n", ej.tLlegada);
        }

        // ── BLOQUEADOS ──────────────────────────────────────────────────────
        System.out.println(barra("🔒 COLA DE BLOQUEADOS", RED));
        if (colaBloqueados.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            System.out.printf("  %-6s %-16s%n", "PID","T.en Bloqueado");
            for (Proceso p : colaBloqueados)
                System.out.printf("  %-6d %-16d%n", p.pid, p.tiempoBloqueado);
        }

        // ── TERMINADOS ──────────────────────────────────────────────────────
        System.out.println(barra("✅ PROCESOS TERMINADOS", PURPLE));
        if (terminados.isEmpty()) {
            System.out.println("  (ninguno)");
        } else {
            System.out.printf("  %-6s %-14s %-8s%n", "PID","Operación","Resultado");
            for (Proceso p : terminados)
                System.out.printf("  %-6d %-14s %-8s%n", p.pid, p.operacionStr(), p.resultado());
        }

        System.out.println();
    }

    // =========================================================================
    //  Admisión de procesos nuevos → listos (respetando MAX_EN_MEMORIA)
    // =========================================================================
    static synchronized void admitirNuevos() {
        while (!colaNew.isEmpty()) {
            int enMemoria = colaListos.size() + colaBloqueados.size()
                    + (enEjecucion.get() != null ? 1 : 0);
            if (enMemoria >= MAX_EN_MEMORIA) break;
            Proceso p = colaNew.poll();
            p.entroListosEn = reloj.get();
            colaListos.add(p);
        }
    }

    // =========================================================================
    //  Scheduler: tomar siguiente de listos → ejecución
    // =========================================================================
    static synchronized void despachar() {
        if (enEjecucion.get() == null && !colaListos.isEmpty()) {
            Proceso p = colaListos.poll();
            if (p.primeraVez) {
                p.tRespuesta = reloj.get() - p.tLlegada;
                p.primeraVez = false;
            }
            // acumular espera
            p.acumEspera += reloj.get() - p.entroListosEn;
            enEjecucion.set(p);
        }
    }

    // =========================================================================
    //  Tick de reloj: avanzar un segundo de simulación
    // =========================================================================
    static synchronized void tick() {
        reloj.incrementAndGet();

        // ── Ejecutar proceso ────────────────────────────────────────────────
        Proceso ej = enEjecucion.get();
        if (ej != null) {
            ej.transcurrido++;
            if (ej.transcurrido >= ej.tme) {
                // Termina normalmente
                ej.terminadoNormal = true;
                ej.tFinalizacion   = reloj.get();
                ej.tServicio       = ej.tme;
                ej.tEspera         = ej.acumEspera;
                terminados.add(ej);
                enEjecucion.set(null);
            }
        }

        // ── Avanzar bloqueados ──────────────────────────────────────────────
        Iterator<Proceso> it = colaBloqueados.iterator();
        while (it.hasNext()) {
            Proceso p = it.next();
            p.tiempoBloqueado++;
            if (p.tiempoBloqueado >= TIEMPO_BLOQUEADO) {
                it.remove();
                p.tiempoBloqueado = 0;
                p.entroListosEn   = reloj.get();
                colaListos.add(p);
            }
        }

        admitirNuevos();
        despachar();
    }

    // =========================================================================
    //  Interrupciones de teclado
    // =========================================================================
    static synchronized void interrumpirIO() {
        Proceso ej = enEjecucion.get();
        if (ej == null) { System.out.println(RED + "  [!] No hay proceso en ejecución." + RESET); return; }
        enEjecucion.set(null);
        ej.entroListosEn = reloj.get(); // para calcular espera futura
        colaBloqueados.add(ej);
        despachar();
    }

    static synchronized void terminarPorError() {
        Proceso ej = enEjecucion.get();
        if (ej == null) { System.out.println(RED + "  [!] No hay proceso en ejecución." + RESET); return; }
        enEjecucion.set(null);
        ej.error           = true;
        ej.tFinalizacion   = reloj.get();
        ej.tServicio       = ej.transcurrido;
        ej.tEspera         = ej.acumEspera;
        terminados.add(ej);
        admitirNuevos();
        despachar();
    }

    // =========================================================================
    //  Reporte final
    // =========================================================================
    static void reporteFinal(int totalProcesos) {
        limpiarPantalla();
        System.out.println(BOLD + CYAN +
                "╔══════════════════════════════════════════════════════════════════════╗\n" +
                "║                     REPORTE FINAL - SIMULACIÓN                      ║\n" +
                "╚══════════════════════════════════════════════════════════════════════╝" + RESET);
        System.out.printf("  Tiempo total de simulación: %d ticks%n%n", reloj.get());

        System.out.printf(BOLD + "  %-4s %-12s %-8s %-8s %-8s %-8s %-8s %-8s %-10s %-8s%n" + RESET,
                "PID","Operación","Result","TLleg","TFin","TRetorno","TResp","TEspera","TServicio","Estado");
        System.out.println("  " + "─".repeat(100));

        for (Proceso p : terminados) {
            int tRetorno = p.tFinalizacion - p.tLlegada;
            System.out.printf("  %-4d %-12s %-8s %-8d %-8d %-8d %-8d %-8d %-10d %-8s%n",
                    p.pid,
                    p.operacionStr(),
                    p.resultado(),
                    p.tLlegada,
                    p.tFinalizacion,
                    tRetorno,
                    p.tRespuesta,
                    p.tEspera,
                    p.tServicio,
                    p.error ? RED + "ERROR" + RESET : GREEN + "NORMAL" + RESET
            );
        }

        System.out.println("\n" + BOLD + "  Leyenda de tiempos:" + RESET);
        System.out.println("  TLleg    = Tiempo de Llegada");
        System.out.println("  TFin     = Tiempo de Finalización");
        System.out.println("  TRetorno = Tiempo de Retorno  (TFin - TLleg)");
        System.out.println("  TResp    = Tiempo de Respuesta (primera atención - TLleg)");
        System.out.println("  TEspera  = Tiempo en cola de Listos esperando CPU");
        System.out.println("  TServicio= Tiempo dentro del CPU");
    }

    // =========================================================================
    //  Hilo de lectura de teclado (sin bloquear el bucle principal)
    // =========================================================================
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

    // =========================================================================
    //  MAIN
    // =========================================================================
    public static void main(String[] args) throws InterruptedException {
        Scanner sc = new Scanner(System.in);

        limpiarPantalla();
        System.out.println(BOLD + CYAN +
                "╔══════════════════════════════════════════════════╗\n" +
                "║    SIMULADOR DE PROCESOS - CINCO ESTADOS        ║\n" +
                "║           Algoritmo FCFS                        ║\n" +
                "╚══════════════════════════════════════════════════╝" + RESET);

        int n = 0;
        while (n <= 0) {
            System.out.print(BOLD + "\n  ¿Cuántos procesos desea simular? " + RESET);
            try { n = Integer.parseInt(sc.nextLine().trim()); }
            catch (NumberFormatException e) { /* reintento */ }
            if (n <= 0) System.out.println(RED + "  Ingrese un número mayor a 0." + RESET);
        }

        // Generar todos los procesos con tiempo de llegada 0
        // (llegan todos al inicio; el sistema los admite conforme hay espacio)
        for (int i = 0; i < n; i++) {
            colaNew.add(generarProceso(0));
        }

        // Admitir los primeros (hasta MAX_EN_MEMORIA)
        admitirNuevos();
        despachar();

        System.out.println(GREEN + "\n  Procesos generados. Iniciando simulación...\n" + RESET);
        System.out.println("  Presione ENTER después de cada tecla de control:");
        System.out.println("  E + ENTER → Bloquear  |  W + ENTER → Error");
        System.out.println("  P + ENTER → Pausar    |  C + ENTER → Continuar\n");
        Thread.sleep(2000);

        iniciarLectorTeclado();

        // ── Bucle principal ──────────────────────────────────────────────────
        boolean simulacionTerminada = false;
        while (!simulacionTerminada) {

            // ── Procesar tecla ───────────────────────────────────────────────
            char tecla = teclaPresionada;
            teclaPresionada = 0;

            switch (tecla) {
                case 'E': interrumpirIO();    break;
                case 'W': terminarPorError(); break;
                case 'P': pausado.set(true);  break;
                case 'C': pausado.set(false); break;
            }

            if (!pausado.get()) {
                tick();
            }

            mostrarPantalla();

            if (pausado.get()) {
                System.out.println(YELLOW + BOLD + "  ⏸  PAUSADO — presione C + ENTER para continuar" + RESET);
            }

            // ── Verificar fin ────────────────────────────────────────────────
            boolean todo = colaNew.isEmpty() && colaListos.isEmpty()
                    && enEjecucion.get() == null && colaBloqueados.isEmpty();
            if (todo) simulacionTerminada = true;

            Thread.sleep(1000); // 1 tick = 1 segundo real
        }

        terminar.set(true);
        reporteFinal(n);
    }
}