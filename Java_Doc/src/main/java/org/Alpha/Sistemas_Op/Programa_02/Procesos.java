//package org.Alpha.Sistemas_Op.Programa_02;

public class Procesos implements Runnable{

    // cada proceso esta conformado por una operacion y sus valores
    private String operacion = null;
    private Integer[] valores = valores = new Integer[2];
    private int PID = ((int) Math.round(Math.random() * 100));
    private String resultado_operacion = null;
    private int tiempoMax = (int) (Math.random() * (20 - 6 + 1)) + 6;;
    private int tiempoEjecutado = 0;


    Procesos(){
        calcularOperacion();
        calcularValores();
    }
    Procesos(String numProcesos){

    }

    Procesos(Integer[] valores){
        //this.operacion = op;
        this.valores = valores;
        //calcularTiempoMax();
    }

    private void calcularOperacion(){
        switch ((int) (Math.random() * 6 )) {
            case 1:
                this.operacion = "-";
                break;
            case 2:
                this.operacion = "^";
                break;
            case 3:
                this.operacion = "*";
                break;
            case 4:
                this.operacion = "/";
                break;
            case 5:
                this.operacion = "%";
                break;
            default:
                this.operacion = "+";
                break;
        }
    }

    private void calcularValores(){
        valores[0] = (int) ( Math.random()*100 );
        valores[1] = (int) ( Math.random()*100 );
    }

    private final int tiempoReal = 1400;
    private final int tiempoTest = 500;

    private void dormirProceso(){
        while (this.tiempoMax > 0) {
            try {
                Thread.sleep((int) ( 300 ));
            } catch (InterruptedException e){
                System.out.println("Ocurrio un problema con el delay del hilo actual ");
            }    
            this.tiempoMax--;
        }
    }


    @Override
    public void run() {
        try {
            switch (operacion) {
                case "+": resultado_operacion = String.format("%d + %d = %d", valores[0], valores[1], (valores[0] + valores[1])); break;
                case "-": resultado_operacion = String.format("%d - %d = %d", valores[0], valores[1], (valores[0] - valores[1])); break;
                case "*": resultado_operacion = String.format("%d * %d = %d", valores[0], valores[1], (valores[0] * valores[1])); break;
                case "/": resultado_operacion = String.format("%d / %d = %d", valores[0], valores[1], (valores[0] / valores[1])); break;
                case "%": resultado_operacion = String.format("%d %% %d = %d", valores[0], valores[1], (valores[0] % valores[1])); break;
                case "^":
                    valores[0] = (int) Math.round(Math.sqrt(valores[0]));
                    valores[1] = (int) Math.round(Math.sqrt(valores[1]));
                    resultado_operacion = String.format("%d ^ %d = %d", valores[0], valores[1], (int) Math.pow(valores[0], valores[1]));
                    break;
            }

        } catch (ArithmeticException ex) {
            resultado_operacion = "Error: División por 0";
        }
        // Impresión solicitada
        // esto no debe ir aqui 
        //System.out.printf("PID: %d | Operacion: %s\n", PID, resultado_operacion);
    }

    public void run(int opcionUsr) {
        if (opcionUsr == 0) {
            this.operacion = "Error";
            return;
        }
        try {
            switch (operacion) {
                case "+": resultado_operacion = String.format("%d + %d = %d", valores[0], valores[1], (valores[0] + valores[1])); break;
                case "-": resultado_operacion = String.format("%d - %d = %d", valores[0], valores[1], (valores[0] - valores[1])); break;
                case "*": resultado_operacion = String.format("%d * %d = %d", valores[0], valores[1], (valores[0] * valores[1])); break;
                case "/": resultado_operacion = String.format("%d / %d = %d", valores[0], valores[1], (valores[0] / valores[1])); break;
                case "%": resultado_operacion = String.format("%d %% %d = %d", valores[0], valores[1], (valores[0] % valores[1])); break;
                case "^":
                    valores[0] = (int) Math.round(Math.sqrt(valores[0]));
                    valores[1] = (int) Math.round(Math.sqrt(valores[1]));
                    resultado_operacion = String.format("%d ^ %d = %d", valores[0], valores[1], (int) Math.pow(valores[0], valores[1]));
                    break;
            }
            //dormirProceso();

        } catch (ArithmeticException ex) {
            resultado_operacion = "Error: División por 0";
        }
        // Impresión solicitada
        // esto no debe ir aqui 
        //System.out.printf("PID: %d | Operacion: %s\n", PID, resultado_operacion);
    }

    public String getOperacion() {
        return operacion;
    }

    public void setOperacion(String operacion) {
        this.operacion = operacion;
    }

    public Integer[] getValores() {
        return valores;
    }

    public void setValores(Integer[] valores) {
        this.valores = valores;
    }

    public int getPID() {
        return PID;
    }

    public void setResultado_operacion(String res){
        this.resultado_operacion = res;
    }

    public String getResultado_operacion() {
        return resultado_operacion;
    }

    public int getTiempoMax() {
        return tiempoMax;
    }

    public void setTiempoMax(int tiempoMax){
        this.tiempoMax = tiempoMax;
    }

    public int getTiemopEjecucion() {
        return tiempoEjecutado;
    }

    public void setTiemopEjecucion(int ticksEjecucion){
        this.tiempoEjecutado = ticksEjecucion;
    }
}