package org.Alpha.Algoritmos;

import java.util.Arrays;

public class _10_Remove_Duplicates_from_Sorted_Array {

    public static void main(String[] args) {
        int[] a = {2, 34, 5, 45, 45, 2};
        int[] b = {1, 1, 2};
        int[] c = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

        int[] d = {};
        int[] e = {1};
        int[] f = {1, 2, 3, 4, 5};
        int[] g = {5, 5, 5, 5, 5};
        int[] h = {-1, -1, -2, -3, -3, -2};
        int[] i = {1, 2, 2, 3, 4, 5, 5, 6};
        int[] j = {9, 8, 7, 7, 6, 6, 6, 5};
        int[] k = {100, 100, 99, 98, 98, 97};
        int[] l = {0, 0, 0, 0};
        int[] m = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int[] n = {-10, -10, 0, 10, 10, 20};
        int[] o = {1, 2, 3, 3, 2, 1};
        int[] p = {Integer.MAX_VALUE, Integer.MIN_VALUE, Integer.MAX_VALUE};
        int[] q = {42};
        int[] r = {1, 1, 1, 2, 2, 3, 3, 3, 4};
        int[] s = {1, 3, 3, 5, 5, 5, 7, 9};
        int[] t = {1, 2, 1, 2, 1, 2};
        int[] u = {10, 20, 30, 40, 50, 10, 20};

        System.out.println(Arrays.toString(removeDuplicates(a)));
        System.out.println(Arrays.toString(removeDuplicates(b)));
        System.out.println(Arrays.toString(removeDuplicates(c)));
        System.out.println(Arrays.toString(removeDuplicates(d)));
        System.out.println(Arrays.toString(removeDuplicates(e)));
        System.out.println(Arrays.toString(removeDuplicates(f)));
        System.out.println(Arrays.toString(removeDuplicates(g)));
        System.out.println(Arrays.toString(removeDuplicates(h)));
        System.out.println(Arrays.toString(removeDuplicates(i)));
        System.out.println(Arrays.toString(removeDuplicates(j)));
        System.out.println(Arrays.toString(removeDuplicates(k)));
        System.out.println(Arrays.toString(removeDuplicates(l)));
        System.out.println(Arrays.toString(removeDuplicates(m)));
        System.out.println(Arrays.toString(removeDuplicates(n)));
        System.out.println(Arrays.toString(removeDuplicates(o)));
        System.out.println(Arrays.toString(removeDuplicates(p)));
        System.out.println(Arrays.toString(removeDuplicates(q)));
        System.out.println(Arrays.toString(removeDuplicates(r)));
        System.out.println(Arrays.toString(removeDuplicates(s)));
        System.out.println(Arrays.toString(removeDuplicates(t)));
        System.out.println(Arrays.toString(removeDuplicates(u)));
    }

    public static int[] removeDuplicates(int[] nums) {
        int i = 0;
        int indice_actual = 0;
        int[] respuestas = new int[nums.length];
        //System.out.println(respuestas.length);


            //Si en la posicion actual de mi array en donde guardare los datos, ya esta colocado el dato en el que estoy actualmente, ignorara
            // En pocas palabras guardare el primer elemento que haya, despues verificare

            //Primero validador de que en la posicion anterior no este el elemento nuevo
            // if (respuestas[i-1]) no esta nums[i], agregar nums[i]

        int indice = 0;
        while(i < nums.length){

            if (i < nums.length - 1){
                //System.out.println(nums[i+1]);

                if (nums[i] == nums[i+1]){
                    //System.out.println("repetido " +  nums[i+1]);
                }else {
                    respuestas[indice_actual] = nums[i];
                    indice_actual++;
                }
            }
            else {
                respuestas[indice_actual] = nums[i];
            }

            i++;
        }


        return respuestas;
    }

    public static int removeDuplicatesReturnInt(int[] nums){
        int i = 0;
        int indice_actual = 0;
        int[] respuestas = new int[nums.length];

        int indice = 0;
        while(i < nums.length){

            if (i < nums.length - 1){
                System.out.println(nums[i+1]);

                if (nums[i] == nums[i+1]){
                    System.out.println("repetido " +  nums[i+1]);
                }else {
                    respuestas[indice_actual] = nums[i];
                    //return nums[indice_actual];
                    indice_actual++;
                }
            }
            else {
                respuestas[indice_actual] = nums[i];
            }

            i++;
        }


        return respuestas.length;
    }

}
