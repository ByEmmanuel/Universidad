/*
package org.Alpha.POO;

import java.util.Scanner;

public interface Inversion {
    int convertirPesoAdolar();
    int convertirDolarApeso();
}

public class Divisa {
    String tipoMoneda;
    int moneda;
}

public class Moneda extends Divisa implements Inversion {
    private int peso = 0;
    private int dolar = 0;

    public void pideDatos(Scanner scanner) {
        System.out.println("Ingrese moneda (1: Peso, 2: Dólar):");
        int opcUsr = scanner.nextInt();
        switch (opcUsr) {
            case 1:
                System.out.println("Ingrese cantidad en pesos:");
                this.peso = scanner.nextInt();
                this.tipoMoneda = "Peso";
                break;
            case 2:
                System.out.println("Ingrese cantidad en dólares:");
                this.dolar = scanner.nextInt();
                this.tipoMoneda = "Dólar";
                break;
            default:
                System.out.println("Opción no válida");
                break;
        }
    }

    @Override
    public int convertirPesoAdolar() {
        return (int) (this.peso / 20.3);
    }

    @Override
    public int convertirDolarApeso() {
        return (int) (this.dolar * 20.3);
    }
}

public class Temperatura {
    private double fahrenheit = 0;
    private double celsius = 0;

    public void pideDatos(Scanner scanner) {
        System.out.println("Ingrese grados Fahrenheit:");
        this.fahrenheit = scanner.nextDouble();
        System.out.println("Ingrese grados Celsius:");
        this.celsius = scanner.nextDouble();
    }

    public void muestraTemperatura() {
        System.out.println("Fahrenheit: " + this.fahrenheit);
        System.out.println("Celsius: " + this.celsius);
    }
}

public class Clima {
    private Temperatura grado = new Temperatura();

    public void pideDatos(Scanner scanner) {
        grado.pideDatos(scanner);
    }

    public void muestraTemperatura() {
        grado.muestraTemperatura();
    }
}

public class _4_Polimorfismo {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean bandera = true;

        while (bandera) {
            System.out.println("Ingrese opción usuario:");
            System.out.println("1: Divisas");
            System.out.println("2: Temperatura");
            System.out.println("3: Salir");
            int opcUsr = scanner.nextInt();

            switch (opcUsr) {
                case 1:
                    Moneda moneda = new Moneda();
                    moneda.pideDatos(scanner);
                    System.out.println("Peso a dólar: " + moneda.convertirPesoAdolar());
                    System.out.println("Dólar a peso: " + moneda.convertirDolarApeso());
                    break;
                case 2:
                    Clima clima = new Clima();
                    clima.pideDatos(scanner);
                    clima.muestraTemperatura();
                    break;
                case 3:
                    bandera = false;
                    break;
                default:
                    System.out.println("Opción no válida");
                    break;
            }
        }
        scanner.close();
    }
}
*/
