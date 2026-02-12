package org.Alpha.Sistemas_Op;

import java.util.*;


class Lotes{
    private String nombre_programador = null;
    private List<Map<String, Integer[]>> procesos = new ArrayList<>();
    private int num_proceso = Math.toIntExact(Math.round(Math.random()) * 100);

    public Lotes(String nombre_programador, Vector<String> procesos) {
        this.nombre_programador = nombre_programador;
        //this.procesos = procesos;
    }

    public Lotes() {}
    // un lote contiene solo 4 procesos

    // suma y resta
    public int suma(int a, int b){return a+b;}
    public int  multiplicacion(int a, int b){return a * b;}
    public double division(int a, int b){
        try {
            if (b == 0){
                throw new RuntimeException();
            };
            return ((double) a / b);
        }catch (RuntimeException e){
            System.out.println("No se puede divir entre 0");
            return 0;
        }
    }
    public int residuo(int a, int b){return a % b;}
    public double potencia(int a, int b){return Math.pow(a,b);}

    public String getNombre_programador() {
        return nombre_programador;
    }

    public void setNombre_programador(String nombre_programador) {
        this.nombre_programador = nombre_programador;
    }

    public int getNum_proceso() {
        return num_proceso;
    }

    /*public Map<String, Integer[]> getProcesos() {
        return procesos;
    }

    public void setProcesos(String proceso, Integer[] operaciones) {
        this.procesos.put(proceso, operaciones);
    }*/
    public void setProcesos(Map<String, Integer[]> map) {
        this.procesos.add(map);
    }
}

public class Programa_01 {
    static Stack<Lotes> pila_ejecucion = new Stack<>();


    static void print_operaciones(){
        String[] opciones = {"+","-","*","/","%","^"};
        System.out.println("Escribe las operaciones que se haran conforme a su operador simbolico");

        for(String s : opciones) System.out.println(s);
    }

    static void operadores(Scanner teclado, Integer[] valores){
        try {
            if (valores[0] != null){
                System.out.println("Ingresa el valor de a");
                valores[0] = teclado.nextInt();
            }
            if (valores[1] != null){
                System.out.println("Ingresa el valor de b");
                valores[1] = teclado.nextInt();
            }
        }catch (IllegalFormatConversionException e){
            System.out.println("Ingresa solo numeros ");
            operadores(teclado, valores);
        }
    }


    static void procesos(int n){
        print_operaciones();
        Scanner teclado = new Scanner(System.in);

        String str_op = null;
        int num_operacion = 0;
        // setear todas las operaciones


        int contador = 1;
        Lotes lote = new Lotes();

        for(int i = 0; i < n; i++){
            HashMap<String, Integer[]> operaciones = new HashMap<>();

            System.out.printf("Ingresa una operacion despues presiona enter \nNumero de Operacion: %d \n", num_operacion);
            str_op = teclado.next();

            // validacion para que sea una operacion valida
            while (!str_op.contains("+") || !str_op.contains("-") || !str_op.contains("*") || !str_op.contains("/") || !str_op.contains("%") || !str_op.contains("^")){
                System.out.println("Ingresa una operacion valida");
                str_op = teclado.next();
            }

            // se puede cambiar a double
            //Integer a = null, b = null;
            Integer[] valores = new Integer[2];
            operadores(teclado, valores);

            System.out.printf("\n operadores = %d , %d", valores[0] , valores[1]);
            operaciones.put(str_op, valores);
            lote.setProcesos(operaciones);

            if (contador % 4 == 0){
                pila_ejecucion.add(lote);
                lote = new Lotes();
            }

            //opreaciones.add(tmp);
            str_op = null;
            num_operacion++;
            contador++;

        }
        // Guardar último lote si quedaron operaciones
        // Después del for
        if ((contador - 1) % 4 != 0) {  // Si no terminó justo en múltiplo de 4
            pila_ejecucion.add(lote);
        }

    }

    static void ejecucion(){
        int contador = 0;
        for (Lotes l : pila_ejecucion){
            if (contador > 4){contador = 0;}
            //String operacion = l.getProcesos().;
            List<String> claves = new ArrayList<>(l.getProcesos().keySet());
            String string_unico_claves = claves.get(contador); // indice
            Integer[] valores = l.getProcesos().get(string_unico_claves);
            switch (string_unico_claves){
                case ("+"): l.suma();
                case ("-"):
                case ("*"):
                case ("/"):
                case ("%"):
                case ("^"):
            }
            contador++;
        }

    }

    static void tiempo(){

    }


    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
        int procesos = 0;

        while (true){
            System.out.println("Introduce numero de procesos");
            try{
                procesos = teclado.nextInt();
                if (procesos > 0){

                }
            }catch (IllegalFormatConversionException e){
                System.out.println("Ingresa un numero entero");
            }

        }

    }
}
