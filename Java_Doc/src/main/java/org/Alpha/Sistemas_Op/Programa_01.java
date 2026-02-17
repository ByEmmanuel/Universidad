package org.Alpha.Sistemas_Op;

import java.util.*;
class Tiempo{

    private long inicio = 0;
    private long fin = 0;

    public void init(){
        inicio = System.nanoTime();
    }

    public void end(){
        fin = System.nanoTime();

    }

    public long calculateTime_nano(){
        return fin - inicio;
    }

    public long calculateTime_milis(){
        return (long) ((fin - inicio)/ 1_000_000.0);
    }
}


class Proceso {
    private Map<String, Integer[]> lista_procesos = new HashMap<>();
    private String nombre_programador = null;
    //private final long num_proceso = Math.round(Math.random()*10000);

    private String num_proceso = null;
    public Proceso(String proceso, Integer[] operadores, String nombre_programador) {
        this.lista_procesos.put(proceso, operadores);
        this.nombre_programador = nombre_programador;
    }
    /*
    *
    * */
    public String getNum_proceso() {
        return num_proceso;
    }

    public void procesar(){
        System.out.printf("\nProgramador %s: \n", nombre_programador);
        Map.Entry<String, Integer[]> entrada = lista_procesos.entrySet().iterator().next();
        String operacion = entrada.getKey();
        Integer[] valores = entrada.getValue();

        try{
            switch (operacion){
                case ("+"):{
                    System.out.printf("Operacion %d + %d = %d \n", valores[0], valores[1], (valores[0] + valores[1]) );
                    break;
                }
                case ("-"):{
                    System.out.printf("Operacion %d - %d = %d \n",  valores[0], valores[1], (valores[0] - valores[1]) );
                    break;
                }
                case ("*"):{
                    System.out.printf("Operacion %d * %d = %d \n", valores[0], valores[1], (valores[0] * valores[1]) );
                    break;
                }
                case ("/"):{
                    System.out.printf("Operacion %d / %d = %d \n", valores[0], valores[1], (valores[0] / valores[1]) );
                    break;
                }
                case ("%"):{
                    System.out.printf("Operacion %d %% %d = %d \n", valores[0], valores[1], (valores[0] % valores[1]) );
                    break;
                }
                case ("^"):{
                    System.out.printf("Operacion %d ^ %d = %f \n",  valores[0], valores[1], Math.pow(valores[0], valores[1]));
                    break;
                }
            }
        }catch (ArithmeticException e){
            System.out.println("No se puede divir por 0, intenta de nuevo");
        }

    }

    public void setNum_proceso(String n){
        this.num_proceso = n;
    }
}

class Lotes{

    // cada lote contiene una lista con 4 elementos
    private List<Proceso> procesos = new ArrayList<>();

    public Lotes() {}
    // un lote contiene solo 4 procesos

    public List<Proceso> getProcesosList(){
        return this.procesos;
    }
    public void setProcesos(Proceso proceso) {
        this.procesos.add(proceso);
    }
}

public class Programa_01 {


    static ArrayDeque<Lotes> pila_ejecucion = new ArrayDeque<>();
    static ArrayList<String> id_procesos = new ArrayList<>();

    static void print_operaciones(){
        String[] opciones = {"+","-","*","/","%","^"};
        System.out.println("Escribe las operaciones que se haran conforme a su operador simbolico");

        for(String s : opciones) System.out.println(s);
    }

    static void operadores(Scanner teclado, Integer[] valores){
        try {
            if (valores[0] == null){
                System.out.println("Ingresa el valor de a");
                valores[0] = teclado.nextInt();
            }
            if (valores[1] == null){
                System.out.println("Ingresa el valor de b");
                valores[1] = teclado.nextInt();
            }
        }catch (IllegalFormatConversionException e){
            System.out.println("Ingresa solo numeros ");
            operadores(teclado, valores);
        }
    }


