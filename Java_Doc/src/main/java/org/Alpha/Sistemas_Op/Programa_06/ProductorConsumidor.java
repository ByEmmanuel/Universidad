package org.Alpha.Sistemas_Op.Programa_06;

import java.util.*;

public class ProductorConsumidor {
    static class Nodo{
        Nodo sig;
        private boolean dato;

        Nodo(Nodo sig, boolean dato){
            this.sig = sig;
            this.dato = dato;
        }

        Nodo(boolean dato){
            this.dato = dato;
        }

        public boolean getDato(){
            return dato;
        }

        public void setDato(boolean d){
            this.dato = d;
        }
    }

    static class ListaCircular{
        int tamañoActual = 0;
        int tamañoMax = 0;
        Nodo h;
        Nodo t;
        Nodo temp;

        ListaCircular(int tamaño){
            this.tamañoMax = tamaño;
            this.h = null;
            this.t = null;
        }

        public boolean insertar(){
            if (tamañoMax >= 18){
                return false;
            }else {
                this.tamañoActual++;
                if (h == null){
                    h = new Nodo(true);
                    t = h;
                    h.sig = null;
                    temp = h;
                    return false;
                }else{
                    Nodo n = new Nodo(true);
                    temp.sig = n;
                    temp = temp.sig;
                    t = temp;

                    // circular
                    //t.sig = h;
                    return true;
                }

            }
        }

        public void removeEnd(){
            //t.setDato(false);
        }

        public void imprimir(){
            Nodo aux = h;
            int contador = 0;
            while (aux != null){
                if (aux.getDato()){
                    System.out.print(contador + " ");
                }else {
                    System.out.print(" _ ");
                }
                System.out.println(aux);
                aux = aux.sig;
                ++contador;
            }
        }

        public void imprimirTail(){
            Nodo aux = t;
            int i = 0;
            while (aux != null){
                System.out.println( "\n" + aux);
                aux = aux.sig;
            }
        }
    }

    public static void main(String[] args) {
        ListaCircular l = new ListaCircular(18);
        l.insertar();
        l.insertar();
        l.insertar();
        l.removeEnd();
        l.imprimir();
        System.out.println();
        l.insertar();
        l.insertar();
        l.insertar();
        l.removeEnd();
        l.imprimir();

        /*int tamaño = 18;
        List<Boolean> e = new ArrayList<>();

        for (int i = 0; i <= 18; i++){
            e.addFirst(false);
        }*/

        Scanner t = new Scanner(System.in);
        boolean[] v = new boolean[18];
        // generar numeros random
        Random r = new Random();
        int productorOrConsumidor = 0;
        int espaciosProductor = 0;
        int espaciosConsumidor = 0;
        int posA = 0;
        int posB = 0;

        while (true){
            productorOrConsumidor = r.nextInt(0,2);
            espaciosConsumidor = espaciosProductor = r.nextInt(3,7);

            System.out.println(productorOrConsumidor == 1 ? "Productor " +  espaciosConsumidor: "Consumidor " + espaciosConsumidor);
            for (int i = 0; i < espaciosConsumidor; i++) {
                if (posA >= 18){
                    posA = 0;
                }
                if (posB >= 18) {
                    posB = 0;
                }
                // 1 productor
                if (productorOrConsumidor == 1){

                    if (!v[posB]){
                        v[posB] = true;
                        posB++;
                    }else {
                        System.out.println("Productor durmiendo");
                    }

                    // 2 consumidor
                }else {
                    if (v[posA]){
                        v[posA] = false;
                        posA++;
                    }else {
                        System.out.println("Consumidor durmiendo");
                    }

                }
            }

            for (int i = 0; i < v.length; i++){
                System.out.print((v[i] ?  " X " : " _ "));
            }
            System.out.println( " ");
            try {Thread.sleep(1000);
            } catch (InterruptedException ex) {throw new RuntimeException(ex);}

        }





        //l.imprimirTail();
    }
}
