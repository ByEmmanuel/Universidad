// Este documento tendra los tipos de datos en C++ y sus diferencias con C.
/*  
* Nombre: 2_TiposDeDatos.cpp
* Autor: ByEmmanuel
* Fecha: 03-09-2024
* Descripcion: Tipos de datos en C++ y sus diferencias con C
*/

// Tipos de datos en C++
// En C++ los tipos de datos son los mismos que en C, pero con algunas diferencias.
// Los tipos de datos en C++ son los siguientes:

// Tipos de datos primitivos


// char: Se utiliza para almacenar caracteres. Ocupa 1 byte de memoria.
char caracter[5] = {'a','b','c','d','\0'};  
// int: Se utiliza para almacenar números enteros. Ocupa 4 bytes de memoria.
int entero = 5;
// float: Se utiliza para almacenar números decimales de precisión simple. Ocupa 4 bytes de memoria.
float decimal = 3.14;
// double: Se utiliza para almacenar números decimales de precisión doble. Ocupa 8 bytes de memoria.
double doble = 3.14159265359;
// bool: Se utiliza para almacenar valores booleanos (true o false). Ocupa 1 byte de memoria.
bool booleano = true;
// void: Se utiliza para indicar que una función no devuelve ningún valor.
void funcion(){
    return;
}

// Tipos de datos compuestos


// string: Se utiliza para almacenar cadenas de caracteres.
#include <string>
std::string cadena = "Hola Mundo";
// array: Se utiliza para almacenar una colección de elementos del mismo tipo.
int array[] = {1, 2, 3, 4, 5};
// struct: Se utiliza para definir una estructura que puede contener varios tipos de datos.
struct Persona{
    std::string nombre;
    int edad;
};
// union: Se utiliza para definir una estructura que puede contener varios tipos de datos, pero solo uno a la vez.
union Datos{
    int entero;
    float decimal;
};
// enum: Se utiliza para definir un conjunto de constantes enteras.
enum Colores{
    Rojo,
    Verde,
    Azul
};

// Tipos de datos punteros
// int*: Puntero a un entero.
int* punteroUNo = &entero;
// float*: Puntero a un número decimal.
float* punteroDos = &decimal;
// char*: Puntero a un carácter.
char* punteroTres = caracter;
// void*: Puntero a cualquier tipo de dato.
void* punteroCuatro = &entero;

// Tipos de datos en C
// En C los tipos de datos son los mismos que en C++, pero con algunas diferencias.
// Los tipos de datos en C son los siguientes:

// Tipos de datos primitivos
// char: Se utiliza para almacenar caracteres. Ocupa 1 byte de memoria.
// int: Se utiliza para almacenar números enteros. Ocupa 4 bytes de memoria.
// float: Se utiliza para almacenar números decimales de precisión simple. Ocupa 4 bytes de memoria.
// double: Se utiliza para almacenar números decimales de precisión doble. Ocupa 8 bytes de memoria.
// bool: Se utiliza para almacenar valores booleanos (true o false). Ocupa 1 byte de memoria.
// void: Se utiliza para indicar que una función no devuelve ningún valor.


// Tipos de datos compuestos
// struct: Se utiliza para definir una estructura que puede contener varios tipos de datos.
// union: Se utiliza para definir una estructura que puede contener varios tipos de datos, pero solo uno a la vez.
// enum: Se utiliza para definir un conjunto de constantes enteras.

// Tipos de datos punteros
// int*: Puntero a un entero.
// float*: Puntero a un número decimal.
// char*: Puntero a un carácter.
// void*: Puntero a cualquier tipo de dato.

// Diferencias entre C y C++
// Las principales diferencias entre C y C++ en cuanto a tipos de datos son las siguientes:

// En C++ se pueden declarar variables en cualquier parte del código, mientras que en C solo se pueden declarar al principio de una función.
// En C++ se pueden declarar variables sin inicializarlas, mientras que en C todas las variables deben ser inicializadas.
// En C++ se pueden declarar variables con el tipo auto, que permite que el compilador infiera el tipo de la variable en función del valor asignado.
// En C++ se pueden declarar variables con el tipo decltype, que permite que el compilador infiera el tipo de la variable en función de otra variable.
// En C++ se pueden declarar variables con el tipo nullptr, que representa un puntero nulo.
// En C++ se pueden declarar variables con el tipo constexpr, que permite que una variable sea evaluada en tiempo de compilación.
// En C++ se pueden declarar variables con el tipo decltype(auto), que permite que el compilador infiera el tipo de la variable en función de otra variable.
// En C++ se pueden declarar variables con el tipo static_assert, que permite que una condición sea evaluada en tiempo de compilación.
// En C++ se pueden declarar variables con el tipo noexcept, que indica que una función no lanza excepciones.