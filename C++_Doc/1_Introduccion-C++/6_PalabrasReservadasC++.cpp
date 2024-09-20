/*
 * Sexto programa de la serie de ejemplos de C++
 *  Nombre: Palabras Reservadas en C++
 *  Autor: ByEmmanuel
 *  Fecha: 08-09-2024
 *  Descripcion: Programa que muestra las palabras reservadas en C++ y sus usos
 *
 */

#include <iostream>



int mainPalabrasReservadas()
{
    // Palabras reservadas en C++
    // Las palabras reservadas son aquellas que tienen un significado especial en el lenguaje de programación y no pueden ser utilizadas como identificadores.
    // Las palabras reservadas en C++ son las siguientes:

    // Palabras reservadas de C++

    // asm: Se utiliza para insertar código ensamblador en un programa de C++.
    asm("nop");

    // auto: Se utiliza para declarar una variable con almacenamiento automático.
    auto variable = 5;

    // bool: Se utiliza para declarar una variable booleana.
    bool booleano = true;

    // break: Se utiliza para salir de un bucle o un switch.
    for (int i = 0; i < 5; i++){
        if (i == 3){
            break;
        }
    }

    // case: Se utiliza en un switch para comparar un valor con una etiqueta.
    int valor = 2;
    switch (valor){
    case 1:
        std::cout << "Caso 1" << std::endl;
        break;
    case 2:
        std::cout << "Caso 2" << std::endl;
        break;
    default:
        std::cout << "Caso por defecto" << std::endl;
        break;
    }

    // catch: Se utiliza en un bloque try-catch para capturar una excepción.
    try{
        throw 20;
    }
    catch (int e){
        std::cout << "Excepción capturada: " << e << std::endl;
    }

    // char: Se utiliza para declarar una variable de tipo carácter.
    char caracter = 'a';

    // class: Se utiliza para definir una clase en C++.
    class objeto {
    public:
        int x;
        int y;
    };

    // const: Se utiliza para declarar una variable constante.
    const int constante = 5;

    // continue: Se utiliza para saltar a la siguiente iteración de un bucle.
    for (int i = 0; i < 5; i++){
        if (i == 3){
            continue;
        }
        std::cout << i << std::endl;
    }

    // default: Se utiliza en un switch para definir un caso por defecto.
    int valor2 = 4;
    switch (valor2)
    {
    case 1:
        std::cout << "Caso 1" << std::endl;
        break;
    case 2 :
        std::cout << "Caso 2" << std::endl;
        break;
    default:
        std::cout << "Caso por defecto" << std::endl;
        break;
    }

    // delete: Se utiliza para liberar la memoria de un objeto creado con new.
    int* puntero = new int;
    delete puntero;

    // do: Se utiliza para iniciar un bucle do-while.
    int i = 0;
    do{
        std::cout << i << std::endl;
        i++;
    } while (i < 5);

    // double: Se utiliza para declarar una variable de tipo decimal de doble precisión.
    double decimal = 5.5;

    // dynamic_cast: Se utiliza para realizar conversiones de tipos dinámicas.
    class Base {
    public:
        virtual void metodo() {}
    };

    class Derivada : public Base {};
    Base* base = new Derivada;
    Derivada* derivada = dynamic_cast<Derivada*>(base);


    // else: Se utiliza en una estructura if-else para definir el bloque de código que se ejecuta si la condición es falsa.
    // else if: Se utiliza en una estructura if-else para definir una condición adicional.
    int numero = 5;
    if (numero > 7){
        std::cout << "El número es positivo" << std::endl;
    } else if (numero < 9){
        std::cout << "El número es menor que 3" << std::endl;
    }
    else{
        std::cout << "El número es negativo" << std::endl;
    }

    // enum: Se utiliza para definir un conjunto de constantes enteras.
    enum Colores {
        Rojo,
        Verde,
        Azul
    };

    // explicit: Se utiliza para indicar que un constructor no debe ser utilizado para conversiones implícitas.
    class Clase {
    public:
        explicit Clase(int x) {}
    };

    // export: Se utiliza para exportar un módulo de un programa.

    // extern: Se utiliza para declarar una variable o función que se encuentra en otro archivo.
    extern int variableExterna;

    // false: Se utiliza para representar el valor falso en una variable booleana.
    bool falso = false;

    // float: Se utiliza para declarar una variable de tipo decimal de precisión simple.
    float flotante = 5.5;

    // for: Se utiliza para iniciar un bucle for.
    for (int i = 0; i < 5; i++){
        std::cout << i << std::endl;
    }

    // friend: Se utiliza para declarar una función o clase como amiga de otra clase.
    class ClaseAmiga {
    public:
        friend class OtraClase;
    };

    // goto: Se utiliza para saltar a una etiqueta en un programa.
    int j = 0;
    inicio:
    std::cout << "Inicio goto aqui " << j << std::endl;
    j++;
    if (j < 5){
        goto inicio;
    }

    // if: Se utiliza para iniciar una estructura if-else.
    int numero2 = 5;
    if (numero2 > 0){
        std::cout << "El número es positivo" << std::endl;
    }else{
        std::cout << "El número es negativo" << std::endl;
    }

}

// inline: Se utiliza para indicar al compilador que una función debe ser inlined.
inline int suma(int a, int b) {
    return a + b;
}