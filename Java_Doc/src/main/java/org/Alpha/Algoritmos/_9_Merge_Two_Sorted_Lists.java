package org.Alpha.Algoritmos;


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
        System.out.println(mergeTwoLists(n1, m1));
        printList(n1);
        //System.out.println(mergeTwoLists(list2));
        //System.out.println(mergeTwoLists(list3));
    }
    public static ListNode mergeTwoLists(ListNode list1, ListNode list2){
        while(list1 != null && list2 != null){
            (motor->culata != NULL) ? precioPruebaPresion : 0.0f
            System.out.println((list1.val < list2.val) ? 2 : 4);
        }

        return null;
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
