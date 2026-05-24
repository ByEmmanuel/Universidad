package org.Alpha.Sistemas_Op.Programa_08;

import java.io.FileInputStream;
import java.util.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;


public class Programa_08 implements SoInterface {

    // Colores ───────────────────────────────────────────────────────────────
    static final String RESET  = "\033[0m";
    static final String BOLD   = "\033[1m";
    static final String CYAN   = "\033[36m";
    static final String GREEN  = "\033[32m";
    static final String YELLOW = "\033[33m";
    static final String RED    = "\033[31m";
    static final String BLUE   = "\033[34m";
    static final String PURPLE = "\033[35m";
    static final String WHITE  = "\033[37m";

    // Colas ─────────────────────────────────────────────────────────────────
    private static PriorityQueue<Procesos> colaNuevos = new PriorityQueue<>(
            Comparator.comparingInt(Procesos::getPID)
    );
    private static Queue<Procesos> colaListos     = new LinkedList<>();
    private static Queue<Procesos> colaBloqueados = new LinkedList<>();
    private static Queue<Procesos> colaSuspendidos = new LinkedList<>();
    
    private static AtomicReference<Procesos> enEjecucion = new AtomicReference<>();
    private static ArrayList<Procesos> listaTerminados = new ArrayList<>();

    // logs del sistema
    private static ArrayList<String> logs = new ArrayList<>();

    // ═══════════════════════════════════════════════════════════════════════════
    //  MEMORIA PAGINADA
    //  Capacidad total : 230 unidades lógicas
    //  Tamaño de frame : 5  unidades lógicas
    //  Número de frames: 230 / 5 = 46 frames
    //
    //  memoria[i] == 0  →  frame i libre
    //  memoria[i] >  0  →  frame i ocupado con `memoria[i]` unidades del proceso
    // ═══════════════════════════════════════════════════════════════════════════
    private static final int CAPACIDAD_MEMORIA      = 230;   // unidades lógicas totales
    private static final int TAMANO_MAXIMO_POR_FRAME = 5;    // unidades por frame
    private static final int NUMERO_FRAMES =
            CAPACIDAD_MEMORIA / TAMANO_MAXIMO_POR_FRAME;      // 46 frames

    /** Arreglo de frames: índice = número de frame, valor = unidades ocupadas (0 = libre) */
    private static int[] memoria = new int[NUMERO_FRAMES];

    // si la queremos ordenada
    private static ArrayList<Procesos> listaTerminados_2 = new ArrayList<>();

    // ─── Control ──────────────────────────────────────────────────────────────
    static final AtomicBoolean pausado   = new AtomicBoolean(false);
    static final AtomicBoolean teclaB    = new AtomicBoolean(false);
    static final AtomicBoolean teclaT    = new AtomicBoolean(false);
    static final AtomicBoolean teclaS  = new AtomicBoolean(false);
    static final AtomicBoolean teclaR  = new AtomicBoolean(false);
    static final AtomicBoolean terminar  = new AtomicBoolean(false);
    

    static volatile char teclaPresionada = 0;
    private static int quantum           = 0;

    private static final short ticksTiempoMilis       = 350;
    private static short tickMensajes = 5;
    private static int         contadorGlobalProcesos = 0;

    // ═══════════════════════════════════════════════════════════════════════════
    //  GESTIÓN DE MEMORIA
    // ═══════════════════════════════════════════════════════════════════════════

    /**
     * Retorna cuántos frames libres hay actualmente.
     * Un frame libre es aquel con memoria[i] == 0.
     */
    private static int framesLibres() {
        int libres = 0;
        for (int v : memoria) if (v == 0) libres++;
        return libres;
    }

    /**
     * Calcula los frames que necesita un proceso de tamaño {@code tamano}.
     *   framesNecesarios = ⌈tamano / TAMANO_MAXIMO_POR_FRAME⌉
     */
    private static int framesNecesarios(int tamano) {
        return (int) Math.ceil((double) tamano / TAMANO_MAXIMO_POR_FRAME);
    }

    /**
     * Verifica si hay suficientes frames libres para admitir un proceso.
     *
     *   hayEspacio ⟺  framesLibres() ≥ ⌈tamano / TAMANO_MAXIMO_POR_FRAME⌉
     */
    private static boolean hayEspacioDisponible(int tamano) {
        return framesLibres() >= framesNecesarios(tamano);
    }

