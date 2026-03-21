package org.Alpha.JavaFX.HuntTheWumpusLogic;


import java.util.ArrayList;
import java.util.Map;
import java.util.Stack;

public class Nodo {

    // Coordenadas+
    //private int ID = 0;
    private final char id;
    private int x = 0;
    private int y = 0;
    private boolean wumpus = false;
    private boolean jugador  = false;

    public Nodo(int ID){
        this.id = (char) ID;
    }

    // Lista de vertices
    private ArrayList<Nodo> lista_vertices = new ArrayList<>();


    //
    public boolean existeVerticeConNodo(int verticeNum){
        for (int i = 0; i < lista_vertices.size(); i++) {
            if (lista_vertices.get(i).getId() == (char) verticeNum){
                return true;
            }
        }
        return false;
    }

    public boolean sonAdyacentes(int A, int B){
        /*short nodo1 = 0, nodo2 = 0;
        for(Vertices v : lista_vertices){
            char verticeId = v.getA().getId();
            if (verticeId  == (char) A ){
                nodo1++;
            }
            if (verticeId == (char) B){
                nodo2++;
            }
        }
        return nodo1 == nodo2;*/
        boolean r1 = existeVerticeConNodo(A);
        boolean r2 = existeVerticeConNodo(B);
        return r1 && r2;
    }


    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }


    public ArrayList<Nodo> getLista_vertices() {
        return lista_vertices;
    }
    /*
    public void setLista_vertices(ArrayList<Vertices> lista_vertices) {
        this.lista_vertices = lista_vertices;
    }*/

    public char getId() {
        return id;
    }

    public boolean isWumpus() {
        return wumpus;
    }

    public void setWumpus(boolean wumpus) {
        this.wumpus = wumpus;
    }

    public boolean isJugador() {
        return jugador;
    }

    public void setJugador(boolean jugador) {
        this.jugador = jugador;
    }
}
