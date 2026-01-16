package org.Alpha.Algoritmos;

import java.util.Arrays;

/**
 * Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if
 * needle is not part of haystack.
 *
 * Example 1:
 * Input: haystack = "sadbutsad", needle = "sad"
 * Output: 0
 * Explanation: "sad" occurs at index 0 and 6.
 * The first occurrence is at index 0, so we return 0.
 * Example 2:
 *
 * Input: haystack = "leetcode", needle = "leeto"
 * Output: -1
 * Explanation: "leeto" did not occur in "leetcode", so we return -1.
 *
 * */

public class _20_Find_the_Index_of_the_First_Occurrence {
    public static void main(String[] args) {
        System.out.println(strStr("sadbutsad", "sad"));
        System.out.println(strStr("leetcode","leeto"));
        System.out.println(strStr("abc","c"));
        System.out.println(strStr("aaa","a"));

        System.out.println(("leetcode".contains("leeto")));
    }

    public static int strStr(String haystack, String needle) {
        if(!haystack.contains(needle)){
            return -1;
        }

        // contemplar los 3 eventos
        // si esta al incio
        // en posicion
        // al final
        int ind = 0;


        return ind;
    }
}