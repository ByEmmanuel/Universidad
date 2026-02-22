package org.Alpha.Sistemas_Op.Programa_02;

import java.util.Scanner;

public class PruebaMultiprocesos {
    private static final Object monitor = new Object();

    private static volatile boolean pausa = false;

    public static void main(String[] args) {

        Thread hiloTeclado = new Thread(() ->{
            Scanner scanner = new Scanner(System.in);
            System.out.println("Comandos: 'p' (Pausar) | 'r' (Reanudar) | 's' (Salir)");

            while (true){
                String entrada = scanner.nextLine().trim().toLowerCase();
                switch (entrada) {
                    case "p":
                        pausa = true;
                        System.out.println("[SISTEMA] Pausa solicitada...");
                        break;
                    case "r":
                        pausa = false;
                        System.out.println("[SISTEMA] Reanudando ejecución...");
                        // Sincronizamos con el monitor para despertar al hilo principal
                        synchronized (monitor) {
                            monitor.notify();
                        }
                        break;
                    case "s":
                        System.out.println("[SISTEMA] Terminando programa.");
                        System.exit(0);
                        break;
                }
            }
        });

        // Lo marcamos como Daemon para que muera automáticamente si el hilo principal termina.
        hiloTeclado.setDaemon(true);
        hiloTeclado.start();

        int ciclo = 1;
        while (true){
            synchronized (monitor){
                while (pausa){
                    try {
                        monitor.wait();
                    }catch (InterruptedException e){
                        Thread.currentThread().interrupt();
                        System.err.println("Hilo interrumpido inesperadamente");
                    }
                }
            }
            // logica de negocio
            System.out.println("Procesando ciclo: " + ciclo++);
            try{
                Thread.sleep(1000);
            }catch (InterruptedException e){
                Thread.currentThread().interrupt();
            }

        }



    }
}
