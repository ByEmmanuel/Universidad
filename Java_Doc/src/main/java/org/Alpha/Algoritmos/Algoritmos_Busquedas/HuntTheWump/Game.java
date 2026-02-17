package org.Alpha.Algoritmos.Algoritmos_Busquedas.HuntTheWump;
import javax.management.RuntimeErrorException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


// Definicion del problema
/* Crear El videojuego hunt the wumpus
*  Tendras el modo de juego facil, medio, dificil y modo aventura
*  Los modos constaran de N nodos; N sera el tamaño del grafo
*
* */

class Vertices  {


}


class ProcesosJuego{
    List<Vertices> listaVertices = new ArrayList<>();

    private void facil(){
        System.out.println("FACIL");
    }

    private void medio(){
        System.out.println("MEDIO");
    }

    private void dificil(){
        System.out.println("DIFICIL");
    }


    void ejecucionDificultad(String dificultad){
        switch (dificultad){
            case "f": facil(); break;
            case "m": medio(); break;
            case "d": dificil(); break;
        }
    }

}




public class Game {

    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
        while(true){
            try{
                String[] dificultades = {"Facil", "Medio", "Dificil"};
                for (String s: dificultades){System.out.println(s);}
                System.out.print("\nIngrese dificultad : \nF - Facil \nM - Media \nD- DIficil");

                String dif_Usr = teclado.next();
                dif_Usr = dif_Usr.toLowerCase();
                while (!dif_Usr.contains("f") && !dif_Usr.contains("m") && !dif_Usr.contains("d")){
                    dif_Usr = teclado.next();
                    dif_Usr = dif_Usr.toLowerCase();
                }

                ProcesosJuego procesosJuego = new ProcesosJuego();
                procesosJuego.ejecucionDificultad(dif_Usr);
            }catch (RuntimeErrorException e){
                System.out.println("Error en la funcion");
            }
        }
    }
}
