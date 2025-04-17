package org.Alpha.Algoritmos;

import java.util.ArrayList;

public class _3_TwoSum {
    public static void main(String[] args) {
        int[] nums = new int[] { 2, 7, 11, 15 };
        int [] fun = funcion();
        //System.out.println(fun[0] + " "+ " " + fun[1]);
    }

    private static int[] funcion(){
        int[] nums = new int[] { 2, 7, 11, 15 };

        int target = 9;
        int i ;
        int j ;
        for (i = 0; i < nums.length; i ++) {
            for (j = i + 1; j < nums.length; j++) {
                if (nums[i] + nums[j] == target) {
                    return  new int [] {i,j};
                }

            }
        }

        return null;
    }
}
