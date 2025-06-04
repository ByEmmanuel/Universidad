package org.Alpha.Algoritmos;

public class _8_Longest_common_prefix {
    public static void main(String[] args) {

        String[] array = {"flower","flow","flight"};
        String[] array2 = {"dog","racecar","car"};
        String[] array3 = {"a"};
        String[] array4 = {"interspecies", "interstellar", "interstate"};
        String[] array5 = {"throne", "throb"};
        String[] array6 = {"", ""};
        String[] array7 = {"abc", "abcd", "ab"};
        String[] array8 = {"xyz", "pqr", "lmn"};
        String[] array9 = {"single"};
        String[] array10 = {};
        String[] array11 = {"cir", "car"};

        System.out.println(fun(array));
        System.out.println(fun(array2));
        System.out.println(fun(array3));
        System.out.println(fun(array4)); // Debería devolver "inter" no
        System.out.println(fun(array5)); // Debería devolver "thro" no
        System.out.println(fun(array6)); // Debería devolver "" si
        System.out.println(fun(array7)); // Debería devolver "ab" si
        System.out.println(fun(array8)); // Debería devolver "" si
        System.out.println(fun(array9)); // Debería devolver "single" si
        System.out.println(fun(array10)); // Debería devolver "" si
        System.out.println(fun(array11)); // Debería devolver "" si

    }

    /*public static String fun(String[] strs){
        if(strs.length > 0){
            StringBuilder resul = new StringBuilder();
            int len = 0;
            // flower
            char[] primero = strs[0].toCharArray();
            len = primero.length;
            for (int i = 1; i < strs.length; i++) {
                for (char a : strs[i].toCharArray()){
                    if (a == primero[i-1]){
                        resul.append(a);
                    }
                }

            }
            return resul.toString();
        }
        return "";
        }*/

        /*public static String fun(String[] strs){
            if(strs.length < 1){
                return "";
            }
            if (strs.length < 2 && !strs[0].matches("")){
                return strs[0];
            }
            StringBuilder resul = new StringBuilder();
            StringBuilder ver = new StringBuilder();
            int len = 0;
            // flower
            char[] primero = strs[0].toCharArray();
            len = primero.length;
            //      throne
            for (int i = 1; i < strs.length ; i++) {
                for (int j = 0; j < strs[i].length(); j++) {
                    char a = strs[i].charAt(j);
                    if (a == primero[i-1]){
                        resul.append(a);
                    }
                }

            }
            return resul.toString();
        }*/

        public static String fun(String[] strs){
            if(strs.length < 1){
                return "";
            }
            if (strs.length < 2 && !strs[0].matches("")){
                return strs[0];
            }
            StringBuilder resul = new StringBuilder();

            // flower
            char[] primero = strs[0].toCharArray();
            //      throne
            // 2
            // Total de cadenas
            int e = strs.length;
            int x = 0;
            int y = 0;
            //"cir", "car"
            //Limitamos a la Longitud de la primera cadena
            while(x < strs[0].length()){
                int c = 0;
                for (int posAct = 0; posAct < e; posAct++) {
                    if (x < strs[posAct].length() && primero[x] == strs[posAct].charAt(x)){
                        c++;
                    }else {
                        x = 100;
                    }
                    if (c == e){
                        resul.append(primero[x]);
                        c = 0;
                    }
                }
                x++;
            }

            return resul.toString();
        }
}
