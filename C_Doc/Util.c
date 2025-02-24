//
// Created by Jesus Emmanuel Garcia on 2/22/25.
//

#include "Util.h"
#include <stdio.h>
#include <string.h>

// Copiamos las cadenas asegurándonos de que terminen en '\0'
void asignString(char *dst, const char *src, size_t n){
    strncpy(dst, src, n - 1);
    dst[n - 1] = '\0';
}

// Limpia cualquier residuo en el búfer
void cleanBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}