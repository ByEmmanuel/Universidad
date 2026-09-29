package org.Alpha.Sistemas_Op.Programa_07;

import java.util.Random;

public class Procesos {

    private static final Random random = new Random();

    private final int PID = random.nextInt(1001);
    private int tiempoMaxEjecucion = random.nextInt(20 - 6 + 1) + 6;
    private final String operacion = obtenerOperador();
    private final int[] operadores = new int[]{random.nextInt(100) + 1, random.nextInt(100) + 1};
    private int tiempoLlegada   = 0;
    // si tiempo de ejecucion % quantum != 0 || != tiempoMaxEjecucion ejecutar proceso
    private int tiempoEnQuantumm = 1;
    private int tiempoEjecucion = 0;
    private int estadoBloqueado = 8;
    private String estado       = null;

    // ── Tiempos de planificación ──────────────────────────────────────────────
    private int tFinalizacion = 0;   // tick en que el proceso terminó
    private int tRespuesta    = -1;  // tick en que fue atendido por primera vez
    private int tEspera       = 0;   // ticks acumulados esperando en colaListos
    private int tickEntroListos = 0; // último tick en que entró a colaListos
    private boolean primeraVez = true;
    private boolean terminadoPorError = false;


    // Atributos para Algoritmo Paginacion Simple
    private int tamaño = random.nextInt(6,27);
    private int cantidadPaginas = 0;

    // 6 debido a que el tamaño maximo de un proceso son 26 y su capacidad maxima son 6 frames
    // cada frame esta compuesta por 5 paginas
    // valores entre 5 y 46
    private final int framesARellenar = (int) Math.ceil((double) tamaño / 5 );
    private int[] direccionMemoria = new int[ framesARellenar];



    public Procesos() {}

    private String obtenerOperador() {
        return switch (random.nextInt(6)) {
            case 1 -> "-";
            case 2 -> "^";
            case 3 -> "*";
            case 4 -> "/";
            case 5 -> "%";
            default -> "+";
        };
    }

    // ── Resultado de la operación ─────────────────────────────────────────────
    public String getResultado() {
        if (terminadoPorError) return "ERROR";
        int a = operadores[0];
        int b = operadores[1];
        try {
            return switch (operacion) {
                case "+" -> String.valueOf(a + b);
                case "-" -> String.valueOf(a - b);
                case "*" -> String.valueOf(a * b);
                case "/" -> b == 0 ? "ERROR(div/0)" : String.valueOf(a / b);
                case "%" -> b == 0 ? "ERROR(mod/0)" : String.valueOf(a % b);
                case "^" -> String.valueOf((int) Math.pow(a, b));
                default  -> "?";
            };
        } catch (Exception e) {
            return "ERROR";
        }
    }

    public String getOperacionCompleta() {
        return operadores[0] + " " + operacion + " " + operadores[1];
    }

    // ── Getters / Setters existentes ──────────────────────────────────────────
    public int    getPID()                          { return PID; }
    public int    getTiempoMaxEjecucion()           { return tiempoMaxEjecucion; }
    public void   setTiempoMaxEjecucion(int t)      { this.tiempoMaxEjecucion = t; }
    public String getOperacion()                    { return operacion; }
    public int[]  getOperadores()                   { return operadores; }
    public String getEstado()                       { return estado; }
    public void   setEstado(String estado)          { this.estado = estado; }
    public void   setTiempoLlegada(int hora)        { this.tiempoLlegada = hora; }
    public int    getTiempoLlegada()                { return tiempoLlegada; }
    public int    getTiempoBloqueado()              { return estadoBloqueado; }
    public void   setTiempoBloqueado(int t)         { this.estadoBloqueado = t; }
    public int    getTiempoejecucion()              { return tiempoEjecucion; }
    public void   setTiempoEjecucion(int t)         { this.tiempoEjecucion = t; }

    // ── Getters / Setters nuevos de planificación ─────────────────────────────
    public int  getTFinalizacion()                  { return tFinalizacion; }
    public void setTFinalizacion(int t)             { this.tFinalizacion = t; }

    public int  getTRespuesta()                     { return tRespuesta; }
    public void setTRespuesta(int t)                { if (tRespuesta == -1) this.tRespuesta = t; }

    public int  getTEspera()                        { return tEspera; }
    public void acumularEspera(int ticks)           { this.tEspera += ticks; }

    public int  getTickEntroListos()                { return tickEntroListos; }
    public void setTickEntroListos(int t)           { this.tickEntroListos = t; }

    public boolean isPrimeraVez()                   { return primeraVez; }
    public void    setPrimeraVez(boolean b)         { this.primeraVez = b; }

    public boolean isTerminadoPorError()            { return terminadoPorError; }
    public void    setTerminadoPorError(boolean b)  { this.terminadoPorError = b; }

    // Tiempo de retorno = tFinalizacion - tLlegada
    public int getTRetorno()                        { return tFinalizacion - tiempoLlegada; }

    // Tiempo de servicio = ticks que estuvo dentro del CPU
    public int getTServicio()                       { return tiempoEjecucion; }

    public int getTiempoEnQuantumm()                 { return tiempoEnQuantumm;}

    public void setTiempoEnQuantumm(int tiempoEnQuantumm) {
        this.tiempoEnQuantumm = tiempoEnQuantumm;
    }

    // Paginacion --------------------------------------

    public int getTamaño()                          {return tamaño;}

    public void setTamaño(int tamaño)               {this.tamaño = tamaño;}

    public int getCantidadPaginas()                 {return cantidadPaginas;}

    public void setCantidadPaginas(int cantidadPaginas) {this.cantidadPaginas = cantidadPaginas;}

    public int[] getDireccionMemoria()               {return direccionMemoria;}

    public void setDireccionMemoria(int[] direccionMemoria) {this.direccionMemoria = direccionMemoria;}

    public int getFramesARellenar() {return framesARellenar;}
}