package org.Alpha.Algoritmos;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class _12_4Sum {
    public static void main(String[] args) {

        int[] a = {1,0,-1,0,-2,2};
        int[] b =  {2,2,2,2,2};
        System.out.println(fourSum(a,0));
        System.out.println();
        System.out.println(fourSum(b,8));
    }

    //Vas a retornar una lista con listas de enteros
    public static List<List<Integer>> fourSum(int[] nums, int target) {
        List<List<Integer>> resultado = new ArrayList<>();
        List<Integer> resultado_2_;
        int indice_1_ = 0;
        int indice_2_ = 0;
        /*while(indice_1_ < nums.length){
            while(indice_2_ < nums.length){
                if ((nums[indice_1_] + nums[indice_2_]) == target) {
                    resultado_2_.add(nums[indice_1_]);
                    resultado_2_.add(nums[indice_2_]);
                    indice_1_++;
                    System.out.printf("Target POS _1_: %d POS _2_: %d \n", nums[indice_1_], nums[indice_2_]);
                }
                indice_2_++;
            }
            //condicion de salida

            resultado.add(resultado_2_);

            indice_1_++;
        }*/

        int local = 0;
        while(indice_1_ < nums.length){
            resultado_2_ = new ArrayList<>();
            for (int i = 1; i < nums.length; i++) {
                local = nums[indice_1_] + nums[indice_2_] + nums[i] + nums[i-1];
                if (local == target){
                    System.out.println("local : " +  local);
                    resultado_2_.add(nums[indice_1_]);
                    resultado_2_.add(nums[indice_2_]);
                    resultado_2_.add(nums[i]);
                    resultado_2_.add(nums[i-1]);
                    indice_2_++;
                    //System.out.printf("Target POS _1_: %d POS _2_: %d \n", nums[indice_1_], nums[i]);
                    break;
                }
            }
            if (!resultado.contains(resultado_2_)){
                resultado.add(resultado_2_);
                indice_2_ = 0;
            }
            indice_1_++;
        }

    return resultado;
    }

}
