package org.Alpha.Algoritmos;

public class _23_AwayTooLong {
    public static void main(String[] args) {
        System.out.println(solution("word"));
        System.out.println(solution("localization"));
        System.out.println(solution("internationalization"));
        System.out.println(solution("pneumonoultramicroscopicsilicovolcanoconiosis"));
    }

    public static String solution(String s){
        if (s.length() < 10) return s;

        StringBuilder resultado = new StringBuilder();

        int r = s.length()-2;
        resultado.append(s.charAt(0));
        resultado.append(r);
        resultado.append(s.charAt(r+1));

        return resultado.toString();
    }
}