    /**
     * Asigna frames al proceso {@code p} de forma no contigua (paginación).
     * Llena cada frame con 5 unidades excepto el último, que recibe el residuo
     * si tamano % 5 ≠ 0.
     */
    private static void llenarMemoria(Procesos p) {
        int frames   = framesNecesarios(p.getTamaño());
        int[] dir    = new int[frames];
        int residuo  = p.getTamaño() % TAMANO_MAXIMO_POR_FRAME;
        int restante = p.getTamaño();
        int idx      = 0;

        for (int i = 0; i < memoria.length && idx < frames; i++) {
            if (memoria[i] == 0) {
                int ocupacion = (restante <= TAMANO_MAXIMO_POR_FRAME) ? restante : TAMANO_MAXIMO_POR_FRAME;
                memoria[i] = ocupacion;
                dir[idx++] = i;
                restante  -= ocupacion;
            }
        }
        p.setDireccionMemoria(dir);
    }

    /** Libera todos los frames asignados al proceso {@code p}. */
    private static void vaciarEspacioMemoria(Procesos p) {
        int[] vectorDirecciones = p.getDireccionMemoria();
        if (vectorDirecciones != null) {
            for (int frame : vectorDirecciones) {
                memoria[frame] = 0;
            }
            p.setDireccionMemoria(null);
        }
    }

    // ─── Llenar cola de nuevos ────────────────────────────────────────────────
    private static void llenarProcesos(int nProcesos) {
        for (int i = 0; i < nProcesos; i++) {
            Procesos p = new Procesos();
            p.setEstado("Nuevo");
            colaNuevos.add(p);
        }
    }

    // Pasar un proceso del estado de bloqueado a suspendido, liberar su memoria 
    // y si posteriormente se vuelve a necesitar del proceso, se va a la cola de listos
    private static void moverProcesoBloqueadoToSuspendido(){
        if(colaBloqueados.isEmpty())return;

        Procesos p = colaBloqueados.poll();
        vaciarEspacioMemoria(p);
        colaSuspendidos.add(p);

    }

    private static void moveSuspendidosToListos(){
        if (colaSuspendidos.isEmpty()) return;

        Procesos p = colaSuspendidos.poll();
        
        llenarMemoria(p);
        colaListos.add(p);
    }

    // ═══════════════════════════════════════════════════════════════════════════
    //  TICK PRINCIPAL
    //  La admisión de nuevos → listos ya NO usa un límite fijo de procesos;
    //  depende exclusivamente de los frames libres en memoria.
    // ═══════════════════════════════════════════════════════════════════════════
    private static void tickProcesos() {

        // Admitir mientras haya frames disponibles
        while (!colaNuevos.isEmpty()) {
            Procesos candidato = colaNuevos.peek();

            if (!hayEspacioDisponible(candidato.getTamaño())) {
                // El proceso de mayor prioridad no cabe; detenemos la admisión
                // (otros procesos de menor prioridad tampoco se intentan para
                // preservar el orden FCFS de la cola de nuevos)
                logs.add(String.format(
                        "Sin frames para PID %d (tam=%d, framesNec=%d, libres=%d), Tick=%d",
                        candidato.getPID(), candidato.getTamaño(),
                        framesNecesarios(candidato.getTamaño()),
                        framesLibres(), contadorGlobalProcesos));
                break;
            }

            Procesos p = colaNuevos.poll();
            llenarMemoria(p);
            p.setTiempoLlegada(contadorGlobalProcesos);
            p.setTickEntroListos(contadorGlobalProcesos);
            p.setEstado("Listo");
            colaListos.add(p);
        }

        Procesos p = enEjecucion.get();

        // Despachar si no hay proceso en ejecución
        if (p == null && !colaListos.isEmpty()) {
            p = colaListos.poll();
            p.acumularEspera(contadorGlobalProcesos - p.getTickEntroListos());

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

            if ((p.getTiempoEnQuantumm() < quantum) && p.getTiempoejecucion() < p.getTiempoMaxEjecucion()) {
                p.setTiempoEnQuantumm(p.getTiempoEnQuantumm() + 1);

            } else if (p.getTiempoEnQuantumm() >= quantum) {
                p.setTiempoEnQuantumm(1);
                enEjecucion.set(null);
                colaListos.add(p);
            }

            if (p.getTiempoejecucion() >= p.getTiempoMaxEjecucion()) {
                p.setTFinalizacion(contadorGlobalProcesos + 1);
                p.setEstado("Terminado");
                listaTerminados.add(p);
                enEjecucion.set(null);
                vaciarEspacioMemoria(p);
            }
        }
    }

    // ─── Tick bloqueados ──────────────────────────────────────────────────────
    private static void tickBloqueados() {
        Iterator<Procesos> it = colaBloqueados.iterator();
        while (it.hasNext()) {
            Procesos p = it.next();
            p.setTiempoBloqueado(p.getTiempoBloqueado() - 1);
            if (p.getTiempoBloqueado() <= 0) {
                it.remove();
                p.setTiempoBloqueado(8);
                p.setTickEntroListos(contadorGlobalProcesos);
                p.setEstado("Listo");
                colaListos.add(p);
            }
        }
    }

