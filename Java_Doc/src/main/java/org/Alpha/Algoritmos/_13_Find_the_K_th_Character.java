package org.Alpha.Algoritmos;

public class _13_Find_the_K_th_Character {

    public static char kthCharacter(int k) {
        StringBuilder resultado_2_ = new StringBuilder("a");
        int b = resultado_2_.length();
        // Valor ascii
        while(resultado_2_.length() <= k){
            StringBuilder toAdd = new StringBuilder();
            for (int j = 1; j <= resultado_2_.length(); j++){
                toAdd.append((char) ((int) resultado_2_.charAt(j-1) + 1));
            }
            resultado_2_.append(toAdd);
        }
        System.out.println(resultado_2_);
        return resultado_2_.charAt(k-1);
    }

    public static void main(String[] args) {
        System.out.println(kthCharacter(10));
    }

}
