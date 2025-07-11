package org.Alpha.Algoritmos;

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode() {}
    TreeNode(int val) { this.val = val; }
    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

public class _16_Convert_Sorted_Array_to_Binary_Search_Tree {

    // len 5
    public static TreeNode sortedArrayToBST(int[] nums) {
        TreeNode root = new TreeNode(0);

        int i = 0;


        for (int j = 1; j <= nums.length; j++){
            TreeNode idk = new TreeNode();

            if (j < nums.length && nums[i] < nums[j]){
                if (idk.left == null){
                    idk.left = new TreeNode(nums[i]);
                }
            }else {
                idk.left = new TreeNode(nums[i]);
            }

            if (idk.left.val < idk.right.val){
                root.left = idk;
            }else {
                root.right = idk;
            }

            i++;
        }

        return root;
    }



    // esto imprimira cada rama de izquierda a derecha
    public static void imprimirArbol(TreeNode arbol){
        TreeNode dummyLeft = arbol;
        TreeNode dummyRight = arbol;

        TreeNode head = arbol;
        int pisos = 0;

        while(dummyLeft.left != null){
            System.out.println(dummyLeft.val);
            dummyLeft = dummyLeft.left;
            pisos++;
        }
        System.out.println(dummyLeft.val);

        System.out.println("otro nodo");

        while (dummyRight.right != null){
            System.out.println(dummyRight.val);
            dummyRight = dummyRight.right;
        }
        System.out.println(dummyRight.val);

        System.out.println("pisos " + pisos);


    }



    public static void main(String[] args) {

        TreeNode root = new TreeNode(0, new TreeNode(-10), new TreeNode(5));

        //root.left.right.val = -3;

        root.left.left = new TreeNode(-13);
        root.left.right = new TreeNode(-3);
        root.left.left.left = new TreeNode(-11);

        root.right.left = new TreeNode();
        root.right.right = new TreeNode(9);



        //imprimirArbol(sortedArrayToBST(new int[]{-10,-3,0,5,9}));
        imprimirArbol(root);
    }

}
