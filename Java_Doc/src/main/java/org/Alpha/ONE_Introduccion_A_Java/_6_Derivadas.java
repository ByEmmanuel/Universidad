package org.Alpha.ONE_Introduccion_A_Java;

import java.util.function.Function;

public class _6_Derivadas {

    static class Trigonometria{

    }


    public static void main(String[] args) {
        double x = Math.PI;
        Function<Double, Double> f_x = Math::sin;
        Function<Double, Double> f_x1 = Math::cos;
        //System.out.println("La expresion f(" + x + ") = " + f_x.apply(x));
        System.out.printf("La expresion f(%f) = %f",x, f_x.apply(2.0 * x));
        System.out.println();
        System.out.printf("La expresion f(%f) = %f",x, f_x1.apply(0.0));

        int z = 0;
        while(true){
            System.out.println(++z);
        }
    }

}
