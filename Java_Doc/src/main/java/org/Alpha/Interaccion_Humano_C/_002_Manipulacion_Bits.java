package org.Alpha.Interaccion_Humano_C;

public class _002_Manipulacion_Bits {

    static void bit_01_(){
     int uno = 0b11111111;
        System.out.printf("Valor original : %d\n", uno);
        System.out.printf("Conteo de bits : %d \n", Integer.bitCount(uno));
        System.out.printf("Valor del bit mas significativo %d \n", Integer.highestOneBit(uno));
        System.out.printf("String de los bits en formato char %s \n", Integer.toBinaryString(uno));
        System.out.printf("Valor del bit menos significativo %d \n", Integer.lowestOneBit(uno));
        System.out.printf("Valor en decimal de los bits %d \n", Integer.valueOf(uno));
    }

    public static void main(String[] args) {
        bit_01_();
    }
}
