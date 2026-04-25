package org.Alpha.Sistemas_Op.Programa_06;

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
            if (tamañoMax < 18){
                return false;
            }else {
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
            t.setDato(false);
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

        //l.imprimirTail();
    }
}
