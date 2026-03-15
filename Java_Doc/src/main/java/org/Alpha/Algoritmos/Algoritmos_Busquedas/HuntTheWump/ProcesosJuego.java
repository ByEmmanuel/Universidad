package org.Alpha.Algoritmos.Algoritmos_Busquedas.HuntTheWump;

import java.util.ArrayList;
import java.util.List;

class ProcesosJuego {
    List<Vertices> listaVertices = new ArrayList<>();

    private void facil() {
        System.out.println("FACIL");
    }

    private void medio() {
        System.out.println("MEDIO");
    }

    private void dificil() {
        System.out.println("DIFICIL");
    }


    void ejecucionDificultad(String dificultad) {
        switch (dificultad) {
            case "f":
                facil();
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
