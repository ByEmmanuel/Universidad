/*
*  Quinto Archivo
* Nombre: Operadores Y Operadores Matematicos
* Autor: ByEmmanuel
* Fecha: 06-09-2024
* Descripcion: Tipos de Operadores en C++
* Los operadores son simbolos que permiten realizar operaciones sobre variables y valores
* Los operadores en C++ se dividen en varios tipos:
*  - aritmeticos,
*  - relacionales,
*  - logicos,
*  - de asignacion,
*  - de incremento y decremento,
*  - de bits
*  - y condicionales
*/

#include <iostream>

int mainOperadores(){

    // Suma (+): Suma dos valores
    int a = 5 + 3;  // a = 8
    // Resta (-): Resta dos valores
    int b = 5 - 3;  // b = 2

    // Multiplicacion (*): Multiplica dos valores
    int c = 5 * 3;  // c = 15
    // Division (/): Divide dos valores
    int d = 5 / 3;  // d = 1

    // Modulo (%): Obtiene el resto de la division
    int e = 5 % 3;  // e = 2

    // Incremento (++): Incrementa en 1 el valor de una variable
    int f = 5;
    f++;  // f = 6

    // Decremento (--): Decrementa en 1 el valor de una variable
    int g = 5;
    g--;  // g = 4
    std::cout <<"Clase 5, Operadores" << "El resultado es: " << g << std::endl;

    // Operadores de asignacion
    int h = 5;
    h += 3;  // h = h + 3 = 8
    h -= 3;  // h = h - 3 = 5
    h *= 3;  // h = h * 3 = 15
    h /= 3;  // h = h / 3 = 5
    h %= 3;  // h = h % 3 = 2

    // Operadores de comparacion
    int i = 5;
    int j = 3;
    // ==, !=, >, <, >=, <=
    //parecido, diferente, mayor, menor, mayor o igual, menor o igual
    bool k = i == j;  // k = false
    bool l = i != j;  // l = true
    bool m = i > j;   // m = true
    bool n = i < j;   // n = false
    bool o = i >= j;  // o = true
    bool p = i <= j;  // p = false

    // Operadores logicos
    bool q = true;
    bool r = false;
    bool s = q && r;  // s = false
    bool t = q || r;  // t = true
    bool u = !q;      // u = false

    // Operadores de bits
    int v = 5;  // 101
    int w = 3;  // 011
    int x = v & w;  // x = 1
    int y = v | w;  // y = 7
    int z = v ^ w;  // z = 6
    int aa = ~v;    // aa = -6

    // Operador condicional
    int ab = 5;
    int ac = 3;
    int ad = ab > ac ? 10 : 20;  // ad = 10

    // Operador de miembro
    int ae = 5;
    int *af = &ae;  // af = 5
    int ag = *af;   // ag = 5
    double ah = 5.5;
    int ai = (int)ah;  // ai = 5

    // Operador de direccion
    int aj = 5;
    int *ak = &aj;  // ak = 5

    // Operador de indireccion
    int al = 5;
    int *am = &al; // am = 5
    int an = *am;  // an = 5

    // Operador de tamaño
    int ao = sizeof(int);  // ao = 4

    // Operador de tipo
    int ap = 5;
    int aq = static_cast<double>(ap);  // aq = 5.0

    // Operador de rango
    int ar = 5;
    int as = 1;
    int at = 10;
    bool au = ar > as && ar < at;  // au = true

    // Operador de coma (Varias Asignaciones)
    int av = 5, aw = 3;  // av = 5, aw = 3

    // Operador de direccion de memoria
    int ax = 5;
    int *ay = &ax;  // ay = 5

    // Operador de indireccion de memoria
    int az = 5;
    int *ba = &az;  // ba = 5
    int bb = *ba;    // bb = 5

    // Operador de tamaño de memoria
    int bc = sizeof(int);  // bc = 4
    std::cout << "Clase 5, Operadores" << "El tamaño de memoria es: " << bc << std::endl;

    // Operador de tipo de memoria
    int bd = 5;
    int be = static_cast<double>(bd);  // be = 5.0

    // Operador de rango de memoria
    int bf = 5;
    int bg = 1;
    int bh = 10;
    bool bi = bf > bg && bf < bh;  // bi = true

    // Operador de coma
    int bj = 5, bk = 3;  // bj = 5, bk = 3

    return 0;
}
