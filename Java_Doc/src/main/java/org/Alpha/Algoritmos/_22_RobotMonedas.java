package org.Alpha.Algoritmos;

public class _22_RobotMonedas {
    public static void main(String[] args){
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

        int[][] mapa_2 = new int[12][13];

        mapa_2[0][1] = 1;mapa_2[0][5] = 1;
        mapa_2[0][11] = 1;mapa_2[1][8] = 1;
        mapa_2[1][6] = 1;mapa_2[2][1] = 1;
        mapa_2[2][4] = 1;mapa_2[3][3] = 1;
        mapa_2[3][8] = 1;mapa_2[3][10] = 1;
        mapa_2[3][12] = 1;mapa_2[5][1] = 1;
        mapa_2[4][6] = 1;mapa_2[5][8] = 1;
        mapa_2[5][11] = 1;mapa_2[6][4] = 1;
        mapa_2[6][6] = 1;mapa_2[7][8] = 1;
        mapa_2[7][10] = 1;mapa_2[8][2] = 1;
        mapa_2[9][0] = 1;mapa_2[9][5] = 1;
        mapa_2[10][5] = 1;mapa_2[9][11] = 1;
        mapa_2[10][8] = 1;mapa_2[10][10] = 1;

        mapa_2[0][7]  = -1;
        mapa_2[0][6]  = -1;
        mapa_2[0][8]  = -1;
        mapa_2[1][0]  = -1;
        mapa_2[2][5]  = -1;
        mapa_2[2][8]  = -1;
        mapa_2[2][11] = -1;
        mapa_2[4][1]  = -1;
        mapa_2[4][5]  = -1;
        mapa_2[5][9]  = -1;
        mapa_2[6][3]  = -1;
        mapa_2[6][7]  = -1;
        mapa_2[7][1]  = -1;
        mapa_2[8][5]  = -1;
        mapa_2[9][1]  = -1;
        mapa_2[10][0] = -1;
        mapa_2[11][0] = -1;
        mapa_2[11][2] = -1;
        mapa_2[11][4] = -1;

        imprimirMatriz(calcularRuta(mapa));
        imprimirMatriz(calcularRuta(mapa_2));


    }

    public static boolean movimientoValido(int[][] arr, int x, int y){

        return x >= 0 && y >= 0 &&
        x < arr.length && y < arr[0].length
        && arr[x][y] != -1; 
    } 
    public static int[][] calcularRuta(int [][] mapa){
        
        // mapear el mapa
        //int[][] resultado = new int[mapa.length][mapa[0].length];
        
        for(int filas = 0; filas < mapa.length; filas++){

            for (int columnas = 0; columnas < mapa[0].length; columnas++) {
                /**
                 * Ejemplo mapa[1][0] = 1
                 * Ejemplo mapa[1][1] = 1
                 * Ejemplo mapa[1][2] = 1
                 */
                // tanto si para la derecha como para abajo son movimientos validos
                System.out.print( " " + mapa[filas][columnas] + "\t");

                // caso base 1
                if (filas == 0 && columnas == 0){
                    continue;

                // caso base 2
                    // solo se puede mover a la derecha
                }else if(filas == 0) {
                    if (movimientoValido(mapa, filas, columnas)){
                        //mapa[0][columnas] += mapa[0][columnas-1];
                        mapa[0][columnas] = Math.max(mapa[0][columnas], mapa[0][columnas-1]);

                        //resultado[0][columnas] += mapa[0][columnas-1];
                    }
                    //caso base 3
                    // solo se puede mover hacia abajo
                }else if(columnas == 0){
                    if (movimientoValido(mapa, filas, columnas)){
                        // la posicion de abajo es igual a la suma de arriba
                        //mapa[filas][0] += mapa[filas-1][0];
                        mapa[filas][0] = Math.max(mapa[filas-1][0], mapa[filas][0]);

                        //resultado[filas][0] += mapa[filas-1][0];
                    }
                    //mapa[filas][0] = mapa[filas][0] + Math.max(mapa[filas-1][0], mapa[filas][0]);
                    // caso general
                }else{
                    if (movimientoValido(mapa,filas ,columnas )){
                        mapa[filas][columnas] = mapa[filas][columnas]
                                + Math.max(mapa[filas][columnas-1], mapa[filas-1][columnas]);

                        /*resultado[filas][columnas] = mapa[filas][columnas]
                                + Math.max(mapa[filas][columnas-1], mapa[filas-1][columnas]);*/
                    }
                }

                /*try {
                    Thread.sleep(10);
                } catch (Exception e) {
                    // TODO: handle exception
                }*/
                
            }
            
        
            System.out.println();
        }
        return mapa;
    }

    public static void imprimirMatriz(int [][] arr){
        System.out.println("\n\n");
        for(int[] fila : arr){
            for(int columna : fila){
                System.out.print(columna <= 0  ? " \t" : columna + "\t");
            }
            System.out.println();
        }
    }   
}