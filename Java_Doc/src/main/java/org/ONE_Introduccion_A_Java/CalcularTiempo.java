package org.ONE_Introduccion_A_Java;

public class CalcularTiempo {

    private long tiempoInicio;
    private long tiempoFin;

    public void  retornarTiempo(){
        // Calcular el tiempo transcurrido
        long tiempoTranscurrido = tiempoFin - tiempoInicio;
        // Convertir el tiempo transcurrido a milisegundos
        double tiempoMilisegundos = tiempoTranscurrido / 1_000_000.0;
        double tiempoSegundos = (double) tiempoTranscurrido / 1_000_000_000;
        System.out.println("Tiempo transcurrido: " + tiempoMilisegundos + " ms");
        System.out.println("Tiempo transcurrido: " + tiempoSegundos + " s");

    }

    public void init(){
        // Tiempo de inicio en nanosegundos
        this.tiempoInicio = System.nanoTime();
    }

    public void end(){
        // Tiempo de finalización en nanosegundos
        this.tiempoFin = System.nanoTime();
        retornarTiempo();
    }
}
