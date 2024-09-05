/*
 *  Tercer Archivo
* Nombre: Tipos De Estructuras De Datos.cpp
* Autor: ByEmmanuel
* Fecha: 05-09-2024
* Descripcion: Tipos de Estructuras de control en C++
* Estas estructuras de controlo definen para donde debe ir el rumbo del programa
*/

#include <iostream>

int estructurasDeControl(){
    // Estructura de control if
    int numero = 5;
    if (numero > 0){
        std::cout << "El numero es positivo" << std::endl;
    }
    else if (numero < 0){
        std::cout << "El numero es negativo" << std::endl;
    }
    else{
        std::cout << "El numero es cero" << std::endl;
    }

    // Estructura de control switch
    int dia = 3;
    switch (dia){
        case 1:
            std::cout << "Lunes" << std::endl;
            break;
        case 2:
            std::cout << "Martes" << std::endl;
            break;
        case 3:
            std::cout << "Miercoles" << std::endl;
            break;
        case 4:
            std::cout << "Jueves" << std::endl;
            break;
        case 5:
            std::cout << "Viernes" << std::endl;
            break;
        case 6:
            std::cout << "Sabado" << std::endl;
            break;
        case 7:
            std::cout << "Domingo" << std::endl;
            break;
        default:
            std::cout << "Dia invalido" << std::endl;
            break;
    }

    // Estructura de control while
    int i = 0;
    while (i < 5){
        std::cout << i << std::endl;
        i++;
    }

    // Estructura de control do-while
    int j = 0;
    do{
        std::cout << j << std::endl;
        j++;
    } while (j < 5);

    // Estructura de control for
    for (int k = 0; k < 5; k++){
        std::cout << k << std::endl;
    }

    return 0;
}
