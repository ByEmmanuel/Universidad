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

    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);

        int numProcesos;

        /*
        * LOGICA DEL SEGUNDO HILO
        * */

        // comprobar si tiene que estar dentro del bucle para ser parte del hilo
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

        // limpiar buffer
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
        //System.out.println(numProcesos);


        Thread hiloTeclado = new Thread(() -> {
           //Scanner scanner = new Scanner(System.in);
            System.out.println("Comandos: 'p' (Pausar) | 'c' (Continuar) | 'e' (Interrupcion I/O) | 'w' (Error)");

            while (true){
                String respuestaUsr = teclado.nextLine().trim().toLowerCase();
                switch (respuestaUsr){
                    case "p":
                        pausa = true;
                        System.out.println("Pausa");
                        break;
                    case "c":
                        pausa = false;
                        System.out.println("Continuar");
                        synchronized (monitor){
                            monitor.notify();
                        }
                        break;
                    case "e":
                        System.out.println("Interrupcion");
                        break;
                    case "w":
                        System.out.println("Error");
                        break;
                    default:
                        System.out.println("Opcion no valida:");
                        break;
                }
            }

        });

        hiloTeclado.setDaemon(true);
        hiloTeclado.start();

        // EJECUTAR PROCESOS UNICAMENTE CUANDO YA NO SE REQUIERA INTRODUCIR MAS
        ejecutarProcesos();


    }

    private static void llenarProcesos(int numProcesos){

        int contadorProcesos = 0;
        int numProcesosPorLote = 3;

        Lotes l = new Lotes();
        ArrayList<Procesos> procesos = new ArrayList<>();

        int lotes = Math.floorDiv(numProcesos, numProcesosPorLote);

        int procesosPares = lotes * numProcesosPorLote;

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
            // cambiar el puntero de datos
            l = new Lotes();
            procesos = new ArrayList<>();
        }
        mostrarProcesosEnCola();

        if (contadorProcesos < numProcesos){
            // esto es menor que numProcesosPorLote
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

        // for (Lotes l : colaLotes)
        while (!colaLotes.isEmpty()){
            Lotes loteActual = colaLotes.pop();
            // procesoPendientes toda via no se usa
            ArrayList<Procesos> procesoPendientes = new ArrayList<>(loteActual.getListaProcesos());
            ArrayList<Procesos> procesosTerminados = new ArrayList<>();

            int procesoLote = 1;

            while (!procesoPendientes.isEmpty()){

                int tamañoPendientes = procesoPendientes.size();

                Procesos p = procesoPendientes.remove(tamañoPendientes - 1);


                // informacion de los completados
                if(!lotesCompletados.isEmpty()){
                    clearScreen();
                    System.out.println("---------- LOTES ANTERIORES CONCLUIDOS ----------");

                    for (int i = 0; i < lotesCompletados.size(); i++) {
                        System.out.println("Operacion #" + (i + 1));
                        for (Procesos pp : lotesCompletados.get(i).getListaProcesos()) {
                            System.out.println("  [PID: " + pp.getPID() + " | Res: " + pp.getResultado_operacion() + "]");
                        }
                    }
                    System.out.println("-----------------------------------");
                }

                /*try{
                    Thread.sleep(p.getTiempoMax()* 100L);
                }catch (InterruptedException ex){}*/
                for (int i = 0; i < procesoPendientes.size() ; i++) {
                    System.out.printf(
                            "\nPID: %d " +
                                    "Operacion : %s " +
                                    "Valor A: %d " +
                                    "Valor B: %d " +
                                    "Resultado : %s " +
                                    "TME: %d \n",
                            p.getPID(), p.getOperacion(),
                            p.getValores()[0], p.getValores()[1],
                            p.getResultado_operacion() == null ? "La operacion no ha sido realizada" : p.getResultado_operacion(), p.getTiempoMax());
                }

                // Sub-sección: Terminados del lote actual
                System.out.println("\n[ PROCESOS CONCLUIDOS DE ESTE LOTE ]");
                if (procesosTerminados.isEmpty()) System.out.println("  (Ninguno)");
                for (Procesos pp : procesosTerminados) {
                    System.out.println("  ✔ ID: " + pp.getPID() + " Operacion: " + pp.getOperacion());
                }

                // Sub-sección: Pendientes del lote actual
                System.out.println("\n[ POR CONCLUIR (PENDIENTES DEL LOTE) ]");
                if (procesoPendientes.isEmpty()) System.out.println("  (Es el último del lote)");
                for (Procesos pp : procesoPendientes) {
                    System.out.println("  ⌛ PID: " + pp.getPID());
                }

                // MUY IMPORTANTE AQUI; EL HILO PRINCIPAL TIENE QUE ESCUCHAR RESPUESTAS DEL USUARIO
                synchronized (monitor){
                    while (pausa){
                        try{
                            System.out.println("Systema pausado");
                            monitor.wait();
                        }catch (InterruptedException ex){
                            Thread.currentThread().interrupt();
                            System.err.println("Hilo interrumpido inesperadamente");
                        }
                    }
                }

                //System.out.printf("\n> Procesos Totales N: %d \n", procesoActual);
                System.out.printf("\n>Proceso N:%d En el lote: %d \n", procesoLote, lotesActuales);
                p.run();
                //System.out.println(p.getResultado_operacion());

                // proceso terminado
                procesosTerminados.add(p);
                //imprimirProcesosDetalles(procesosTerminados);
                // imprimir lotes proximos

                try{Thread.sleep(1000);}catch (InterruptedException ex){}

                // System.out.println("---------- LOTES ANTERIORES CONCLUIDOS ----------");
                // for (int i = 0; i < lotesCompletados.size(); i++){
                //     System.out.println("Lote   AS #" + (i + 1));
                //     for (Procesos proConcluido : lotesCompletados.get(i).getListaProcesos()){
                        
                //     }
                //     System.out.println("");
                // }

                procesoLote++;
                procesoActual_int++;
                

            }
            // lote terminado

            // reiniciar la lista sin perder el puntero
            loteTerminado.setListaProcesos(procesosTerminados);
            //procesosTerminados = new ArrayList<>();
            lotesCompletados.add(loteTerminado);
            loteTerminado = new Lotes();


            // principio de simply linked list
            /*
            ArrayDeque<Lotes> tmp = colaLotes;
            tmp.pop();
            colaLotes = tmp;
            */
            lotesActuales++;
        }
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
                        "Resultado : %d" +
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
                // limpiar la pantalla, mostrar procesos acumulandose
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