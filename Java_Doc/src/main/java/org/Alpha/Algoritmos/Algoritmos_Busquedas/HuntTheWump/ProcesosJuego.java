package org.Alpha.Algoritmos.Algoritmos_Busquedas.HuntTheWump;

import org.Alpha.JavaFX.HuntTheWumpusLogic.Nodo;
import org.Alpha.JavaFX.HuntTheWumpusLogic.Vertices;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

class ProcesosJuego {

    private final Random random = new Random();

    private void imprimirGrafo(ArrayList<Nodo> listAdj){

        for (Nodo n : listAdj){
            ArrayList<Nodo> lista = n.getLista_vertices();
            System.out.printf("Nodo: %c Vertices : ", n.getId());
            for (Nodo nodo : lista) {
                System.out.printf("%s || ", nodo.getId());
            }
            System.out.println(" ");

        }

    }


    private void facil(Scanner teclado) {
        int numNodos = random.nextInt(20);
        int tamaño = 12;
        ArrayList<Nodo> vertices = new ArrayList<>(tamaño);

        // Letra que representara al vertice
        int ascii = 97;
        for (int i = 0; i < tamaño; i++) {
            vertices.add(new Nodo(ascii++));
        }

        // llenar matrices
        for (int k = 0; k < tamaño; k++) {
            // cada vertice tendra cuatro aristas

            //int conexionesAdyacentes = random.nextInt(4);
            int conexionesAdyacentes = 3;
            int i = 0;
            while (i < conexionesAdyacentes) {
                int nodoA = random.nextInt(97, ascii);
                //int nodoB = random.nextInt(97, ascii);


                // obtener el k-esimo elemento
                Nodo nodoActualizar = vertices.get(k);

                if (!nodoActualizar.existeVerticeConNodo(nodoA) && nodoA != nodoActualizar.getId()){
                    Nodo tmp = buscarNodo(vertices,nodoA);
                    nodoActualizar.getLista_vertices().add(tmp);

                    for (int l = 0; l < vertices.size(); l++){
                        Nodo v = vertices.get(l);
                        if (v.getId() == nodoA){
                            v.getLista_vertices().add(nodoActualizar);
                        }
                    }

                    /*
                    * Nodo destino = buscarNodo(vertices, nodoA);
                        if (destino == null) continue;
                    * */

                    i++;
                }
            }
        }

        // poner al wumpus en alguna sala random
        int wumpusSala = random.nextInt(97, ascii);
        Nodo salaWumpus = buscarNodo(vertices, wumpusSala);
        if (salaWumpus != null){
            salaWumpus.setWumpus(true);
            System.out.println("Se coloco un wumpus");
        }else{
            System.out.println("No hay wumpus dispnibles reinicia el juego");
        }

        int salaRespawn = random.nextInt(97, ascii);
        Nodo jugadorSpwan = buscarNodo(vertices, salaRespawn);
        if (jugadorSpwan != null){
            jugadorSpwan.setJugador(true);
            System.out.println("Se coloco un jugador");
        }else{
            System.out.println("No hay jugadores");
        }


        Nodo salaJugadr = buscarJugador(vertices);
        while (true){


            /*try{
                Thread.sleep(2000);
            }catch (InterruptedException e){
                System.out.println("Si");
            }*/


            //int salaJug = random.nextInt(97,ascii);


            if (salaJugadr == null){
                System.out.println("No hay sala con jugador");
                break;
            }

            System.out.println("Estas en la sala: " +  salaJugadr.getId());
            // imprimir vecinos
            char[] vecinos = new char[salaJugadr.getLista_vertices().size()];
            int i = 0;
            for (Nodo n : salaJugadr.getLista_vertices()){
                System.out.print(" | " + n.getId());
                vecinos[i++] = n.getId();
            }

            String salaOpcUsr = "0";
            while (!salaOpcUsr.matches("^[a-z]$")){
                System.out.println("\nIntroduce la sala a moverte: ");

                salaOpcUsr = teclado.next();


                String vecinosString = Arrays.toString(vecinos);
                if (!vecinosString.contains(salaOpcUsr)){
                    System.out.printf("\nIntroduce un vecino de %s : para moverte\n", salaJugadr.getId());
                    salaOpcUsr = "0";
                }
                /*for (char c : vecinos){
                    // si la opcion pulsada no es vecino
                    if (c != ){
                        salaOpcUsr = "0";
                        System.out.printf("\nIntroduce un vecino de %s : para moverte\n", salaJugadr.getId());
                        continue;
                    };
                }*/
            }
            salaJugadr.setJugador(false);
            salaJugadr = buscarNodo(vertices, (int) salaOpcUsr.charAt(0));
            if (salaJugadr != null){
                salaJugadr.setJugador(true);
            }

            assert salaJugadr != null;
            if (estatusWumpus(salaJugadr)){
                System.out.println("¡Huele extraño!");
            }

            if (salaJugadr.getId() == salaWumpus.getId()){
                System.out.println("Perdiste");
                System.exit(-1);
            }

            //imprimirGrafo(vertices);
        }


    }

    private boolean estatusWumpus(Nodo posicionJugador){
        for (Nodo n : posicionJugador.getLista_vertices()){
            if (n.isWumpus()){
                return true;
            }
        }
        return false;
    }

    private Nodo buscarNodo(ArrayList<Nodo> l, int intNodoAbuscar) {
        for (Nodo n : l){
            if (n.getId() == intNodoAbuscar){
                return n;
            };
        }
        return null;
    }

    private Nodo buscarJugador(ArrayList<Nodo> l){
        for (Nodo n : l){
            ArrayList<Nodo> v = n.getLista_vertices();
            for (Nodo nodo : v) {
                if (nodo.isJugador()) {
                    return n;
                }
            }
        }
        return null;

    }


    //System.out.println("FACIL");


    private static void medio() {
        System.out.println("MEDIO");
    }

    private static void dificil() {
        System.out.println("DIFICIL");
    }


    public void ejecucionDificultad(String dificultad, Scanner t) {
        switch (dificultad) {
            case "f":
                facil(t);
                break;
            case "m":
                medio();
                break;
            case "d":
                dificil();
                break;
        }
    }

}
