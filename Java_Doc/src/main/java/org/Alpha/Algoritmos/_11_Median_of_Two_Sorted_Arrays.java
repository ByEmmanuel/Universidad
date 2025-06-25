package org.Alpha.Algoritmos;

public class _11_Median_of_Two_Sorted_Arrays {

    public static void main(String[] args) {

        int[] a = {2, 5, 34, 45};                  // original: {2, 34, 5, 45, 45, 2}
        int[] aa = {1,2};
        int[] bb = {3,4};

        int[] cc = {1,3};
        int[] dd = {2};

        int[] ee = {0,0};
        int[] ff = {0,0};

        int[] gg = {};
        int[] hh = {2,3};

        int[] b = {1, 2};                          // original: {1, 1, 2}
        int[] c = {0, 1, 2, 3, 4};                 // original: {0, 0, 1, 1, 1, 2, 2, 3, 3, 4}
        int[] d = {};                              // vacío
        int[] e = {1};                             // un solo número
        int[] f = {1, 2, 3, 4, 5};                 // ya estaba bien
        int[] g = {5};                             // original: {5, 5, 5, 5, 5}
        int[] h = {-3, -2, -1};                    // original: {-1, -1, -2, -3, -3, -2}
        int[] i = {1, 2, 3, 4, 5, 6};              // original: {1, 2, 2, 3, 4, 5, 5, 6}
        int[] j = {5, 6, 7, 8, 9};                 // original: {9, 8, 7, 7, 6, 6, 6, 5}
        int[] k = {97, 98, 99, 100};               // original: {100, 100, 99, 98, 98, 97}
        int[] l = {0};                             // original: {0, 0, 0, 0}
        int[] m = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // ya estaba bien
        int[] n = {-10, 0, 10, 20};                // original: {-10, -10, 0, 10, 10, 20}
        int[] o = {1, 2, 3};                       // original: {1, 2, 3, 3, 2, 1}

        System.out.println(findMedianSortedArrays(aa,bb));
        System.out.println(findMedianSortedArrays(b, a));   // pares con distintos tamaños
        System.out.println(findMedianSortedArrays(cc,dd));
        System.out.println(findMedianSortedArrays(ee,ff));
        System.out.println(findMedianSortedArrays(gg,hh));

        /*System.out.println(findMedianSortedArrays(c, d));   // uno vacío*/

        /*System.out.println(findMedianSortedArrays(e, f));   // tamaño 1 + impar*/

        /*System.out.println(findMedianSortedArrays(g, h));   // positivos y negativos*/

        /*System.out.println(findMedianSortedArrays(i, m));   // dos ordenados grandes*/

        /*System.out.println(findMedianSortedArrays(m, l));   // array grande + 0*/

        //System.out.println(findMedianSortedArrays(m, n));   // extremos negativos y positivos

        //System.out.println(findMedianSortedArrays(o, a));   // pequeño + mediano
    }

    public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
        double resultado = 0;
        int array_size = nums1.length + nums2.length;
        int[] nuevoArray = new int[array_size];
        int indice = 0;
        int izquierda = 0;
        int derecha = 0;
        //System.out.printf("Array Size = %d  \n", array_size/2);
        while (indice < nuevoArray.length){
            if (nums1.length > izquierda && nums2.length > derecha){
                if (nums1[izquierda] < nums2[derecha] ){
                    nuevoArray[indice] = nums1[izquierda];
                    izquierda++;
                }else {
                    nuevoArray[indice] = nums2[derecha];
                    derecha++;
                }
                //System.out.println(nuevoArray[indice]);
            }else if (nums1.length > izquierda){
                nuevoArray[indice] = nums1[izquierda];
                izquierda++;
            } else {
                nuevoArray[indice] = nums2[derecha];
                derecha++;
            }

            System.out.println(nuevoArray[indice]);



            //mediana} =
            //
            //nuevoArray}[n/2] si es impar} \\
            // nuevoArray}[n/2 - 1] + \text{nuevoArray}[n/2]}{2.0}, & \text{si } n \text{ es par}
            //\end{cases}

            indice++;
        }
        /*for (int i = 0; i <nuevoArray.length ; i++) {
            System.out.println("Valor del array ; " +  nuevoArray[i]);
        }*/


            if (array_size % 2 != 0 ){
                //resultado = ar == 0 ? 0 :  3;
                resultado = nuevoArray[array_size/2];
                //System.out.println("el array no tiene longitud par");
            }else {
                resultado = (nuevoArray[(array_size/2)-1] + nuevoArray[array_size/2]) / 2.0;
            }



        System.out.println("La mediana es : " + resultado);
        return resultado;
    }
}
