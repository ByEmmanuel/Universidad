package org.Alpha.JavaFX.HuntTheWumpusLogic;

public class Vertices {

    // un vertice nada más puede apuntar a 2 nodos
    private Nodo A;
    private Nodo B;

    public Vertices(int verticeA, int verticeB){
        this.A = new Nodo(verticeA);
        this.B = new Nodo(verticeB);
    }

    public Vertices(Nodo verticeA){
        this.A = verticeA;
    }

    public Vertices(int verticeA){
        this.A = new Nodo(verticeA);
    }

    public Nodo getA() {
        return A;
    }

    public Nodo getB() {
        return B;
    }
    /*public void setA(Nodo a) {
        A = a;
    }


    public void setB(Nodo b) {
        B = b;
    }*/
}
