package org.Alpha.Algoritmos;

import java.util.ArrayList;
import java.util.Scanner;

public class Matriz {
    public static void main(String[] args) {
        int [][] array = new int[5][5];
        Scanner scanner = new Scanner(System.in);

        for (int i = 0; i < array.length; i++) {
            for (int j = 0; j < array.length; j++) {
                array[j][i] = scanner.nextInt();
            }
        }
        
        for (int i = 0; i < array.length; i++) {
            for (int j = 0; j < array.length; j++) {
                System.out.print(array[i][j] + " ");        
            }
            System.out.println(" ");
        }
    }
}
