package org.Alpha.Algoritmos;

import java.math.BigInteger;
import java.util.ArrayList;

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
        return x;
    }

    private static BigInteger fiboDP(int n){
        switch (n){
            case 0: return BigInteger.ZERO;
            case 1: return BigInteger.ONE;
        }
        ArrayList<BigInteger> arr = new ArrayList<>(n);
        arr.add(0, BigInteger.ZERO);
        arr.add(1, BigInteger.ONE);
        int i = 2;
        while (i < n){
            BigInteger res = arr.get(i-1);
            BigInteger res_2 = arr.get(i-2);
            BigInteger suma = res;
            arr.add(i, suma.add(res_2));
            i++;
        }
        return arr.get(i-1);
    }

    private static int fiboDP_2(int n){
        switch (n){
            case 0: return 0;
            case 1: return 1;
        }
        int[] arr = new int[n];
        arr[0] = 0;
        arr[1] = 1;

        int i = 2;
        while (i < n){
            arr[i] = (arr[i-1] + arr[i-2]);
            i++;
        }
        return arr[i-1];
    }

    public static void main(String[] args) {

        // imprimir el n-simo elemento de la serie de sucecion de fibonacci recursivamente
        int n = 100;

        BigInteger v_1 = fibo(0,n,BigInteger.ZERO,BigInteger.ONE);
        BigInteger v_2 = fiboIterativo(n);
        System.out.println("FIBO RECURSIVO: " + v_1 );
        System.out.println("fIBO aLTERNATIVO: " + v_2 );

        System.out.printf("Son iguales? : %b \n" , v_2.compareTo(v_1));
        System.out.println("\nFibo DP :" + fiboDP(n));
        System.out.println("\nFibo DP_2 " + fiboDP_2(n));
    }
}
