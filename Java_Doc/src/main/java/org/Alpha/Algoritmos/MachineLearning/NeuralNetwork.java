package org.Alpha.Algoritmos.MachineLearning;

import org.Alpha.ONE_Introduccion_A_Java.CalcularTiempo;

import java.time.LocalTime;
import java.util.Date;
import java.util.Random;
import java.util.TimeZone;
import java.util.Timer;

public class NeuralNetwork {

    private double[][] weightsInputHidden;
    private double[][] weightsHiddenOutput;
    private double[] hiddenBias;
    private double[] outputBias;
    private int inputNodes;
    private int hiddenNodes;
    private int outputNodes;
    private double learningRate;

    // Constructor
    public NeuralNetwork(int input, int hidden, int output, double lr) {
        inputNodes = input;
        hiddenNodes = hidden;
        outputNodes = output;
        learningRate = lr;

        // Inicializar pesos y biases
        weightsInputHidden = new double[input][hidden];
        weightsHiddenOutput = new double[hidden][output];
        hiddenBias = new double[hidden];
        outputBias = new double[output];

        // Inicializar con valores aleatorios
        Random random = new Random();
        for (int i = 0; i < input; i++) {
            for (int j = 0; j < hidden; j++) {
                weightsInputHidden[i][j] = random.nextGaussian();
            }
        }
        for (int i = 0; i < hidden; i++) {
            for (int j = 0; j < output; j++) {
                weightsHiddenOutput[i][j] = random.nextGaussian();
            }
        }
        for (int i = 0; i < hidden; i++) {
            hiddenBias[i] = random.nextGaussian();
        }
        for (int i = 0; i < output; i++) {
            outputBias[i] = random.nextGaussian();
        }
    }

    // Función de activación sigmoide
    private double sigmoid(double x) {
        return 1.0 / (1.0 + Math.exp(-x));
    }

    // Derivada de la sigmoide
    private double sigmoidDerivative(double x) {
        double sig = sigmoid(x);
        return sig * (1 - sig);
    }

    // Propagación hacia adelante
    public double[] forward(double[] inputs) {
        // Calcular activaciones de la capa oculta
        double[] hidden = new double[hiddenNodes];
        for (int j = 0; j < hiddenNodes; j++) {
            double sum = hiddenBias[j];
            for (int i = 0; i < inputNodes; i++) {
                sum += inputs[i] * weightsInputHidden[i][j];
            }
            hidden[j] = sigmoid(sum);
        }

        // Calcular activaciones de la capa de salida
        double[] outputs = new double[outputNodes];
        for (int j = 0; j < outputNodes; j++) {
            double sum = outputBias[j];
            for (int i = 0; i < hiddenNodes; i++) {
                sum += hidden[i] * weightsHiddenOutput[i][j];
            }
            outputs[j] = sigmoid(sum);
        }
        return outputs;
    }

    // Entrenamiento con backpropagation
    public void train(double[] inputs, double[] targets) {
        // Propagación hacia adelante
        double[] hidden = new double[hiddenNodes];
        double[] hiddenInputs = new double[hiddenNodes];
        for (int j = 0; j < hiddenNodes; j++) {
            double sum = hiddenBias[j];
            for (int i = 0; i < inputNodes; i++) {
                sum += inputs[i] * weightsInputHidden[i][j];
            }
            hiddenInputs[j] = sum;
            hidden[j] = sigmoid(sum);
        }

        double[] outputs = new double[outputNodes];
        double[] outputInputs = new double[outputNodes];
        for (int j = 0; j < outputNodes; j++) {
            double sum = outputBias[j];
            for (int i = 0; i < hiddenNodes; i++) {
                sum += hidden[i] * weightsHiddenOutput[i][j];
            }
            outputInputs[j] = sum;
            outputs[j] = sigmoid(sum);
        }

        // Calcular errores de la capa de salida
        double[] outputErrors = new double[outputNodes];
        for (int j = 0; j < outputNodes; j++) {
            outputErrors[j] = targets[j] - outputs[j];
        }

        // Actualizar pesos y biases de la capa de salida
        for (int j = 0; j < outputNodes; j++) {
            double delta = outputErrors[j] * sigmoidDerivative(outputInputs[j]);
            outputBias[j] += learningRate * delta;
            for (int i = 0; i < hiddenNodes; i++) {
                weightsHiddenOutput[i][j] += learningRate * delta * hidden[i];
            }
        }

        // Calcular errores de la capa oculta
        double[] hiddenErrors = new double[hiddenNodes];
        for (int j = 0; j < hiddenNodes; j++) {
            double error = 0;
            for (int k = 0; k < outputNodes; k++) {
                error += outputErrors[k] * weightsHiddenOutput[j][k];
            }
            hiddenErrors[j] = error * sigmoidDerivative(hiddenInputs[j]);
        }

        // Actualizar pesos y biases de la capa oculta
        for (int j = 0; j < hiddenNodes; j++) {
            hiddenBias[j] += learningRate * hiddenErrors[j];
            for (int i = 0; i < inputNodes; i++) {
                weightsInputHidden[i][j] += learningRate * hiddenErrors[j] * inputs[i];
            }
        }
    }

    // Ejemplo de uso
    public static void main(String[] args) {
        CalcularTiempo calcularTiempo = new CalcularTiempo();
        calcularTiempo.init();

        // Crear red neuronal (2 entradas, 4 nodos ocultos, 1 salida)
        NeuralNetwork nn = new NeuralNetwork(2, 8, 1, 0.1);

        // Datos de entrenamiento para XOR
        double[][] inputs = {
                {0, 0},
                {0, 1},
                {1, 0},
                {1, 1}
        };
        double[][] targets = {
                {0},
                {1},
                {1},
                {0}
        };

        // Entrenar la red
        // Epocas -> Saltos que da la red neuronal en la derivada, para obtener el minimo error al obtener un valor concreto y mas especifico
        // Esto significa que, al calcular la pendiente de la recta tangente de la funcion de Error Cuadratico (x^2/2), nos dara que tan verdadero es el resultado
        // se pasan los pesos y los objetivos -> es decir, se entrena comforme mas se le pasan los parametros
        for (int i = 0; i < 1000_0; i++) {
            for (int j = 0; j < inputs.length; j++) {
                nn.train(inputs[j], targets[j]);
            }
        }

        // Probar la red
        for (double[] input : inputs) {
            double[] output = nn.forward(input);
            System.out.printf("Entrada: %.0f, %.0f -> Salida: %.3f%n",
                    input[0], input[1], output[0]);
        }

        calcularTiempo.end();
    }
}