    // ─── Interrupciones ───────────────────────────────────────────────────────
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
        vaciarEspacioMemoria(p);   // liberar frames al terminar por error
    }

    // ─── Raw mode ─────────────────────────────────────────────────────────────
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

    // ─── Impresión ────────────────────────────────────────────────────────────
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

    // ─── MÉTODOS DE APOYO PARA LA INTERFAZ A DOBLE COLUMNA ──────────────────

    private static String padRightANSI(String s, int width) {
        // Calcula la longitud real del texto ignorando los códigos de color ANSI
        int visibleLength = s.replaceAll("\033\\[[;\\d]*m", "").length();
        int spacesNeeded = width - visibleLength;
        return spacesNeeded > 0 ? s + " ".repeat(spacesNeeded) : s + "  ";
    }

    private static String construirCeldaFrame(int i, Map<Integer, Integer> framePid) {
        if (memoria[i] == 0) {
            return String.format(" %-5d %-7s %s", i, "0", GREEN + "LIBRE" + RESET + "         ");
        } else {
            int pid = framePid.getOrDefault(i, -1);
            String txt = CYAN + "OCUPA " + (pid != -1 ? "(P" + pid + ")" : "") + RESET;
            // Ajuste manual de espacios para que la barra central "│" quede alineada
            int visLen = txt.replaceAll("\033\\[[;\\d]*m", "").length();
            return String.format(" %-5d %-7d %s", i, memoria[i], txt + " ".repeat(Math.max(0, 14 - visLen)));
        }
    }

    private static String construirFilaProc(String fmt, int fila, Procesos p, String estado) {
        int[] dir = p.getDireccionMemoria();
        String frames = (dir == null) ? "—" : construirCadenaFrames(dir);
        return String.format(fmt, fila, p.getPID(), p.getTamaño(), frames + " " + estado);
    }

    // ─── REEMPLAZO DE LA FUNCIÓN PRINCIPAL DE IMPRESIÓN ──────────────────────

    private static void imprimirDetallesProcesos() {
        clearScreen();

        List<String> left = new ArrayList<>();
        List<String> right = new ArrayList<>();

        int ocupados = NUMERO_FRAMES - framesLibres();
        String separadorIzq = "══════════════════════════════════════════════════════════════════════════════════";

        // ════════════════ PANEL IZQUIERDO (PROCESOS) ════════════════
        left.add(BOLD + CYAN + separadorIzq + RESET);
        left.add(BOLD + CYAN + "                           ALGORITMO  -  Round Robin                              " + RESET);
        left.add(BOLD + CYAN + separadorIzq + RESET);
        left.add(String.format(BOLD + "  Reloj: %d ticks%s", contadorGlobalProcesos, RESET));
        left.add(String.format("  Quantum : %d", quantum));
        left.add(String.format("  Memoria : %d/%d frames ocupados  (%d/%d unidades)", ocupados, NUMERO_FRAMES, ocupados * TAMANO_MAXIMO_POR_FRAME, CAPACIDAD_MEMORIA));
        left.add(WHITE + "  [I] Bloq  [E] Error  [P] Pausar  [C] Cont  [N] Nuevo" + RESET);
        left.add("");
        if (pausado.get()) left.add(RED + BOLD + "  ⏸  SISTEMA PAUSADO — presione C para continuar" + RESET);

        // esto puede ser camniado despues por alguna funcionalidad especial de la tecla S
        if (colaBloqueados.isEmpty() && tickMensajes-- >= 0) {
            left.add(CYAN + BOLD + "LA COLA ESTA VACIA: NO HAY NADA QUE SUSPENDER" + RESET);
        }else if(tickMensajes <= 0){
            tickMensajes = 5;
        }

        // NUEVOS
        left.add(YELLOW + BOLD + separadorIzq + RESET);
        left.add(YELLOW + BOLD + "  COLA DE NUEVOS  (" + colaNuevos.size() + " procesos)" + RESET);
        left.add(YELLOW + BOLD + separadorIzq + RESET);
        if (colaNuevos.isEmpty()) left.add("  (vacía)");
        else {
            left.add(String.format("  %-6s %-6s %-8s %-8s %-14s", "PID", "TME", "Tamaño", "Llegada", "Operación"));
            for (Procesos p : colaNuevos)
                left.add(String.format("  %-6d %-6d %-8d %-8d %-14s", p.getPID(), p.getTiempoMaxEjecucion(), p.getTamaño(), p.getTiempoLlegada(), p.getOperacionCompleta()));
        }
        left.add("");

        // LISTOS
        left.add(GREEN + BOLD + separadorIzq + RESET);
        left.add(GREEN + BOLD + "  COLA DE LISTOS  (" + colaListos.size() + " procesos)" + RESET);
        left.add(GREEN + BOLD + separadorIzq + RESET);
        if (colaListos.isEmpty()) left.add("  (vacía)");
        else {
            left.add(String.format("  %-6s %-6s %-8s %-12s %-14s", "PID", "TME", "Tamaño", "T.Ejecutado", "Operación"));
            for (Procesos p : colaListos)
                left.add(String.format("  %-6d %-6d %-8d %-12d %-14s", p.getPID(), p.getTiempoMaxEjecucion(), p.getTamaño(), p.getTiempoejecucion(), p.getOperacionCompleta()));
        }
        left.add("");

        // BLOQUEADOS
        left.add(RED + BOLD + separadorIzq + RESET);
        left.add(RED + BOLD + "  COLA DE BLOQUEADOS  (" + colaBloqueados.size() + " procesos)" + RESET);
        left.add(RED + BOLD + separadorIzq + RESET);
        if (colaBloqueados.isEmpty()) left.add("  (vacía)");
        else {
            left.add(String.format("  %-10s %-6s %-6s %-8s", "T.Bloq", "PID", "TME", "Llegada"));
            for (Procesos p : colaBloqueados)
                left.add(String.format("  %-10d %-6d %-6d %-8d", p.getTiempoBloqueado(), p.getPID(), p.getTiempoMaxEjecucion(), p.getTiempoLlegada()));
        }
        left.add("");

        // EN EJECUCIÓN
        left.add(CYAN + BOLD + separadorIzq + RESET);
        left.add(CYAN + BOLD + "  EN EJECUCIÓN" + RESET);
        left.add(CYAN + BOLD + separadorIzq + RESET);
        Procesos ej = enEjecucion.get();
        if (ej == null) left.add("  (ninguno)");
        else {
            left.add(String.format("  PID          : %d", ej.getPID()));
            left.add(String.format("  Operación    : %s", ej.getOperacionCompleta()));
            left.add(String.format("  Tamaño       : %d uds (%d frames)", ej.getTamaño(), framesNecesarios(ej.getTamaño())));
            left.add(String.format("  T.Restante   : %d", ej.getTiempoMaxEjecucion() - ej.getTiempoejecucion()));
        }
        left.add("");

        // TERMINADOS
        left.add(PURPLE + BOLD + separadorIzq + RESET);
        left.add(PURPLE + BOLD + "  PROCESOS TERMINADOS  (" + listaTerminados.size() + ")" + RESET);
        left.add(PURPLE + BOLD + separadorIzq + RESET);
        if (listaTerminados.isEmpty()) left.add("  (ninguno)");
        else {
            left.add(String.format("  %-6s %-14s %-10s %-8s %-10s %-8s %-10s %-10s", 
                    "PID", "Operación", "Resultado", "TLleg", "TFin", "TRetorno", "TRespuesta", "TEspera"));
            for (Procesos p : listaTerminados)
                left.add(String.format("  %-6d %-14s %-10s %-8d %-10d %-8d %-10d %-10d", 
                        p.getPID(), p.getOperacionCompleta(), p.getResultado(), p.getTiempoLlegada(), p.getTFinalizacion(), p.getTRetorno(), p.getTRespuesta(), p.getTEspera()));
        }
        left.add("");

        // SUSPENDIDOS
        left.add(YELLOW + BOLD + separadorIzq + RESET);
        left.add(YELLOW + BOLD + "  PROCESOS SUSPENDIDOS  (" + colaSuspendidos.size() + ")" + RESET);
        left.add(YELLOW + BOLD + separadorIzq + RESET);
        if (colaSuspendidos.isEmpty()) {
            left.add("  (ninguno)");
        }else {
            left.add(String.format("  %-6s %-14s %-10s %-8s %-10s %-8s %-10s %-10s", 
                    "PID", "Operación", "Resultado", "TLleg", "TFin", "TRetorno", "TRespuesta", "TEspera"));
            for (Procesos p : colaSuspendidos)
                left.add(String.format("  %-6d %-14s %-10s %-8d %-10d %-8d %-10d %-10d", 
                        p.getPID(), p.getOperacionCompleta(), p.getResultado(), p.getTiempoLlegada(), p.getTFinalizacion(), p.getTRetorno(), p.getTRespuesta(), p.getTEspera()));
        }
        left.add("");


        // ════════════════ PANEL DERECHO (MEMORIA) ════════════════
        String separadorDer = "════════════════════════════════════════════════════════════════";
        right.add(BLUE + BOLD + separadorDer + RESET);
        right.add(BLUE + BOLD + "                  MAPA DE FRAMES Y PAGINACIÓN                   " + RESET);
        right.add(BLUE + BOLD + separadorDer + RESET);
        
        Map<Integer, Integer> framePid = new HashMap<>();
        for (Procesos p : colaListos) mapearFrames(framePid, p);
        for (Procesos p : colaBloqueados) mapearFrames(framePid, p);
        if (ej != null) mapearFrames(framePid, ej);

        // Dividido en dos columnas para ahorrar espacio vertical
        right.add(String.format("  %-5s %-7s %-14s │ %-5s %-7s %-14s", "Frame", "Ocupado", "Estado", "Frame", "Ocupado", "Estado"));
        right.add("  " + "─".repeat(60));
        
        int mitad = NUMERO_FRAMES / 2; // 23
        for (int i = 0; i < mitad; i++) {
            int i2 = i + mitad;
            String f1 = construirCeldaFrame(i, framePid);
            String f2 = (i2 < NUMERO_FRAMES) ? construirCeldaFrame(i2, framePid) : "";
            right.add(f1 + " │ " + f2);
        }
        right.add("");

        right.add(BOLD + "  DETALLE DE FRAMES POR PROCESO" + RESET);
        right.add("  " + "─".repeat(60));
        String fmtPag = "  %-5s %-5s %-7s %-30s";
        right.add(String.format(BOLD + fmtPag + RESET, "Fila", "PID", "Tamaño", "Frames asignados"));
        
        int fila = 0;
        for (Procesos p : colaNuevos) right.add(String.format(fmtPag, fila++, p.getPID(), p.getTamaño(), "(en espera)"));
        for (Procesos p : colaListos) right.add(construirFilaProc(fmtPag, fila++, p, GREEN + "LISTO" + RESET));
        if (ej != null) right.add(construirFilaProc(fmtPag, fila++, ej, CYAN + "EJEC" + RESET));
        for (Procesos p : colaBloqueados) right.add(construirFilaProc(fmtPag, fila++, p, RED + "BLOQ" + RESET));
        for (Procesos p : listaTerminados) {
            int[] mem = p.getDireccionMemoria();
            String memStr = mem == null ? PURPLE + "Liberada" + RESET : construirCadenaFrames(mem) + " " + PURPLE + "TERM" + RESET;
            right.add(String.format(fmtPag, fila++, p.getPID(), p.getTamaño(), memStr));
        }

        // ════════════════ UNIR Y RENDERIZAR ════════════════
        int maxLineas = Math.max(left.size(), right.size());
        int anchoPanelIzquierdo = 86; // Espacio fijo antes de imprimir la columna derecha

        for (int i = 0; i < maxLineas; i++) {
            String lineaIzq = (i < left.size()) ? left.get(i) : "";
            String lineaDer = (i < right.size()) ? right.get(i) : "";
            
            // padRightANSI se asegura de que la columna izquierda mida exactamente 86 caracteres visuales,
            // sin importar los códigos de color, manteniendo la columna derecha perfectamente alineada.
            System.out.println(padRightANSI(lineaIzq, anchoPanelIzquierdo) + lineaDer);
        }
    }

    // ─── Reporte final ────────────────────────────────────────────────────────
    private static void reporteFinal() {
        clearScreen();
        listaTerminados.sort(Comparator.comparing(Procesos::getPID));

        System.out.println(BOLD + CYAN +
                "════════════════════════════════════════════════════════════════════\n" +
                "                    REPORTE FINAL DE SIMULACIÓN                    \n" +
                "════════════════════════════════════════════════════════════════════" + RESET);
        System.out.printf("  Tiempo total : %d ticks%n", contadorGlobalProcesos);
        System.out.printf("  Quantum      : %d%n", quantum);
        System.out.printf("  Memoria      : %d unidades / %d frames%n%n", CAPACIDAD_MEMORIA, NUMERO_FRAMES);

        System.out.printf(BOLD + "  %-6s %-16s %-10s %-6s %-6s %-8s %-8s %-8s %-8s %-8s%n" + RESET,
                "PID", "Operación", "Resultado",
                "TLleg", "TFin", "TRetorno", "TResp", "TEspera", "TServicio", "Estado");
        System.out.println("  " + "─".repeat(104));

        for (Procesos p : listaTerminados) {
            System.out.printf("  %-6d %-16s %-10s %-6d %-6d %-8d %-8d %-8d %-8d %-8s%n",
                    p.getPID(), p.getOperacionCompleta(), p.getResultado(),
                    p.getTiempoLlegada(), p.getTFinalizacion(),
                    p.getTRetorno(), p.getTRespuesta(),
                    (p.getTRetorno() - p.getTServicio()),
                    p.getTServicio(),
                    p.isTerminadoPorError() ? RED + "ERROR" + RESET : GREEN + "NORMAL" + RESET);
        }

        System.out.println("\n" + BOLD + "  Leyenda:" + RESET);
        System.out.println("  TLleg     = Tiempo de Llegada");
        System.out.println("  TFin      = Tiempo de Finalización");
        System.out.println("  TRetorno  = TFin - TLleg");
        System.out.println("  TResp     = Primera atención - TLleg");
        System.out.println("  TEspera   = Ticks esperando en cola de Listos");
        System.out.println("  TServicio = Ticks dentro del CPU");
    }

    // ─── Reporte tecla B ─────────────────────────────────────────────────────
    private static void reporteTeclaB() {
        clearScreen();

        String encabezado = String.format(
                BOLD + "  %-6s %-16s %-10s %-6s %-6s %-8s %-8s %-8s %-8s %-8s%n" + RESET,
                "PID", "Operación", "Resultado",
                "TLleg", "TFin", "TRetorno", "TResp", "TEspera", "TServicio", "Estado");
        String separador = "  " + "─".repeat(104);

        System.out.println(BOLD + CYAN +
                "════════════════════════════════════════════════════════════════════\n" +
                "                    REPORTE PARCIAL (TECLA B)                      \n" +
                "════════════════════════════════════════════════════════════════════" + RESET);
        System.out.printf("  Tiempo actual: %d ticks%n", contadorGlobalProcesos);
        System.out.printf("  Quantum : %d%n%n", quantum);

        // NUEVOS
        System.out.println(YELLOW + BOLD + "\n  NUEVOS" + RESET);
        System.out.print(encabezado);
        System.out.println(separador);
        if (colaNuevos.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            for (Procesos p : colaNuevos)
                System.out.printf("  %-6d %-16s %-10s %-6d %-6d %-8d %-8d %-8d %-8d %-8s%n",
                        p.getPID(), p.getOperacionCompleta(), "-",
                        p.getTiempoLlegada(), 0, 0, 0, 0, 0,
                        YELLOW + "NUEVO" + RESET);
        }

        // LISTOS
        System.out.println(GREEN + BOLD + "\n  LISTOS" + RESET);
        System.out.print(encabezado);
        System.out.println(separador);
        if (colaListos.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            for (Procesos p : colaListos)
                System.out.printf("  %-6d %-16s %-10s %-6d %-6d %-8d %-8d %-8d %-8d %-8s%n",
                        p.getPID(), p.getOperacionCompleta(), "-",
                        p.getTiempoLlegada(), 0, 0,
                        (Math.max(p.getTRespuesta(), 0)),
                        (contadorGlobalProcesos - p.getTiempoLlegada() - p.getTServicio()),
                        p.getTServicio(),
                        GREEN + "LISTO" + RESET);
        }

        // EN EJECUCIÓN
        System.out.println(CYAN + BOLD + "\n  EN EJECUCIÓN" + RESET);
        System.out.print(encabezado);
        System.out.println(separador);
        Procesos ej = enEjecucion.get();
        if (ej == null) {
            System.out.println("  (ninguno)");
        } else {
            System.out.printf("  %-6d %-16s %-10s %-6d %-6d %-8d %-8d %-8d %-8d %-8s%n",
                    ej.getPID(), ej.getOperacionCompleta(), "-",
                    ej.getTiempoLlegada(), 0, 0,
                    ej.getTRespuesta(),
                    (contadorGlobalProcesos - ej.getTiempoLlegada() - ej.getTServicio()),
                    ej.getTServicio(),
                    CYAN + "EJEC" + RESET);
        }

        // BLOQUEADOS
        System.out.println(RED + BOLD + "\n  BLOQUEADOS" + RESET);
        System.out.print(encabezado);
        System.out.println(separador);
        if (colaBloqueados.isEmpty()) {
            System.out.println("  (vacía)");
        } else {
            for (Procesos p : colaBloqueados)
                System.out.printf("  %-6d %-16s %-10s %-6d %-6d %-8d %-8d %-8d %-8d %-8s%n",
                        p.getPID(), p.getOperacionCompleta(), "-",
                        p.getTiempoLlegada(), 0, 0,
                        p.getTRespuesta(),
                        (contadorGlobalProcesos - p.getTiempoLlegada() - p.getTServicio()),
                        p.getTServicio(),
                        RED + "BLOQ" + RESET);
        }

        // TERMINADOS
        System.out.println(PURPLE + BOLD + "\n  TERMINADOS" + RESET);
        System.out.print(encabezado);
        System.out.println(separador);
        if (listaTerminados.isEmpty()) {
            System.out.println("  (ninguno)");
        } else {
            for (Procesos p : listaTerminados)
                System.out.printf("  %-6d %-16s %-10s %-6d %-6d %-8d %-8d %-8d %-8d %-8s%n",
                        p.getPID(), p.getOperacionCompleta(), p.getResultado(),
                        p.getTiempoLlegada(), p.getTFinalizacion(),
                        p.getTRetorno(), p.getTRespuesta(),
                        (p.getTRetorno() - p.getTServicio()),
                        p.getTServicio(),
                        p.isTerminadoPorError() ? RED + "ERROR" + RESET : GREEN + "NORMAL" + RESET);
        }

        System.out.println("\n" + BOLD + "  Leyenda:" + RESET);
        System.out.println("  TLleg     = Tiempo de Llegada");
        System.out.println("  TFin      = Tiempo de Finalización  (0 si no ha terminado)");
        System.out.println("  TRetorno  = TFin - TLleg            (0 si no ha terminado)");
        System.out.println("  TResp     = Primera atención - TLleg");
        System.out.println("  TEspera   = Ticks esperando en cola de Listos");
        System.out.println("  TServicio = Ticks dentro del CPU");
    }

    // ═══════════════════════════════════════════════════════════════════════════
    //  VISTA DE PAGINACIÓN (TECLA T)
    //  Muestra el mapa completo de los 46 frames con su estado.
    // ═══════════════════════════════════════════════════════════════════════════

    /**
     * 
     * De la cola de bloqueados al presionar la tecla S deberan pasar a lista de suspendidos, 
     * en suspendidos se liberara la memoria, posterior mente la tecla R le volvera a signar memoria 
     * y pasara a cola de listos
     */
    private static void paginacionProcesos() {
        clearScreen();

        String formato    = "  %-8s %-8s %-8s %-30s\n";
        String encabezado = String.format(BOLD + formato + RESET,
                "Frame", "PID", "Tamaño", "Frames asignados");
        String separador  = "  " + "─".repeat(60);

        int ocupados = NUMERO_FRAMES - framesLibres();

        System.out.println(BOLD + CYAN +
                "════════════════════════════════════════════════════════════════════\n" +
                "             PAGINACIÓN DE MEMORIA (TECLA T)                       \n" +
                "════════════════════════════════════════════════════════════════════" + RESET);
        System.out.printf("  Tiempo actual : %d ticks%n", contadorGlobalProcesos);
        System.out.printf("  Quantum       : %d%n", quantum);
        System.out.printf("  Capacidad     : %d unidades lógicas / %d frames%n",
                CAPACIDAD_MEMORIA, NUMERO_FRAMES);
        System.out.printf("  Ocupación     : %d frames ocupados, %d libres%n%n",
                ocupados, framesLibres());

        // ── Mapa de frames ────────────────────────────────────────────────────
        System.out.println(BOLD + "  MAPA DE FRAMES (cada celda = 1 frame de 5 unidades)" + RESET);
        System.out.println(separador);
        System.out.printf("  %-6s %-8s %s%n", "Frame", "Ocupado", "Estado");
        System.out.println(separador);

        // Construir un mapa frame → PID para la visualización
        Map<Integer, Integer> framePid = new HashMap<>();

        // Recorrer todos los procesos activos para mapear sus frames
        for (Procesos p : colaListos)
            mapearFrames(framePid, p);
        for (Procesos p : colaBloqueados)
            mapearFrames(framePid, p);
        Procesos ej = enEjecucion.get();
        if (ej != null) mapearFrames(framePid, ej);

        for (int i = 0; i < NUMERO_FRAMES; i++) {
            if (memoria[i] == 0) {
                System.out.printf("  %-6d %-8s %s%n", i, "0", GREEN + "LIBRE" + RESET);
            } else {
                int pid = framePid.getOrDefault(i, -1);
                System.out.printf("  %-6d %-8d %s%n",
                        i, memoria[i],
                        CYAN + "OCUPADO" + (pid != -1 ? " (PID " + pid + ")" : "") + RESET);
            }
        }

        System.out.println();
        System.out.println(BOLD + "  DETALLE POR PROCESO" + RESET);
        System.out.println(separador);
        System.out.print(encabezado);
        System.out.println(separador);

        int filaDet = 0;

        // Nuevos (sin frames asignados aún)
        for (Procesos p : colaNuevos) {
            System.out.printf(formato, filaDet++, p.getPID(), p.getTamaño(), "(en espera)");
        }
        for (Procesos p : colaListos)
            imprimirFilaPaginacion(formato, filaDet++, p, GREEN + "LISTO" + RESET);
        if (ej != null)
            imprimirFilaPaginacion(formato, filaDet++, ej, CYAN + "EJEC" + RESET);
        for (Procesos p : colaBloqueados)
            imprimirFilaPaginacion(formato, filaDet++, p, RED + "BLOQ" + RESET);
        for (Procesos p : listaTerminados) {
            int[] mem = p.getDireccionMemoria();
            System.out.printf(formato, filaDet++, p.getPID(), p.getTamaño(),
                    mem == null ? PURPLE + "Memoria liberada" + RESET
                            : construirCadenaFrames(mem) + " " + PURPLE + "TERM" + RESET);
        }
    }

    /** Rellena el mapa frame→PID a partir de los frames del proceso. */
    private static void mapearFrames(Map<Integer, Integer> mapa, Procesos p) {
        int[] dir = p.getDireccionMemoria();
        if (dir == null) return;
        for (int f : dir) mapa.put(f, p.getPID());
    }

    private static void imprimirFilaPaginacion(String fmt, int fila, Procesos p, String estado) {
        int[] dir = p.getDireccionMemoria();
        String frames = (dir == null) ? "—" : construirCadenaFrames(dir);
        System.out.printf(fmt, fila, p.getPID(), p.getTamaño(), frames + " " + estado);
    }

    private static String construirCadenaFrames(int[] dir) {
        StringBuilder sb = new StringBuilder();
        for (int f : dir) sb.append(f).append(" ");
        return sb.toString().trim();
    }

    // ─── Main ─────────────────────────────────────────────────────────────────
    public static void main(String[] args) {

        int nProcesos = 0;
        quantum = 0;
        while (nProcesos <= 0 || quantum <= 0) {
            System.out.println("Ingrese número de PROCESOS: ");
            try {
                nProcesos = teclado.nextInt();
                System.out.println("Ingrese Quantum: ");
                quantum = teclado.nextInt();
                if (nProcesos > 0 && quantum > 0) break;
            } catch (InputMismatchException ex) {
                System.out.println("Introduce un número válido.");
                teclado.next();
            }
        }
        teclado.nextLine();

        try {
            activarRawMode();
        } catch (Exception ignored) {}

        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            try { desactivarRawMode(); } catch (Exception ignored) {}
        }));

        llenarProcesos(nProcesos);
        iniciarLectorTecladoFileInput();

        boolean simulacionTerminada = false;

        while (!simulacionTerminada) {

            try {
                Thread.sleep(200);
            } catch (InterruptedException ignored) {}

            char tecla = teclaPresionada;
            teclaPresionada = 0;

            switch (tecla) {
                case 'I':
                    if (!pausado.get()) interrumpirIO();
                    break;
                case 'E':
                    if (!pausado.get()) terminarPorError();
                    break;
                case 'P':
                    pausado.set(true);
                    break;
                case 'C':
                    pausado.set(false);
                    teclaB.set(false);
                    teclaT.set(false);
                    break;
                case 'N':
                    llenarProcesos(1);
                    break;
                case 'B':
                    teclaB.set(true);
                    break;
                case 'T':
                    teclaT.set(true);
                    break;
                case 'S':
                    // poner timer de tiempo en el que se mostrara el mensaje por si no hay procesos en 
                    // ejecucion, y/o no se pueden liberar
                    teclaS.set(true);
                    break;
                case 'R':
                    teclaR.set(true);
                    break;
            }

            if (!pausado.get()) {
                imprimirDetallesProcesos();
                tickProcesos();
                tickBloqueados();
                contadorGlobalProcesos++;
            }

            if (!pausado.get() && teclaB.get()) {
                clearScreen();
                reporteTeclaB();
                pausado.set(true);
            }

            if (!pausado.get() && teclaT.get()) {
                clearScreen();
                paginacionProcesos();
                pausado.set(true);
            }

            if(teclaS.get() && !colaBloqueados.isEmpty()){
                moverProcesoBloqueadoToSuspendido();
                
                teclaS.set(false);
            }

            if (teclaR.get()) {
                moveSuspendidosToListos();
                teclaR.set(false);
            }

            boolean todo = colaNuevos.isEmpty()
                    && colaListos.isEmpty()
                    && enEjecucion.get() == null
                    && colaBloqueados.isEmpty()
                    && colaSuspendidos.isEmpty();
            if (todo) simulacionTerminada = true;
        }

        terminar.set(true);
        reporteFinal();
    }
}