package org.Alpha.Algoritmos;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class _18_String_to_Integer_ {

    public static int myAtoi(String s){

        StringBuilder result = new StringBuilder();

        for (char a : s.toCharArray()){

            if(a == '-' && result.length() < 2 ){
                //System.out.println("tiene un menos");
                result.append(a);
            }
            if (a > 48 && a < 61){
                result.append(a);
                //System.out.println(a);
            }
            //System.out.println();

        }

        return Integer.decode(result.toString());
    }

    public static void main(String[] args) {
        System.out.println(myAtoi("42"));
        System.out.println(myAtoi("-42"));
        System.out.println(myAtoi("   -042"));
        System.out.println(myAtoi("1337c0d3"));


        int var_ceros = 0b1001001;
        System.out.println(var_ceros);
    }
}
