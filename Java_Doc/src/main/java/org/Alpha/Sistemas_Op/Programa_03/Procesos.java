package org.Alpha.Sistemas_Op.Programa_03;

import java.util.Random;

public class Procesos implements SoInterface{
    private static final Random random = new Random();
    private final int PID = random.nextInt(1001);
    private int tiempoMaxEjecucion = random.nextInt(20 - 6 + 1) + 6;
    private final String operacion = obtenerOperador();
    private final int[] operadores = new int[]{random.nextInt(100),random.nextInt(100)};
    private int tiempoLlegada = 0;
    private int tiempoEjecucion = 0;
    private int estadoBloqueado = 8;
    private String estado = null; // este lo define el sistema


    public Procesos() {}

    private String obtenerOperador(){
        return switch (random.nextInt(6)) {
            case 1 -> "-";
            case 2 -> "^";
            case 3 -> "*";
            case 4 -> "/";
            case 5 -> "%";
            default->   "+";
        };
    }

    public int getPID() {
        return PID;
    }

    public int getTiempoMaxEjecucion() {
        return tiempoMaxEjecucion;
    }

    public String getOperacion() {
        return operacion;
    }

    public int[] getOperadores() {
        return operadores;
    }

    public String getEstado() {
        return estado;
    }

    public void setEstado(String estado) {
        this.estado = estado;
    }

    public void setTiempoMaxEjecucion(int tiempoMaxEjecucion) {
        this.tiempoMaxEjecucion = tiempoMaxEjecucion;
    }

    public void setTiempoLlegada(int hora){
        this.tiempoLlegada = hora;
    }

    public int getTiempoLlegada(){
        return this.tiempoLlegada;
    }
    
    public int getTiempoBloqueado(){
        return this.estadoBloqueado;
    }

    public void setTiempoBloqueado(int tiempoBloqueado){
        this.estadoBloqueado = tiempoBloqueado;
    }

    public int getTiempoejecucion(){
        return this.tiempoEjecucion;
    }

    public void setTiempoEjecucion(int tiempoEjecucion){
        this.tiempoEjecucion = tiempoEjecucion;
    }
}
