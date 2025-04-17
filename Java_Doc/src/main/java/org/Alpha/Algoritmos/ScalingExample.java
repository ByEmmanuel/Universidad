package org.Alpha.Algoritmos;

import java.util.Random;

public class ScalingExample {

    // Función de activación phi (ReLU)
    public static double phi(double x) {
        return Math.max(0, x); // ReLU
    }

    // Función y_n(theta) sin asumir escalamiento en la definición
    public static double y_n(double[] A, double[] B, double[] b, double x) {
        double sum = 0;
        int n = A.length;
        for (int i = 0; i < n; i++) {
            sum += A[i] * phi(B[i] * x + b[i]);
        }
        return sum;
    }

    // Función para escalar los parámetros theta por 1/alpha
    public static double y_n_scaled(double[] A, double[] B, double[] b, double x, double alpha) {
        int n = A.length;
        double[] A_scaled = new double[n];
        double[] B_scaled = new double[n];
        double[] b_scaled = new double[n];

        // Escalar los parámetros: theta / alpha
        for (int i = 0; i < n; i++) {
            A_scaled[i] = A[i] / alpha;
            B_scaled[i] = B[i] / alpha;
            b_scaled[i] = b[i] / alpha;
        }

        return alpha * alpha * y_n(A_scaled, B_scaled, b_scaled, x);
    }

    public static void main(String[] args) {
        int n = 5; // Número de neuronas
        double alpha = 2.0; // Factor de escalado
        double x = 1.0; // Entrada

        // Inicialización aleatoria de A, B, b (valores entre -1 y 1)
        Random rand = new Random();
        double[] A = new double[n];
        double[] B = new double[n];
        double[] b = new double[n];

        for (int i = 0; i < n; i++) {
            A[i] = 2 * rand.nextDouble() - 1; // [-1, 1]
            B[i] = 2 * rand.nextDouble() - 1; // [-1, 1]
            b[i] = 2 * rand.nextDouble() - 1; // [-1, 1]
        }

        // Calculando y_n(theta) original
        double y_original = y_n(A, B, b, x);
        // Calculando y_n(theta / alpha) con escalamiento
        double y_scaled = y_n_scaled(A, B, b, x, alpha);

        System.out.println("y_n(theta): " + y_original);
        System.out.println("y_n(theta / alpha) * alpha^2: " + y_scaled);
        System.out.println("Relación (y_scaled / y_original): " + (y_scaled / y_original));
        System.out.println("Esperado (alpha^2): " + (alpha * alpha));
    }
}