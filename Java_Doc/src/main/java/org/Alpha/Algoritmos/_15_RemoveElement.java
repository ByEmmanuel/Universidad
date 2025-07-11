package org.Alpha.Algoritmos;

/**
 * Given an integer array nums and an integer val, remove all occurrences of val in nums in-place.
 * The order of the elements may be changed. Then return the number of elements in nums which are not equal to val.
 * Consider the number of elements in nums which are not equal to val be k,
 * to get accepted, you need to do the following things:
 * Change the array nums such that the first k elements of nums contain the elements which are not equal to val.
 * The remaining elements of nums are not important as well as the size of nums.
 * Return k.
 */

public class _15_RemoveElement {

    public static int removeElement(int[] nums, int val) {
        int a = 1;

        int izq = 0, der = nums.length - 1;

        while(izq <= der){
            if (nums[izq] == val){
                nums[izq] = nums[der];
                der--;
            }else {
                izq++;
            }
        }


        for (int i = 0; i < izq ; i++) {
            System.out.println(nums[i]);
        }

        return izq;
    }

    public static void main(String[] args) {
        System.out.println("AAA " + removeElement(new int[]{3,2,2,3},3));
        System.out.println("AAA " + removeElement(new int[]{0,1,2,2,3,0,4,2},2));
    }
}
