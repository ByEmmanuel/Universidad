package org.Algoritmos;

import java.util.Random;

public class EstocasticaOrnsteinUhlenbeck {

    public static double[] simular(double A, double B, double s, double S, double theta0, double dt, int pasos) {
        double[] theta = new double[pasos];
        Random random = new Random();
        theta[0] = theta0;

        for (int i = 1; i < pasos; i++) {
            double t = i * dt;
            double expFactor = Math.exp(-A * t);
            double ruido = Math.sqrt(s / S) * B * Math.sqrt(dt) * random.nextGaussian();
            double integralAprox = Math.exp(-A * (t - (t - dt))) * ruido;

            theta[i] = expFactor * theta0 + integralAprox;
        }

        return theta;
    }

    public static void main(String[] args) {
        double A = 0.5;
        double B = 1.0;
        double s = 1.0;
        double S = 10.0;
        double theta0 = 40.0;
        double dt = 0.01;
        int pasos = 1000;

        double[] resultado = simular(A, B, s, S, theta0, dt, pasos);

        for (int i = 0; i < resultado.length; i++) {
            System.out.printf("t = %.2f, theta = %.5f%n", i * dt, resultado[i]);
        }
    }
}
