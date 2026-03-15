package org.Alpha.Sistemas_Op.Programa_02;

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
    private static int ticksEjecucion = 0;

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
                    case "i":
                        System.out.println("Interrupcion solicitada...");
                        interrupcionIO = true;
                        break;
                    case "e":
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
        int numProcesosPorLote = 5;

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
                try { Thread.sleep((int) ( Math.random()  * 300 )); } catch (InterruptedException e) { }
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
                //clearScreen();

                //imprimirDetallesProcesos(lotesActuales, procesosTerminados, procesoPendientes, p);

                // En lugar de un solo sleep largo, hacemos muchos cortitos
                
                boolean canceladoPorError = false;
                boolean canceladoPorInterrupcion = false;
                
                int ticksTotales = p.getTiempoMax() * 100; 
                

                // despues de este for para revisar si se presiono una tecla se ejecuta el proceso
                while (p.getTiempoMax() > 0) {

                    // --- BLOQUE 3: EL SEMÁFORO (PAUSA) ---
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

                    try {
                        Thread.sleep(300);
                    } catch (InterruptedException ex) {
                        Thread.currentThread().interrupt();
                    }

                    // limpiar pantalla aqui y mostrarla 
                    ticksEjecucion++;
                    p.setTiempoMax(p.getTiempoMax()-1);
                    imprimirDetallesProcesos(lotesActuales, procesosTerminados, procesoPendientes, p);

                    // Despues de cada fracción de segundo revisamos si se oprimio 'w'
                    if (errorProceso) {
                        canceladoPorError = true;
                        errorProceso = false; 
                        break; 
                    }else if (interrupcionIO) {
                        procesoPendientes.add(0, p);
                        canceladoPorInterrupcion = true;
                        interrupcionIO = false;
                        break;
                    }
                }
                p.setTiemopEjecucion(ticksEjecucion);
                if (canceladoPorError) {
                    p.setResultado_operacion("ERROR");
                    p.run(0); // lógica para cuando hay error
                    //canceladoPorError = false; -> esto no es necesario ya que cada while se crea la variable
                }
                else if (canceladoPorInterrupcion) {
                    continue;
                } else{
                    p.run();  // Ejecución normal si no hubo errores
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

    private static void imprimirDetallesProcesos(int lotesActuales, ArrayList<Procesos> procesosTerminados, ArrayList<Procesos> procesoPendientes, Procesos p){
        // este bloque puede ser una funcion en otra clase o despues en una funcion
                clearScreen();
                if(!lotesCompletados.isEmpty()){
                    System.out.println("---------- LOTES ANTERIORES CONCLUIDOS ----------");
                    for (int i = 0; i < lotesCompletados.size(); i++) {
                        System.out.println("Lote #" + (i + 1));
                        for (Procesos pp : lotesCompletados.get(i).getListaProcesos()) {
                            System.out.printf(
                            "  [PID: %d] | Op: %s | Val A: %d Val B: %d | Res: %s | TME: %d | TE: %d \n",
                            pp.getPID(), pp.getOperacion(),
                            pp.getValores()[0], pp.getValores()[1],
                            pp.getResultado_operacion() == null ? "N/A" : pp.getResultado_operacion(), pp.getTiempoMax(), pp.getTiemopEjecucion());
                        }
                    }
                    System.out.println("-------------------------------------------------");
                }

                System.out.println("\n[ PROCESO EN EJECUCIÓN (Lote actual: " + lotesActuales + ") ] TIEMPO EN EJECUCION GLOBAL: " + ticksEjecucion);
                System.out.printf(
                        "  >> PID: %d | Op: %s | Val A: %d | Val B: %d | TME: %d \n",
                        p.getPID(), p.getOperacion(), p.getValores()[0], p.getValores()[1], p.getTiempoMax());

                System.out.println("\n[ PROCESOS CONCLUIDOS DE ESTE LOTE ]");
                if (procesosTerminados.isEmpty()) System.out.println("  (Ninguno)");
                for (Procesos pp : procesosTerminados) {
                    System.out.println("  >> ID: " + pp.getPID() + " Operacion: " + pp.getOperacion() + " | Res: " + pp.getResultado_operacion() + "| TEJ: " + pp.getTiemopEjecucion() + "| TME: " + pp.getTiempoMax());
                }

                System.out.println("\n[ PROCESOS PENDIENTES DEL LOTE ]");
                if (procesoPendientes.isEmpty()) System.out.println("  (Es el último del lote)");
                for (int i = procesoPendientes.size()-1; i >= 0; i--) {
                    Procesos pp = procesoPendientes.get(i);
                    System.out.println("  ⌛ PID: " + pp.getPID() + " | TME Estimado: " + pp.getTiempoMax());
                }
                System.out.println("\nLotes Pendientes: " + colaLotes.size());
    }

    static void imprimirDetallesTerminados(ArrayList<Lotes> l){
        System.out.println("---------- LOTES ANTERIORES CONCLUIDOS ----------");
        for (int i = 0; i < lotesCompletados.size(); i++) {
            System.out.println("Lote #" + (i + 1));
            for (Procesos pp : lotesCompletados.get(i).getListaProcesos()) {
                // CORRECCIÓN 1: Aquí imprimía 'p.getPID()'. 'p' es el proceso actual.
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