//Utils
#ifndef Util_H
#define Util_H
#define RETURN_IF_ESC(x) if ((x) == -1) return -1
#define LEERINT_ESC -1
#define LEERINT_ERROR -2
#define LEERINT_EMPTY -3
#include <stddef.h>
#include <stdio.h>
#include "UsuarioDTO.h"

int strEquals(const char* str1, const char* str2);
int strIsEmpty(const char* str);
int strContains(const char* src, const char* str);
void asignString(char* dst, const char* src, size_t n);
char* enterString(int length);

char* generarFolio(const char* nombre);

int validarString(const char* src);
int leerIntSeguro(int y, int x, int maxLen, char* pregunta);
float leerFloatSeguro(int y, int x, int maxLen, char* pregunta);
char* leerStringSeguro(int y, int x, int maxLen, char* pregunta);
void imprimirTextoMultilinea(int fila, int columna, const char* texto, int anchoMaximo);
void imprimirTextoMultilineaArchivo(FILE* archivo, const char* texto, int anchoMaximo);

void cleanBuffer();

void cleanScreen();
#endif
