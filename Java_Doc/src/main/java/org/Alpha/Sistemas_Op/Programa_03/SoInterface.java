//package org.Alpha.Sistemas_Op.Programa_03;

import java.util.ArrayDeque;
import java.util.Scanner;

public interface SoInterface {
    // variables / funciones que siempre se ejecutaran en los programas de SO

    Scanner teclado = new Scanner(System.in);
    // cola de procesos
    ArrayDeque<Procesos> colaProcesos = new ArrayDeque<>();

    static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    static void threadDelay(int nmilis){
        try{
            Thread.sleep(nmilis);
        }catch (InterruptedException ex){

        }
    }



}
