package org.Alpha.Sistemas_Op.Programa_01;

import java.util.*;

class Tiempo {
    private long inicio = 0;
    private long fin = 0;

    public void init() { inicio = System.nanoTime(); }
    public void end() { fin = System.nanoTime(); }
    public long calculateTime_milis() {
        return (long) ((fin - inicio) / 1_000_000.0);
    }
}

class Proceso {
    private Map<String, Integer[]> lista_procesos = new HashMap<>();
    private String nombre_programador;
    private String num_proceso;
    private String resultado_operacion = ""; // Para guardar el resultado y re-imprimirlo

    public Proceso(String operacion, Integer[] operadores, String nombre_programador) {
        this.lista_procesos.put(operacion, operadores);
        this.nombre_programador = nombre_programador;
    }

    public String getNum_proceso() { return num_proceso; }
    public void setNum_proceso(String n) { this.num_proceso = n; }
    public String getResultado() { return resultado_operacion; }

    public void procesar() {
        Map.Entry<String, Integer[]> entrada = lista_procesos.entrySet().iterator().next();
        String operacion = entrada.getKey();
        Integer[] valores = entrada.getValue();

        try {
            switch (operacion) {
                case "+": resultado_operacion = String.format("%d + %d = %d", valores[0], valores[1], (valores[0] + valores[1])); break;
                case "-": resultado_operacion = String.format("%d - %d = %d", valores[0], valores[1], (valores[0] - valores[1])); break;
                case "*": resultado_operacion = String.format("%d * %d = %d", valores[0], valores[1], (valores[0] * valores[1])); break;
                case "/": resultado_operacion = String.format("%d / %d = %d", valores[0], valores[1], (valores[0] / valores[1])); break;
                case "%": resultado_operacion = String.format("%d %% %d = %d", valores[0], valores[1], (valores[0] % valores[1])); break;
                case "^": resultado_operacion = String.format("%d ^ %d = %.2f", valores[0], valores[1], Math.pow(valores[0], valores[1])); break;
            }
        } catch (ArithmeticException e) {
            resultado_operacion = "Error: División por 0";
        }
        // Impresión solicitada
        System.out.printf("Nombre Usr: %s | PID: %s | Operacion: %s\n", nombre_programador, num_proceso, resultado_operacion);
    }
}

class Lotes {
    private List<Proceso> procesos = new ArrayList<>();
    public List<Proceso> getProcesosList() { return this.procesos; }
    public void setProcesos(Proceso proceso) { this.procesos.add(proceso); }
}

public class Programa_01 {
    static ArrayDeque<Lotes> pila_ejecucion = new ArrayDeque<>();
    static List<Lotes> lotes_concluidos = new ArrayList<>(); // Historial de lotes pasados
    static ArrayList<String> id_procesos = new ArrayList<>();

    // Limpia la terminal en Arch Linux / Bash
    static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    static void procesos(Scanner teclado, int n) {
        int contador = 1;
        Lotes lote = new Lotes();

        for (int i = 0; i < n; i++) {
            System.out.printf("\n Registro de Proceso N: %d ", i+1);
            System.out.print("Nombre Usuario: ");
            String nombre = teclado.next();

            System.out.print("Num proceso: ");
            String num_proceso = teclado.next();
            while (!num_proceso.matches("^[+]?\\d+$") || id_procesos.contains(num_proceso)) {
                System.out.println("ID inválido o ya existe. Intenta otro:");
                num_proceso = teclado.next();
            }
            id_procesos.add(num_proceso);

            System.out.print("Operacion (+,-,*,/,%,^): ");
            String str_op = teclado.next();
            while (!"+-*/%^".contains(str_op)) {
                System.out.print("Operación no válida: ");
                str_op = teclado.next();
            }

            Integer[] valores = new Integer[2];
            for (int j = 0; j < 2; j++) {
                while (true) {
                    try {
                        System.out.print("Valor " + (j == 0 ? "a: " : "b: ") + ": ");
                        valores[j] = teclado.nextInt();
                        if (j == 1 && (str_op.equals("/") || str_op.equals("%")) && valores[j] == 0) {
                            System.out.println("No se puede dividir por 0.");
                            continue;
                        }
                        break;
                    } catch (Exception e) {
                        System.out.println("Ingresa un número.");
                        teclado.next();
                    }
                }
            }

            Proceso proceso = new Proceso(str_op, valores, nombre);
            proceso.setNum_proceso(num_proceso);
            lote.setProcesos(proceso);

            if (contador % 5 == 0 || i == n - 1) {
                pila_ejecucion.add(lote);
                lote = new Lotes();
            }
            contador++;
        }
    }

    static void ejecucion() {
        int idLoteActual = 1;

        while (!pila_ejecucion.isEmpty()) {
            Lotes loteActual = pila_ejecucion.pop();
            List<Proceso> pendientes = new ArrayList<>(loteActual.getProcesosList());
            List<Proceso> terminadosEnEsteLote = new ArrayList<>();

            while (!pendientes.isEmpty()) {
                clearScreen();

                // 1. Mostrar LOTES ANTERIORES (completos)
                if (!lotes_concluidos.isEmpty()) {
                    System.out.println("---------- LOTES ANTERIORES CONCLUIDOS ----------");
                    for (int i = 0; i < lotes_concluidos.size(); i++) {
                        System.out.println("Lote #" + (i + 1));
                        for (Proceso p : lotes_concluidos.get(i).getProcesosList()) {
                            System.out.println("  [ID: " + p.getNum_proceso() + " | Res: " + p.getResultado() + "]");
                        }
                    }
                    System.out.println("-----------------------------------");
                }

                // 2. Información del Lote Actual
                System.out.println("\n>>> TRABAJANDO EN LOTE #" + idLoteActual + " <<<");

                // Sub-sección: Terminados del lote actual
                System.out.println("\n[ PROCESOS CONCLUIDOS DE ESTE LOTE ]");
                if (terminadosEnEsteLote.isEmpty()) System.out.println("  (Ninguno)");
                for (Proceso p : terminadosEnEsteLote) {
                    System.out.println("  ✔ ID: " + p.getNum_proceso() + " -> " + p.getResultado());
                }

                // Sub-sección: Ejecución
                Proceso actual = pendientes.remove(0);
                System.out.println("\n[ EN EJECUCIÓN ]");
                actual.procesar();

                // Sub-sección: Pendientes del lote actual
                System.out.println("\n[ POR CONCLUIR (PENDIENTES DEL LOTE) ]");
                if (pendientes.isEmpty()) System.out.println("  (Es el último del lote)");
                for (Proceso p : pendientes) {
                    System.out.println("  ⌛ PID: " + p.getNum_proceso());
                }

                // Simular tiempo de procesamiento
                try { Thread.sleep(2000); } catch (InterruptedException e) { }

                terminadosEnEsteLote.add(actual);
            }

            // Guardar el lote que acaba de terminar en el historial
            Lotes loteParaHistorial = new Lotes();
            for(Proceso p : terminadosEnEsteLote) loteParaHistorial.setProcesos(p);
            lotes_concluidos.add(loteParaHistorial);

            idLoteActual++;
        }
    }

    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
        int nProcesos = 0;

        while (true) {
            System.out.print("Introduce numero de procesos: ");
            try {
                nProcesos = teclado.nextInt();
                if (nProcesos > 0) break;
            } catch (Exception e) {
                System.out.println("Error");
                teclado.next();
            }
        }

        procesos(teclado, nProcesos);
        ejecucion();

        System.out.println("\nSimulación finalizada.");
        teclado.close();
    }
}