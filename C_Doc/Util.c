//
// Created by Jesus Emmanuel Garcia on 2/22/25.
//

#include "Util.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Funciones importantes para reducir la repeticion de codigo
//  strcspn
//  strncpy
//  strstr
//  fgets

//  realloc, malloc

// Macros para verificar el sistema operativo

char* strFill(const char* str) {
    if (str == NULL) return NULL;

    // Encuentra el inicio (saltando espacios)
    const char* start = str;
    while (*start == ' ') start++;

    // Si la cadena es solo espacios o vacía
    if (*start == '\0') {
        char* result = (char*)malloc(1);
        result[0] = '\0';
        return result;
    }

    // Encuentra el final (retrocediendo desde el último carácter no espacio)
    const char* end = str + strlen(str) - 1;
    while (end > start && *end == ' ') end--;

    // Calcula la longitud de la nueva cadena
    int len = end - start + 1;
    char* result = (char*)malloc(len + 1); // +1 para el '\0'
    if (result == NULL) return NULL;

    // Copia la subcadena
    strncpy(result, start, len);
    result[len] = '\0';
    return result;
}
// Compara dos cadenas
int strEquals(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return (str1 == str2); // Ambos NULL = iguales, uno NULL = diferentes
    }
    return strcmp(str1, str2) == 0; // 1 si son iguales, 0 si no
}
// Verifica si una cadena está vacía
int strIsEmpty(const char* str) {
    if (str == NULL) return 1;      // NULL se considera vacío
    return str[0] == '\0';          // 1 si es "", 0 si no
}
// Verifica si una cadena contiene a otra
int strContains(const char* src, const char* str) {
    if (src == NULL || str == NULL) return 0;
    return strstr(src, str) != NULL; // 1 si str está en src, 0 si no
}
// Copiamos las cadenas asegurándonos de que terminen en '\0'
// Funcion que Asigna una cadena a otra Es decir algo como
// var1 = "idk" var2 = var1 sin paso por referencia y borra el ultimo caracter que deja fgets
void asignString(char *dst, const char *src, const size_t n){
    strncpy(dst, src, n - 1);
    dst[n - 1] = '\0';
}

// Funcion para evitar usar scanF y evitar desbordamientos de buffer
char* cinString(const int bufferSize) {
    // Validar el tamaño del búfer
    if (bufferSize <= 0){
        printf("Tamaño de búfer inválido: %d\n", bufferSize);
        return NULL;
    };
    // Reservar memoria
    char* opcUsr = (char*)malloc(bufferSize);
    if (opcUsr == NULL){ printf("Error de memoria al reservar %d bytes\n", bufferSize);  return NULL;};
    // Leer la entrada
    if (fgets(opcUsr, bufferSize, stdin) == NULL) {
        printf("Error al leer la entrada o EOF detectado\n");
        free(opcUsr);
        return NULL;
    }
    opcUsr[strcspn(opcUsr, "\n")] = '\0';
    return opcUsr;
}

char* generarFolio(const char *nombre) {
    char* folio = (char*)malloc(13);

    if (folio == NULL) {
        printf("Error de memoria al reservar %d bytes\n", 13);
        return NULL;
    }

    int len = strlen(nombre);

    // Usar las primeras 3 letras del nombre o rellenar con 'X' si es más corto
    for (int i = 0; i < 3; i++) {
        if (i < len) {
            folio[i] = toupper(nombre[i]); // Convertir a mayúscula
        } else {
            folio[i] = 'X';
        }
    }

    // Generar 9 números pseudo-aleatorios en base al nombre
    srand(time(NULL) + len); // Semilla basada en el tiempo y longitud del nombre
    for (int i = 3; i < 12; i++) {
        folio[i] = '0' + rand() % 10;
    }

    // Fin de cadena
    folio[12] = '\0';
    return folio;
}
// Limpia cualquier residuo en el búfer
void cleanBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


void cleanScreen(){
    printf("\033[2J\033[H");
}