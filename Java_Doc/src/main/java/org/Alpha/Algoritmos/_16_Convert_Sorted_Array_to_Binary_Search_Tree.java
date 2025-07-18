package org.Alpha.Algoritmos;


// NOTA, NO PUDE RESOLVER ESTE ALGORITMO POR MI PROPIA CUENTA ME AYUDO GPT CON CONCEPTOS DE RECURSIVIDAD
// ESTUDIAR RECURSIVIDAD
// NO SE IMPRIME CORRECTAMENTE EL ARBOL


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

        //indice del medio del arreglo
        int mitad = (nums.length-1) / 2;

        TreeNode root = new TreeNode(nums[mitad]);
        TreeNode dummy_left = root;
        TreeNode dummy_right = root;
        //System.out.println(mitad);


            //root.left = helper(nums, 0 , mitad - 1 );
            //root.right = helper(nums, mitad + 1  , nums.length - 1);
            return helper(nums, 0, nums.length-1);


        /*int i = 0;
        while(i < mitad ){
            root.left = helper(nums, i , mitad - 1 );

            System.out.println(nums[i]);
            i++;
        }
        i++;
        while (i < nums.length){
            root.right = helper(nums, mitad + 1  , nums.length );

            System.out.println(nums[i]);
            i++;
        }*/


        //return root;
    }
    static int a = 0;
    public static TreeNode helper(int[] nums, int inicio, int fin){

        if (inicio > fin)return null;
        int mid = (inicio + fin)/2;
        TreeNode root =  new TreeNode(nums[mid]);
        root.left = helper(nums, inicio, mid -1);
        root.right = helper(nums, mid + 1, fin);


        return root;
    }

    // esto imprimira cada rama de izquierda a derecha
    public static void imprimirArbol(TreeNode arbol){
        try{
            System.out.println("Valor: " + arbol.val);
            if (arbol.left != null){
            }
                imprimirArbol(arbol.left);
            if (arbol.right != null){
            }
                imprimirArbol(arbol.right);
        }catch (NullPointerException ex){
            System.out.println("null");
        }

    }



    public static void main(String[] args) {

        TreeNode root = new TreeNode(0, new TreeNode(-10), new TreeNode(5));

        //root.left.right.val = -3;

        root.left.left = new TreeNode(-13);
        root.left.right = new TreeNode(-3);
        root.left.left.left = new TreeNode(-11);

        root.right.left = new TreeNode();
        root.right.right = new TreeNode(9);



        imprimirArbol(sortedArrayToBST(new int[]{-10,-3,0,5,9}));
        //imprimirArbol(root);
    }

}
