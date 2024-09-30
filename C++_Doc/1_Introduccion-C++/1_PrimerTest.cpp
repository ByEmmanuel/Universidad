
/* Description: Primer programa en C++
 * Fecha: 02-09-2024
 *
 * Breve explicacion de la estructura de un programa en C++:
 */

/* Incluye la libreria stdio.h que contiene las funciones basicas de entrada y salida
 * Debemos Importar Las Librerias Necesarias Para Nuestro Programa con la palabra reservada #include
 * En Este Caso Esta Libreria Es de C, Pero En C++ Se Utiliza iostream
 */
#include <iostream>
#include <string>

// Con esto puedo incluir el archivo necesario
// #include <C++_Doc/1_Introduccion-C++/5_Operadores.cpp>

/* Primero Se DECLARAN Las Funciones De Nuestro Programa ._.
 * La Declaracion De Una Funcion Se Hace De La Siguiente Manera:
 */
int suma(int a, int b);
int resta(int a, int b);
int multiplicacion(int a, int b);
int division(int a, int b);

void estructurasDeControl();
void mainOperadores();
void mainPalabrasReservadas();



int main(){
    printf("Hello World\n");
    int resultado = suma(2, 3); // 5

    //Se Usa std::cout Para Imprimir En Pantalla
    /* std          Es Un Espacio De Nombres Que Contiene Las Funciones De Entrada Y Salida (namespace)
     * cout         Es La Funcion Que Imprime En Pantalla (output)
     * cin          Es La Funcion Que Lee De La Entrada Estandar (input)
     * <<           Es El Operador De Insercion Que Inserta El Valor De La Variable En El Stream De Salida
     * endl         Es Un Caracter De Escape Que Indica El Fin De Linea
     */
    std::cout << "El resultado de la suma es: " << resultado << std::endl;
    std::string cadena;
    std::getline(std::cin, cadena);
    
    std::cout << "La cadena es: " << cadena << std::endl;
    // return 0; Indica Que El Programa Finalizo Correctamente

    //Llamada a la funcion de Estructuras de control (POO)
    estructurasDeControl();
    //Llamada a la funcion de Operadores (POO)
    mainOperadores();
    //Llamada a la funcion de Palabras Reservadas (POO)
    mainPalabrasReservadas();
    return 0;
}

/* Luego Se DEFINEN Las Funciones ._. */
int suma(int a, int b){
    return a + b;
}

int resta(int a, int b){
    return a - b;
}

int multiplicacion(int a, int b){
    return a * b;
}

int division(int a, int b){
    return a / b;
}
