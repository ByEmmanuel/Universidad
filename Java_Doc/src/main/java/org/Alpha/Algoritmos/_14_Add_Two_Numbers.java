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
        ListNode copia_l1 = l1;
        ListNode copia_l2 = l2;


        int l1_len = 1;
        int l2_len = 1;

        while (copia_l1.next != null){
            //System.out.println(l1.val);
            copia_l1 = copia_l1.next;
            l1_len++;
        }
        while (copia_l2.next != null){
            //System.out.println(l2.val);
            copia_l2 = copia_l2.next;
            l2_len++;
        }
        int i = 0;
        int variable_arbitraria = 0;
        ListNode result = null;
        // esto se va a ejecutar la longitud de las 2 listas
        int sobra = 0;
        while (i < (l1_len+l2_len)){
            //System.out.println(i);
            int res = 0;
            if (l1 != null){
                System.out.println(l1.val);
                res += l1.val;
                l1 = l1.next;
            }
            if (l2 != null){
                System.out.println(l2.val);
                res += l2.val;
                l2 = l2.next;
            }
            if (res % 10  != 0){
                res = (res / 10);
                sobra ++;
            }

            result = new ListNode(res);

            if (sobra > 0){
                result.next = new ListNode(res+sobra);
            }

            i++;
        }


        System.out.println("longitud l1 es " +  l1_len);
        System.out.println("longitud l2 es " +  l2_len);
        return result;
    }

    public static ListNode helper(ListNode listNode, int valor){


        return null;
    }

    public static void imprimirLista(ListNode d){
       if (d == null)return;
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

        ListNode ee = new ListNode(3);
        ListNode ff = new ListNode(4,ee);
        ListNode gg = new ListNode(2,ff);

        //ListNode aaa = new ListNode(5);
        ListNode hh = new ListNode(4);
        ListNode ii = new ListNode(6,hh);
        ListNode jj = new ListNode(5,ii);

        ListNode _1 = new ListNode(9);
        ListNode _2 = new ListNode(9,_1);
        ListNode _3 = new ListNode(9,_2);
        ListNode _4 = new ListNode(9,_3);
        ListNode _5 = new ListNode(9,_4);
        ListNode _6 = new ListNode(9,_5);
        ListNode _7 = new ListNode(9,_6);

        ListNode __1 = new ListNode(9);
        ListNode __2 = new ListNode(9,__1);
        ListNode __3 = new ListNode(9,__2);
        ListNode __4 = new ListNode(9,__3);




        //imprimirLista(addTwoNumbers(d,dd));
        //imprimirLista(addTwoNumbers(gg,jj));

        imprimirLista(addTwoNumbers(_7,__4));

        //imprimirLista(gg);
        System.out.println();
        //imprimirLista(jj);



    }
}
