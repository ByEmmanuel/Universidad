package org.Alpha.Algoritmos;


import java.util.ArrayList;
import java.util.Comparator;

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
class Solution {
    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {

    }
}
 */

public class _9_Merge_Two_Sorted_Lists {
    public static void main(String[] args) {
        ListNode n4 = new ListNode(7);
        ListNode n3 = new ListNode(5,n4);
        ListNode n2 = new ListNode(4,n3);
        ListNode n1 = new ListNode(3,n2);

        ListNode m4 = new ListNode(3);
        ListNode m3 = new ListNode(2,m4);
        ListNode m2 = new ListNode(2,m3);
        ListNode m1 = new ListNode(1,m2);
        //System.out.println(mergeTwoLists(n1, m1));
        //printList(n1);
        printList(mergeTwoLists(n1, m1));


        // Caso 1
        ListNode a3 = new ListNode(5);
        ListNode a2 = new ListNode(3, a3);
        ListNode a1 = new ListNode(1, a2);

        ListNode b2 = new ListNode(4);
        ListNode b1 = new ListNode(2, b2);
        //System.out.println(mergeTwoLists(a1, b1));
        printList(mergeTwoLists(a1, b1));

        // Caso 2
        ListNode c2 = new ListNode(6);
        ListNode c1 = new ListNode(2, c2);

        ListNode d3 = new ListNode(7);
        ListNode d2 = new ListNode(4, d3);
        ListNode d1 = new ListNode(1, d2);
        //System.out.println(mergeTwoLists(c1, d1));
        printList(mergeTwoLists(c1, d1));

        // Caso 3
        ListNode e1 = new ListNode(1);

        ListNode f1 = new ListNode(2);
        //System.out.println(mergeTwoLists(e1, f1));
        printList(mergeTwoLists(e1, f1));
        // Caso 4
        ListNode g3 = new ListNode(8);
        ListNode g2 = new ListNode(6, g3);
        ListNode g1 = new ListNode(4, g2);

        ListNode h2 = new ListNode(7);
        ListNode h1 = new ListNode(3, h2);
        //System.out.println(mergeTwoLists(g1, h1));
        printList(mergeTwoLists(g1, h1));

        // Caso 5
        ListNode i4 = new ListNode(10);
        ListNode i3 = new ListNode(7, i4);
        ListNode i2 = new ListNode(5, i3);
        ListNode i1 = new ListNode(1, i2);

        ListNode j2 = new ListNode(6);
        ListNode j1 = new ListNode(2, j2);
        //System.out.println(mergeTwoLists(i1, j1));
        printList(mergeTwoLists(i1, j1));

        // Caso 6
        ListNode k1 = null;
        ListNode l1 = new ListNode(1);
        //System.out.println(mergeTwoLists(k1, l1));
        //printList(mergeTwoLists(k1, l1));

        // Caso 7
        ListNode x3 = new ListNode(9);
        ListNode x2 = new ListNode(7, x3);
        ListNode x1 = new ListNode(5, x2);

        ListNode y3 = new ListNode(8);
        ListNode y2 = new ListNode(6, y3);
        ListNode y1 = new ListNode(4, y2);
        //System.out.println(mergeTwoLists(x1, y1));
        printList(mergeTwoLists(x1, y1));

        // Caso 8
        ListNode o1 = null;
        ListNode p1 = null;
        //System.out.println(mergeTwoLists(o1, p1));
        //printList(mergeTwoLists(o1, p1));
        // Caso 9
        ListNode q2 = new ListNode(20);
        ListNode q1 = new ListNode(10, q2);

        ListNode r3 = new ListNode(15);
        ListNode r2 = new ListNode(5, r3);
        ListNode r1 = new ListNode(1, r2);
        //System.out.println(mergeTwoLists(q1, r1));
        printList(mergeTwoLists(q1, r1));

        // Caso 10
        ListNode s5 = new ListNode(100);
        ListNode s4 = new ListNode(70, s5);
        ListNode s3 = new ListNode(50, s4);
        ListNode s2 = new ListNode(20, s3);
        ListNode s1 = new ListNode(10, s2);

        ListNode t1 = new ListNode(5);
        //System.out.println(mergeTwoLists(s1, t1));
        printList(mergeTwoLists(s1, t1));

        ListNode e = new ListNode();    //[]
        ListNode e2 = new ListNode();   //[]
        printList(mergeTwoLists(e, e2));

        //[1,1,2,3,4,4]

        ListNode aa1 = new ListNode(4);
        ListNode aa2 = new ListNode(3,aa1);
        ListNode aa3 = new ListNode(2,aa2);

        ListNode ab4 = new ListNode(4);
        ListNode ab5 = new ListNode(1,ab4);
        ListNode ab6 = new ListNode(1,ab5);

        printList(mergeTwoLists(aa3, ab6));

        //System.out.println(mergeTwoLists(list2));
        //System.out.println(mergeTwoLists(list3));
    }
    public static ListNode mergeTwoLists(ListNode list1, ListNode list2){
            int valorArbitrario1 = 1;
            int valorArbitrario2 = 1;
            ArrayList<Integer> valores = new ArrayList<>();

            if (list1 != null){
                for (int i = 0; i < valorArbitrario1 ; i++) {
                    valores.add(list1.val);
                    if (list1.next != null ){
                        list1 = list1.next;
                        valorArbitrario1++;
                    }
                }


            }
            if (list2 != null){
                for (int i = 0; i < valorArbitrario2 ; i++) {
                    valores.add(list2.val);
                    if (list2.next != null ){
                        list2 = list2.next;
                        valorArbitrario2++;
                    }
                }
            }
            valores.sort(Comparator.reverseOrder());
            ListNode node1 = null;
            // n
            for (int i = 0; i < valores.size(); i++) {

                ListNode node2 = new ListNode(valores.get(i));
                node2.next = node1;
                node1 = node2;
            }

            return node1;
    };
    public static void printList(ListNode node) {
        while (node != null) {
            System.out.print(node.val);
            if (node.next != null) System.out.print(" -> ");
            node = node.next;
        }
        System.out.println();
    }
}

class ListNode {
    int val;
    ListNode next;
    ListNode() {}
    ListNode(int val){
        this.val = val;
    }
    ListNode(int val, ListNode next){
        this.val = val;
        this.next = next; }
}
