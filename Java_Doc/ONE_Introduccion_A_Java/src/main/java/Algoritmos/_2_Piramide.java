package Algoritmos;

public class _2_Piramide {
    public static void main(String[] args) {
        int ancho = 20;
        int largo = 20;
        String[][] matriz = new String[ancho][largo];
        //String[][] matriz = new String[ancho][largo];
        String espacio = " ";
        /*for (int i = 0; i < ancho; i++) {
            for (int j = 0; j < largo ; j++) {
                //matriz[i][j] = "*";
                matriz[j] = "*";
                System.out.print(matriz[i] + " ");
                if ((j % 7) == 0){
                    System.out.println(" ");
                }
            }
        }*/
        int contador = 1;
        /*for (int i = 0; i < ancho; i++) {
            //System.out.println("Este imprime i" + i);
            for (int j = 1; j < largo; j++) {
                //System.out.print("a");
                matriz[i][j] = "* ";
                System.out.print(matriz[i][j]);
                if ((j  % 19) == 0){

                    System.out.println("a" + i);
                }
            }
        }*/
        int j = 1;
        for (int i = 0; i < ancho; i++) {
            System.out.print("* ");
            while ((j  % 19) != 0){
                System.out.print("* ");
                j++;
                if((i % 19) != 0){
                    j = 1;
                    System.out.println("\n");
                }
                if(i < ancho -1){
                    break;
                }
            }
        }
    }
}
//pos 2 1
// pos 3 2
//pos 4 3
// pos 5 4