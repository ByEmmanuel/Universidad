package org.Alpha.Algoritmos;

public class _14_Add_Two_Numbers {
    public static class ListNode {
          int val;
          ListNode next;
          ListNode(){}
          ListNode(int val){
              this.val = val;
          }
          ListNode(int val, ListNode next){
              this.val = val;
              this.next = next;
          }
    }

    // l1 = [2,4,3]
    // l2 = [5,6,4]
    public static ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode copia = l1;
        ListNode copia2 = l2;
        int longitudL1 = 1;
        int longitudL2 = 1;
        while(copia.next != null){
            copia = copia.next;
            longitudL1 ++;
        }
        while(copia2.next != null){
            copia2 = copia2.next;
            longitudL2 ++;
        }
        /*System.out.println("Longitud L1: " + longitudL1);
        System.out.println("Longitud L2: " + longitudL2);*/

        ListNode resultado = new ListNode();
        int indice = 0;

        int longitud2 = 0;
        for (int i = 0; i < longitudL1; i++) {
            int resul = 0;
            int auxiliar = 0;
            if (l2 != null){
                resul = l1.val + l2.val;
                l1 = l1.next;
                l2 = l2.next;
            }else {
                resul = l1.val;
                l1 = l1.next;
            }
            if (resul > 9){
                // Esto me devuelve el numero a la izquierda (decenas) pero sera sumadas como unidad al siguiente digito
                indice = resul / 10;
                // Esto me devuelve el numero a la derecha (el residuo) y sera agregado al nodo actual
                resul = resul % 10;
                System.out.println("result : " + resul);
                System.out.println("ind : " + indice);
                //resultado.next = new ListNode(resul);
            }

            resultado.next = new ListNode(resul);
            longitud2++;
        }
        if (indice > 0){
            resultado.val += indice;
            indice = 0;
        }
        imprimirLista(resultado);
        return resultado;
    }

    public static void imprimirLista(ListNode d){
       while (d.next != null){
            System.out.println(d.val);
            d = d.next;
        };
        System.out.println(d.val);

    }


    public static void main(String[] args) {
        ListNode x = new ListNode(9);
        ListNode a = new ListNode(1,x);
        ListNode b = new ListNode(2,a);
        ListNode c = new ListNode(3,b);
        ListNode d = new ListNode(4,c);

        ListNode aa = new ListNode(4);
        ListNode bb = new ListNode(5,aa);
        ListNode cc = new ListNode(6,bb);
        ListNode dd = new ListNode(8,cc);

        imprimirLista(addTwoNumbers(d,dd));


    }
}
