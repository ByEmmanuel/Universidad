/*
    * Nombre: 3_Arrays.cpp
    * Autor: ByEmmanuel
    * Fecha: 03-09-2024
    * Descripcion: Programa que lee un array de 5 elementos y los imprime en pantalla
*/

/*
 * Las Bibliotecas que terminan en .h son de C, las que no terminan en .h son de C++
 * Los include con <> c++ los busca directamente en el directorio raiz del compilador
 * Los include con "" c++ los busca en el directorio actual (Del proyecto)
 */

#include <iostream>

/* Arrays En C++ */

// Declaracion de un array. El 5 es el tamaño del array (Es decir, cuantos elementos tiene) y epieza desdee el 0
const int tamanoDelArray = 5;
int arrayPrueba[tamanoDelArray];
int leerArray(int tamanoDelArray[]); // Declaracion de la funcion;

// Funcion principal del programa
int funcionPrincipal(int argc, char const *argv[]){
    leerArray(arrayPrueba);
    return 0;
}

// Definicion de la funcion
int leerArray(int array[]){

    /* Bucle for que empeieza por 0 y termina en el tamaño del array
     * std es un espacio de nombres que contiene las funciones de entrada y salida (namespace)
    * cout es la funcion que imprime en pantalla (output)
    * cin es la funcion que lee de la entrada estandar (input)
    * << es el operador de insercion que inserta el valor de la variable en el stream de salida
    * endl es un caracter de escape que indica el fin de linea
    * :: es el operador de resolucion de ambito
    
    */

    for (int i = 0; i < tamanoDelArray; i++){
        std::cout << "Ingrese el valor del elemento " << i << ": ";
        //std::cin >> array[i]; es la forma de leer un valor de la entrada estandar y guardarlo en la variable array[i]
        // es decir, cin (Ingresa un valor y lo asigno a la variable array[i]) con el operador de insercion <<  || cin >> array[i]
        std::cin >> array[i];
    }


    for (int i = 0; i < tamanoDelArray; i++){
        std::cout << "El valor del elemento " << i << " es: " << array[i] << std::endl;
    }
    

    return 0;
};
