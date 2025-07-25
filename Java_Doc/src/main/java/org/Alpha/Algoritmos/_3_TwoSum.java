package org.Alpha.Algoritmos;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class _3_TwoSum {
    public static void main(String[] args) {
        int[] nums = new int[] { 2, 7, 11, 15 };
        int [] fun = funcion();
        //System.out.println(fun[0] + " "+ " " + fun[1]);

        System.out.println(Arrays.toString(two_sum(new int[]{2, 7, 11, 15}, 9)));
        //System.out.println(Arrays.toString(two_sum(new int[]{3,2,4}, 6)));
        System.out.println(Arrays.toString(two_sum(new int[]{3,2,4,8,10,3,9}, 19)));
        System.out.println(Arrays.toString(two_sum(new int[]{3,2,4,8,10,3,9}, 23)));
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

    public static int[] two_sum(int[] nums, int target){
        Map<Integer, Integer> mapa = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complemento =  target - nums[i] ;
            if (mapa.containsKey(complemento)){
                return new int[]{mapa.get(complemento),i};
            }
            mapa.put(nums[i],i);
        }
        return null;
    }
}
