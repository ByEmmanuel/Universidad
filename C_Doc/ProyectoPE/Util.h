//
// Created by Jesus Emmanuel Garcia on 2/22/25.
// Esta SERA UNA LIBRERIA QUE SIMULARA O ABSTRAERA LAS FUNCIONES QUE TIENE JAVA Y OTROS LENGUAJES
// El proposito de esta libreria es disminuir la cantidad de lineas de codigo que puedo poner.
// Ayudando al entendimiento del codigo, legibilidad y mantenimiento

#ifndef Util_H
#define Util_H
#include <sys/_types/_size_t.h>
#include "UsuarioDTO.h"

//Strigs y metodos no agregados
char* strFill(const char* str);              // Elimina espacios al inicio y final
//int porque no hay bool y
int strEquals(const char* str1, const char* str2); // Compara dos cadenas
int strIsEmpty(const char* str);            // Verifica si una cadena está vacía
int strContains(const char* src, const char* str);
//Metodo agregado
void asignString(char *dst, const char *src, size_t n);
char* cinString(int bufferSize);

// ARRAYS
ArrayList* arrayListNew(size_t capacidadInicial);

void arrayListAdd(ArrayList* list, void* element);
void* arrayListGet(ArrayList* list, size_t index);
size_t arrayListSize(ArrayList* list);
void arrayListFree(ArrayList* list);
void arrayListClear(ArrayList* list);
//int arrayListContains(ArrayList* list, void* element, bool (*equals)(void*, void*)); // Verifica si contiene un elemento
void arrayListRemove(ArrayList* list, size_t index); // Elimina elemento por índice

// FECHA
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} SimpleDate;

SimpleDate* dateNow();                       // Obtiene la fecha y hora actual
char* dateToString(SimpleDate* date);        // Convierte a cadena legible
int dateCompare(SimpleDate* d1, SimpleDate* d2); // Compara dos fechas

char* generarFolio(const char *nombre);

// Buffer
void cleanBuffer();

void cleanScreen();
#endif //Util_H
