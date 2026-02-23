//package org.Alpha.Sistemas_Op.Programa_02;

/*
* Programa 2. Simular el procesamiento por lotes con Multiprogramación.
* */

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Scanner;

public class Programa_02{
    private static ArrayDeque<Lotes> colaLotes = new ArrayDeque<>();
    private static ArrayList<Lotes> lotesCompletados = new ArrayList<>();
    private static ArrayList<String> procesosCompletados = new ArrayList<>();

    private static final Object monitor = new Object();
    private static volatile boolean pausa = false;
    private static volatile boolean interrupcionIO = false;
    private static volatile boolean errorProceso = false;

    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);

        int numProcesos;

        while (true){
            try {
                System.out.println("Introduce numero de procesos: ");
                numProcesos = teclado.nextInt();
                if (numProcesos > 0) break;
            }catch (RuntimeException e){
                System.out.println("Introduce un numero valido de procesos");
                teclado.next();
            }
        }

        teclado.nextLine();
        llenarProcesos(numProcesos);

        String opUsr = " ";
        while (!opUsr.toLowerCase().contains("y")){
            clearScreen();
            System.out.printf("\nDeseas Ejecutar los procesos? Y/N \n");

            opUsr = teclado.nextLine();
            if (opUsr.equalsIgnoreCase("n")){
                System.exit(-1);
            }
        }

        Thread hiloTeclado = new Thread(() -> {
            System.out.println("Comandos: 'p' (Pausar) | 'c' (Continuar) | 'e' (Interrupcion I/O) | 'w' (Error)");

            while (true){
                String respuestaUsr = teclado.nextLine().trim().toLowerCase();
                switch (respuestaUsr){
                    case "p":
                        pausa = true;
                        System.out.println("Pausa solicitada...");
                        break;
                    case "c":
                        pausa = false;
                        System.out.println("Continuando...");
                        synchronized (monitor){
                            monitor.notify();
                        }
                        break;
                    case "e":
                        System.out.println("Interrupcion solicitada...");
                        interrupcionIO = true;
                        break;
                    case "w":
                        System.out.println("Error provocado...");
                        errorProceso = true;
                        break;
                    default:
                        System.out.println("Opcion no valida");
                        break;
                }
            }
        });

        hiloTeclado.setDaemon(true);
        hiloTeclado.start();

        ejecutarProcesos();
    }

    private static void llenarProcesos(int numProcesos){
        int contadorProcesos = 0;
        int numProcesosPorLote = 3;

        Lotes l = new Lotes();
        ArrayList<Procesos> procesos = new ArrayList<>();

        int lotes = Math.floorDiv(numProcesos, numProcesosPorLote);

        for (int i = 0; i < lotes; i++) {
            for (int j = 0; j < numProcesosPorLote; j++) {
                procesos.add(new Procesos());
                clearScreen();
                for (Procesos p : procesos){
                    System.out.printf("\nProceso N: %d || Tiempo estimado: %d || Operacion: %s || Valor A: %d || Valor B: %d",p.getPID(), p.getTiempoMax(), p.getOperacion(), p.getValores()[0], p.getValores()[1]);
                }
                try { Thread.sleep((int) ( Math.random()  * 700 )); } catch (InterruptedException e) { }
                contadorProcesos++;
            }
            l.setListaProcesos(procesos);
            colaLotes.add(l);
            l = new Lotes();
            procesos = new ArrayList<>();
        }
        mostrarProcesosEnCola();

        if (contadorProcesos < numProcesos){
            procesos = new ArrayList<>();
            for (int i = contadorProcesos; i < numProcesos; i++) {
                procesos.add(new Procesos());
            }
            Lotes l_2 = new Lotes();
            l_2.setListaProcesos(procesos);
            colaLotes.add(l_2);
        }
        ordenarProcesos();
    }

    private static void ordenarProcesos(){
        int contadorLotes = 0;
        for (Lotes l : colaLotes){
            System.out.printf("\nLote numero : %d \n", contadorLotes);
            l.ordenarProcesos();
            l.comprobarOrdenamiento();
            contadorLotes++;
        }
    }

    private static void ejecutarProcesos(){
        int lotesActuales = 1;
        int procesoActual_int = 1;

        Lotes loteTerminado = new Lotes();

        while (!colaLotes.isEmpty()){
            Lotes loteActual = colaLotes.pop();
            ArrayList<Procesos> procesoPendientes = new ArrayList<>(loteActual.getListaProcesos());
            ArrayList<Procesos> procesosTerminados = new ArrayList<>();

            int procesoLote = 1;

            while (!procesoPendientes.isEmpty()){
                int tamañoPendientes = procesoPendientes.size();
                Procesos p = procesoPendientes.remove(tamañoPendientes - 1);

                // --- BLOQUE 2: RENDERIZADO DE PANTALLA ---
                clearScreen();
                
                if(!lotesCompletados.isEmpty()){
                    System.out.println("---------- LOTES ANTERIORES CONCLUIDOS ----------");
                    for (int i = 0; i < lotesCompletados.size(); i++) {
                        System.out.println("Lote #" + (i + 1));
                        for (Procesos pp : lotesCompletados.get(i).getListaProcesos()) {
                            // CORRECCIÓN 1: Aquí imprimías 'p.getPID()'. 'p' es el proceso actual.
                            // Cambié todas las 'p' por 'pp' para que imprima la información de los procesos ya guardados.
                            System.out.printf(
                            "  [PID: %d] | Op: %s | Val A: %d Val B: %d | Res: %s | TME: %d \n",
                            pp.getPID(), pp.getOperacion(),
                            pp.getValores()[0], pp.getValores()[1],
                            pp.getResultado_operacion() == null ? "N/A" : pp.getResultado_operacion(), pp.getTiempoMax());
                        }
                    }
                    System.out.println("-------------------------------------------------");
                }

                // CORRECCIÓN 2: Eliminé el bucle for(int i=0...) que tenías aquí.
                // Ese bucle estaba imprimiendo el MISMO proceso actual 'p' repetidas veces 
                // dependiendo del tamaño de la lista. Solo necesitamos imprimirlo una vez:
                System.out.println("\n[ PROCESO EN EJECUCIÓN (Lote actual: " + lotesActuales + ") ]");
                System.out.printf(
                        "  ▶ PID: %d | Op: %s | Val A: %d | Val B: %d | TME: %d \n",
                        p.getPID(), p.getOperacion(), p.getValores()[0], p.getValores()[1], p.getTiempoMax());

                System.out.println("\n[ PROCESOS CONCLUIDOS DE ESTE LOTE ]");
                if (procesosTerminados.isEmpty()) System.out.println("  (Ninguno)");
                for (Procesos pp : procesosTerminados) {
                    System.out.println("  ✔ ID: " + pp.getPID() + " Operacion: " + pp.getOperacion() + " | Res: " + pp.getResultado_operacion());
                }

                System.out.println("\n[ POR CONCLUIR (PENDIENTES DEL LOTE) ]");
                if (procesoPendientes.isEmpty()) System.out.println("  (Es el último del lote)");
                for (Procesos pp : procesoPendientes) {
                    System.out.println("  ⌛ PID: " + pp.getPID() + " | TME Estimado: " + pp.getTiempoMax());
                }


                // --- BLOQUE 3: EL SEMÁFORO (PAUSA) ---
                // La pantalla ya está dibujada. Si el usuario pausó, se queda viendo la información correcta.
                synchronized (monitor){
                    while (pausa){
                        try{
                            System.out.println("\n[ SISTEMA PAUSADO - Esperando comando 'c' ]");
                            monitor.wait();
                        }catch (InterruptedException ex){
                            Thread.currentThread().interrupt();
                        }
                    }
                }

                // --- BLOQUE 4: EJECUCIÓN Y TIEMPO ---
                // CORRECCIÓN 3: Movemos la simulación de tiempo de procesamiento AQUÍ.
                // Se ejecuta DESPUÉS de comprobar la pausa, así el programa responde rápido.
                // Multiplico por 1000L asumiendo que el TME está en segundos. Ajusta si son milisegundos.

                // Ejecutar logica interna
                if (!errorProceso) {
                    p.run();
                    try {
                    Thread.sleep(p.getTiempoMax() * 10L);
                } catch (InterruptedException ex) {}
                }else{
                    p.setResultado_operacion("ERROR");
                    p.run(0);
                    errorProceso = false;
                }


                
                
                procesosTerminados.add(p);
                procesoLote++;
                procesoActual_int++;
            }

            // Lote terminado, guardar en histórico
            loteTerminado.setListaProcesos(procesosTerminados);
            lotesCompletados.add(loteTerminado);
            loteTerminado = new Lotes();
            lotesActuales++;
        }
        
        clearScreen();
        System.out.println("=========================================");
        System.out.println(" TODOS LOS LOTES HAN SIDO PROCESADOS ");
        System.out.println("=========================================");

        imprimirDetallesTerminados(lotesCompletados);
    }

    static void imprimirDetallesTerminados(ArrayList<Lotes> l){
        System.out.println("---------- LOTES ANTERIORES CONCLUIDOS ----------");
        for (int i = 0; i < lotesCompletados.size(); i++) {
            System.out.println("Lote #" + (i + 1));
            for (Procesos pp : lotesCompletados.get(i).getListaProcesos()) {
                // CORRECCIÓN 1: Aquí imprimías 'p.getPID()'. 'p' es el proceso actual.
                // Cambié todas las 'p' por 'pp' para que imprima la información de los procesos ya guardados.
                System.out.printf(
                "  [PID: %d] | Op: %s | Val A: %d Val B: %d | Res: %s | TME: %d \n",
                pp.getPID(), pp.getOperacion(),
                pp.getValores()[0], pp.getValores()[1],
                pp.getResultado_operacion() == null ? "N/A" : pp.getResultado_operacion(), pp.getTiempoMax());
            }
        }
        System.out.println("-------------------------------------------------");
    }

    static void imprimirProcesosDetalles(ArrayList<Procesos> terminados){
        clearScreen();
        for (int i = 0; i < lotesCompletados.size()+1; i++){
            int j = 0;
            for (Procesos p : terminados){
                System.out.printf(
                        "PID: %d" +
                        "Operacion : %s" +
                        "Valor A: %d" +
                        "Valor B: %d" +
                        "Resultado : %s" +
                        "TME: %d", p.getPID(),p.getOperacion(), p.getValores()[0], p.getValores()[1],terminados.get(j).getResultado_operacion(), p.getTiempoMax());
                j++;
            }
        }
    }

    public static void mostrarProcesosEnCola(){
        clearScreen();
        for (Lotes l : colaLotes){
            ArrayList<Procesos> lista = l.getListaProcesos();
            for (Procesos p : lista){
                System.out.printf("\nProceso N: %d || Tiempo estimado: %d || Operacion: %s || Valor A: %d || Valor B: %d",p.getPID(), p.getTiempoMax(), p.getOperacion(), p.getValores()[0], p.getValores()[1]);
            }
        }
    }

    // Limpia la terminal en Arch Linux / Bash
    static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }
}