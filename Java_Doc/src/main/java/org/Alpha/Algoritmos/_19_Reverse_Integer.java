package org.Alpha.Algoritmos;

import javax.swing.*;
import java.util.ArrayList;

public class _19_Reverse_Integer {

    // Versio mia, 2 ms RUNTIME (BEATS 10.92%) + 41 MB MEMORY (BEATS 44.26%)
    public static int reverse(int x){
        boolean es_negativo = false;
        if (x < 1) {
            x *= -1;
            es_negativo = true;
        };
        try{
            StringBuilder stringBuilder = new StringBuilder(Integer.toString(x));
            stringBuilder.reverse();
            if (es_negativo) {
                return Integer.valueOf(String.valueOf(stringBuilder)) *-1;
            }
            return Integer.valueOf(String.valueOf(stringBuilder));
        }catch (NumberFormatException e){
            System.out.println("Excepcion");
            return 0;
        }
    }

    public static int reverse_2(int x){
        int a = 0;

        boolean es_negativo = false;
        if (x < 0){
            x*=-1;
            es_negativo = true;
        }

        while(true){
            a *= 10;
            a += x % 10;
            x = x / 10;
            if (x <= 0){
                if (es_negativo){
                    return a*=-1;
                }
                return a;
            }
        }
    }

    public static void main(String[] args) {
        /*System.out.println(reverse(321));
        System.out.println(reverse(-123));
        System.out.println(reverse(120));
        System.out.println(reverse(1534236469));*/

        System.out.println(reverse_2(321));
        System.out.println(reverse_2(-123));
        System.out.println(reverse_2(120));
        System.out.println(reverse_2(1534236469));
    }
}
