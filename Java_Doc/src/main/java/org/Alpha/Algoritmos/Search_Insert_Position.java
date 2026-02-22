package org.Alpha.Algoritmos;

public class Search_Insert_Position {

    static int searchInsert(int[] nums, int target) {
        int tam = nums.length/2;
        int k = 0;
        for (int i = 0; i < nums.length-1; i++){
            if(target == nums[i]){
                return i;
            }else if(target < nums[nums.length-1]){
                for (int j = 1; j < nums.length-1; j++) {
                    if (nums[j-1] < target){

                    }
                }
            }
        }
        return k;
    }


    public static void main(String[] args) {
        System.out.println(searchInsert(new int[]{2,3,6},3));
        System.out.println(searchInsert(new int[]{2,3,6},7));
        System.out.println(searchInsert(new int[]{2,5,6},4));

    }

}