    static void procesos(Scanner teclado,int n){
        print_operaciones();

        String str_op = null;
        int num_operacion = 0;
        // setear todas las operaciones

        int contador = 1;
        Lotes lote = new Lotes();

        for(int i = 0; i < n; i++){
            //HashMap<String, Integer[]> operaciones = new HashMap<>();
            System.out.println("Ingrese Nombre programador: ");
            String nombre_programador = null;
            nombre_programador = teclado.next();

            System.out.println("Ingrese Num proceso: ");
            String num_proceso = teclado.next();
            while (!num_proceso.matches("^[+]?\\d+$")){
                System.out.println("Ingrese un numero valido");
                num_proceso = teclado.next();
            }
            id_procesos.add(num_proceso);

            for(Proceso proceso : lote.getProcesosList()){
                while (proceso.getNum_proceso().equals(num_proceso) || !num_proceso.matches("^[+]?\\d+$")) {
                    System.out.println("El numero que ingresaste ya existe; Ingresa otro");
                    num_proceso = teclado.next();
                }
            }

            System.out.printf("\nNumero de Operacion: %d \nIngresa una operacion despues presiona enter \n", num_operacion);
            str_op = teclado.next();

            // validacion para que sea una operacion valida
            while (!str_op.contains("+") && !str_op.contains("-") && !str_op.contains("*") && !str_op.contains("/") && !str_op.contains("%") && !str_op.contains("^")){
                System.out.println("Ingresa una operacion valida");
                str_op = teclado.next();
            }

            // se puede cambiar a double
            //Integer a = null, b = null;
            Integer[] valores = new Integer[2];
            operadores(teclado, valores);

            System.out.printf("\n operadores = %d , %d  \n", valores[0] , valores[1]);
            Proceso proceso = new Proceso(str_op, valores, nombre_programador);
            proceso.setNum_proceso(num_proceso);

            if (str_op.equals("/") || str_op.equals("%")) {
                while(valores[1] == 0){
                    valores[1] = null;
                    System.out.println("No se puede dividir entre 0");
                    // La opreacion nunca se estaba realizando porque en los condicionales esra que si valore[n] == null;
                    // entonces NO era null y nunca pedia repetir el numero
                    operadores(teclado,valores);
                }
            }


            //procesos.putProceso(str_op, valores);
            //operaciones.put(str_op, valores);
            lote.setProcesos(proceso);

            // por cuantos procesos contendra un lote
            if (contador % 5 == 0){
                pila_ejecucion.add(lote);
                lote = new Lotes();
            }

            //opreaciones.add(tmp);
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
        //int contador = 0;
        int contador_lotes = 1;
        for (Lotes l : pila_ejecucion){
            System.out.printf("\nLOTE N: %d \n", contador_lotes);
            System.out.println("----------------------------------------------------------------");
            contador_lotes++;

            //if (contador > 2){contador = 0;}
            List<Proceso> operaciones = l.getProcesosList();

            int contador_procesos = 1;
            for (Proceso proceso : operaciones){
                Tiempo tiempo = new Tiempo();
                tiempo.init();

                System.out.printf("En Ejecucion PID: %s \n", proceso.getNum_proceso());
                proceso.procesar();
                //proceso.get .entrySet().iterator().next();

                //System.out.println(operacion + ": " + valores[0] + ", " + valores[1]);

                //String operacion = l.getProcesosList().;
                //List<String> claves = new ArrayList<>(l.getProcesosList().keySet());
                //String string_unico_claves = map.entrySet(); // indice

                tiempo.end();

                System.out.printf("\nTiempo del proceso en nanoseg: %d" +
                                "\nTiempo del proceso en miliseg: %d" +
                                "\nProcesos en el lote Restantes: %d " +
                                "\n Tiempo estimado del proceso: %f \n",
                        tiempo.calculateTime_nano(),
                        tiempo.calculateTime_milis(),
                        (operaciones.size()-contador_procesos),
                        Math.random()*10
                );
                System.out.println("----------------------------------------------------------------");
                contador_procesos++;
            }
            pila_ejecucion.pop();
            System.out.printf("\nLotes pendientes: %d \n", pila_ejecucion.size());
            //contador++;
        }

    }


    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
        int procesos = 0;

        Tiempo tiempo = new Tiempo();
        tiempo.init();
        while (true){
            System.out.println("Introduce numero de procesos");
            try{
                procesos = teclado.nextInt();
                if (procesos > 0){
                    procesos(teclado, procesos);
                    ejecucion();
                    break;
                }else{
                    System.out.println("Ingresa un numero mayor a 0");
                }
            }catch (InputMismatchException e){
                System.out.println("Ingresa un numero entero positivo");
                teclado.nextLine();
            }
        }
        teclado.close();
        tiempo.end();
        System.out.printf("Tiempo del programa en nanoseg: %d" +
                        "\nTiempo del programa en miliseg: %d",
                tiempo.calculateTime_nano(),
                tiempo.calculateTime_milis());

        // funcion para imprimir numeros random que simulara el PID del proceso
        //System.out.println(Math.round(Math.random()*10000));

    }
}
