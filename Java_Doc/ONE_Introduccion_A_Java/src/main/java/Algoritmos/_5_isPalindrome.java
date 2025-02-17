package Algoritmos;

public class _5_isPalindrome {
    public static void main(String[] args) {
        isPalindrome(10);
    }
    public static boolean isPalindrome(int x) {

        String y = String.valueOf(x);
        Integer izq = 0;
        Integer der = y.length() - 1 ;
        while(izq < der){
            int a = y.charAt(izq) - '0';
            int c = y.charAt(der) - '0';
            if(x < 0 || (x % 10 == 0 && x != 0)){
                System.out.println("Es falso");

                return false;
            } else if (a == c) {
                System.out.println("Es palindromo: ");
                return true;
            }



            /*if(y.charAt(izq) - '0' == c){
                return true;
            }*/

            /*for (Integer i = 0; i< z ; i++){
                System.out.println("a: " + a);
               if (a == izq) {
                   System.out.println("i: " + i);
                   return true;
               }
            }*/

            y.replace(izq.toString(), der.toString());
            izq++;
            der--;

        }
        System.out.println(y.getClass());
        return false;
    }
}
