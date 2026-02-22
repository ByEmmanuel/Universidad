//package org.Alpha.Sistemas_Op.Programa_02;

import java.util.*;

public class Lotes {
    private ArrayList<Procesos> listaProcesos = new ArrayList<>();

    public Lotes(ArrayList<Procesos> listaProcesos) {
        this.listaProcesos = listaProcesos;
    }

    public Lotes() {

    }

    public ArrayList<Procesos> getListaProcesos() {
        return listaProcesos;
    }

    public void setListaProcesos(ArrayList<Procesos> listaProcesos) {
        this.listaProcesos = listaProcesos;
    }

    public void ordenarProcesos(){
        ArrayList<Procesos> arr = listaProcesos;
        listaProcesos.sort(Comparator.comparingInt(Procesos::getPID));
    }

    public void comprobarOrdenamiento(){
        for (Procesos p : listaProcesos){
            System.out.printf("Proceso: %d \n",p.getPID());
        }
    }


}
