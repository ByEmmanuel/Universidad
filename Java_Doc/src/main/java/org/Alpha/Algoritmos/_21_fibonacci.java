package org.Alpha.Algoritmos;

import java.math.BigInteger;

public class _21_fibonacci {

    private static BigInteger fibo(int actual, long n_esimo, BigInteger x_1, BigInteger x){
        if (actual == n_esimo) return x;
        actual++;
        return fibo(actual,n_esimo ,x, x_1.add(x));
        
    };

    private static BigInteger fiboIterativo(int n_esimo){
        int fibo = 0;
        BigInteger resul = BigInteger.ZERO;
        BigInteger x_1 = BigInteger.ZERO;
        BigInteger x = BigInteger.ONE;
        while (fibo < n_esimo) {
            resul = x_1.add(x);
            x_1 = x;
            x = resul;
            
            //System.out.println(resul);
            fibo++;
        }
        return resul;
    }

    public static void main(String[] args) {

        // imprimir el n-simo elemento de la serie de sucecion de fibonacci recursivamente
        int n = 100;

        BigInteger v_1 = fibo(0,n,BigInteger.ZERO,BigInteger.ONE);
        BigInteger v_2 = fiboIterativo(n);
        System.out.println("FIBO RECURSIVO: " + v_1 );
        System.out.println("fIBO aLTERNATIVO: " + v_2 );

        System.out.printf("Son iguales? : %b \n" , v_2.compareTo(v_1));
    }
}
