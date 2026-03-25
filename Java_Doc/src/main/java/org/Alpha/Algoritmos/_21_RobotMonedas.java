package org.Alpha.Algoritmos;

public class _21_RobotMonedas {
    public static void main(String[] args){
        System.out.println("Hola myundo");
        calcularRuta();
    }

    public static boolean movimientoValido(int[][] arr, int x, int y){

        return x > 0 && y > 0 && 
        x < arr.length && y < arr[0].length
        && arr[x][y] != -1; 
    } 
    public static void calcularRuta(){
        int[][] mapa = new int[5][6];

        //obstaulos
        mapa[0][1] = -1; 
        mapa[4][0] = -1 ;
        mapa[4][1] = -1 ;
        mapa[4][2] = -1 ;
        mapa[1][3] = -1 ;
        mapa[2][3] = -1 ;

        // monedas 
        mapa[1][0] = 1;
        mapa[2][1] = 1;    
        mapa[0][3] = 1;
        mapa[1][4] = 1;
        mapa[2][4] = 1;
        mapa[3][3] = 1;
        mapa[3][5] = 1;
        mapa[4][4] = 1;

        
        // mapear el mapa
        int ptr = 0;
        int inicio = 0;
        int[] final_r = {4,5};
        
        for(int filas = 0; filas < mapa.length; filas++){

            for (int columnas = 0; columnas < mapa[0].length; columnas++) {
                /**
                 * Ejemplo mapa[1][0] = 1
                 * Ejemplo mapa[1][1] = 1
                 * Ejemplo mapa[1][2] = 1
                 */
                System.out.print( " " + mapa[filas][columnas] + "\t");
                if (movimientoValido(mapa, filas+1, columnas+1)) {
                    if (mapa[filas][columnas] > 0) {
                        mapa[filas][columnas+1] += mapa[filas][columnas];
                    }else{
                        //mapa[filas][columnas] = mapa[filas][columnas];
                    }                    

                    
                }else{
                    continue;
                }

                
                try {
                    Thread.sleep(10);
                } catch (Exception e) {
                    // TODO: handle exception
                }
                
            }
            
        
            System.out.println();
        }
        imprimirMatriz(mapa);
    }

    public static void imprimirMatriz(int [][] arr){
        System.out.println("\n\n");
        for(int[] fila : arr){
            for(int columna : fila){
                System.out.print(columna+"\t");
            }
            System.out.println();
        }
    }   
}