package org.Alpha.Algoritmos;

import java.util.*;
import java.util.stream.Stream;

/**
 *
 * Given an array nums of size n, return the majority element.
 * The majority element is the element that appears more than ⌊n / 2⌋ times.
 * You may assume that the majority element always exists in the array.
 * */
public class _17_Majority_Element {

    public static int majorityElement(int[] nums) {
        HashMap<Integer, Integer> set = new HashMap<>();

        ArrayList<Integer> resultado = new ArrayList<>();

        int i = 0;
        int indice = 0;

        int rel = 0;

        for (Integer a : nums){
            if (!set.containsKey(a)) {
                set.put(a, 1);
            }else {
                set.put(a, set.getOrDefault(a, 0) + 1);
            }
            if (set.get(a) > nums.length / 2)return a;
        }


        /*for (Integer b : resultado){
            System.out.println(b);
        }
        int resul = 0;


        int res = 0;
        for (Map.Entry<Integer, Integer> entero : set.entrySet()){

            System.out.printf("Valores: %d , %d \n", entero.getKey(), entero.getValue());
        }*/




        return 0;
    }

    public static void main(String[] args) {

        System.out.println(majorityElement(new int[]{3,2,3}));
        System.out.println(majorityElement(new int[]{2,2,1,1,1,2,2}));
        System.out.println(majorityElement(new int[]{1}));
    }
}
