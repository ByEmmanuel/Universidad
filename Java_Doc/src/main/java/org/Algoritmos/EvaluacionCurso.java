package org.Algoritmos;

import java.util.ArrayList;
import java.util.List;

public class EvaluacionCurso {
    // Clase para representar una forma de evaluación
    static class FormaEvaluacion {
        String nombre;
        int valorInicial;

        FormaEvaluacion(String nombre, int valorInicial) {
            this.nombre = nombre;
            this.valorInicial = valorInicial;
        }
    }

    // Genera un array decreciente de 5 en 5 desde un valor inicial hasta 0
    public static List<Integer> generarArray(int valorInicial) {
        List<Integer> arr = new ArrayList<>();
        for (int i = valorInicial; i > 0; i -= 5) {
            arr.add(i);
        }
        return arr;
    }

    // Función recursiva para encontrar combinaciones
    public static void encontrarCombinaciones(List<FormaEvaluacion> formas, List<List<Integer>> arrays,
                                              List<Integer> combinacionActual, int indice,
                                              int sumaActual, int valorMinimo, int valorMaximo,
                                              List<String> resultados) {
        // Si hemos usado un elemento de cada array
        if (indice == arrays.size()) {
            if (sumaActual >= valorMinimo && sumaActual <= valorMaximo) {
                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < combinacionActual.size(); i++) {
                    sb.append(formas.get(i).nombre).append(": ").append(combinacionActual.get(i));
                    if (i < combinacionActual.size() - 1) {
                        sb.append(", ");
                    }
                }
                sb.append(" -> Suma = ").append(sumaActual);
                resultados.add(sb.toString());
            }
            return;
        }

        // Para el array actual, prueba cada elemento
        for (int valor : arrays.get(indice)) {
            combinacionActual.add(valor);
            encontrarCombinaciones(formas, arrays, combinacionActual, indice + 1,
                    sumaActual + valor, valorMinimo, valorMaximo, resultados);
            combinacionActual.remove(combinacionActual.size() - 1); // Backtracking
        }
    }

    public static void main(String[] args) {
        // Definir las formas de evaluación
        List<FormaEvaluacion> formas = new ArrayList<>();
        formas.add(new FormaEvaluacion("Exámen 1", 25));
        formas.add(new FormaEvaluacion("Exámen 2", 25));
        formas.add(new FormaEvaluacion("Tareas", 50));
        //formas.add(new FormaEvaluacion("Proyecto", 20));

        int valorMinimo = 80; // Valor mínimo deseado
        int valorMaximo = 100; // Límite superior (nota máxima del curso)

        // Generar los arrays
        List<List<Integer>> arrays = new ArrayList<>();
        for (FormaEvaluacion forma : formas) {
            arrays.add(generarArray(forma.valorInicial));
        }

        // Mostrar los arrays generados
        for (int i = 0; i < arrays.size(); i++) {
            System.out.print(formas.get(i).nombre + ": ");
            for (int val : arrays.get(i)) {
                System.out.print(val + " ");
            }
            System.out.println();
        }

        // Encontrar combinaciones
        List<Integer> combinacionActual = new ArrayList<>();
        List<String> resultados = new ArrayList<>();
        encontrarCombinaciones(formas, arrays, combinacionActual, 0, 0, valorMinimo, valorMaximo, resultados);

        // Mostrar resultados
        System.out.println("\nCombinaciones que suman entre " + valorMinimo + " y " + valorMaximo + ":");
        for (String resultado : resultados) {
            System.out.println(resultado);
        }
    }
}