//
// Created by Jesus Emmanuel Garcia on 2/22/25.
//

#include "Util.h"

#include <ctype.h>
#include <limits.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "UserInterface.h"


//Funciones importantes para reducir la repeticion de codigo
//  strcspn
//  strncpy
//  strstr
//  fgets

//  realloc, malloc

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

int validarString(const char* src) {
    if (src == NULL) {
        // usuario presionó ESC o no ingresó nada
        return -1;
    }
    return 1;
}

// Función auxiliar para leer una cadena con ncurses
char* leerString(int y, int x, int maxLen, char* pregunta) {
    mvprintw(y, x, "%s: ", pregunta);
    char* buffer = (char*)malloc(maxLen + 1);
    if (!buffer) {
        mvprintw(y + 1, x, "Error: No se pudo asignar memoria.");
        refresh();
        return NULL;
    }
    memset(buffer, 0, maxLen + 1);

    noecho(); // Desactivar echo para controlar manualmente
    cbreak();  // Desactivar buffer de línea
    keypad(stdscr, TRUE); // Permitir teclas especiales

    int ch, pos = 0;
    move(y, x + strlen(pregunta) + 2);

    while (1) {
        ch = getch();
        if (ch == 27) { // ESC
            free(buffer);
            return NULL;
        } else if (ch == '\n' || ch == KEY_ENTER) {
            break;
        } else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
            if (pos > 0) {
                pos--;
                move(y, x + strlen(pregunta) + 2 + pos);
                addch(' ');
                move(y, x + strlen(pregunta) + 2 + pos);
                buffer[pos] = '\0';
                refresh();
            }
        } else if (isprint(ch) && pos < maxLen) {
            buffer[pos] = ch;
            mvaddch(y, x + strlen(pregunta) + 2 + pos, ch);
            pos++;
            refresh();
        }
    }

    buffer[pos] = '\0';
    if (strlen(buffer) == 0) {
        free(buffer);
        return NULL;
    }
    return buffer;
}

int* leerInt(int y, int x, int maxLen, char* pregunta, int* codigoError) {
    // Inicializar código de error a 0 (sin error)
    if (codigoError) *codigoError = 0;

    mvprintw(y, x, "%s: ", pregunta);
    refresh();

    char buffer[maxLen + 1];
    memset(buffer, 0, maxLen + 1);
    echo();

    // Captura con detección de ESC directamente
    int ch = getch();
    if (ch == 27) {  // ESC presionado antes de escribir
        noecho();
        if (codigoError) *codigoError = LEERINT_ESC;
        return NULL;
    }

    // Si no es ESC, regresamos el carácter al buffer de entrada
    ungetch(ch);

    mvgetnstr(y, x + (int)strlen(pregunta) + 2, buffer, maxLen);
    noecho();

    if (strlen(buffer) == 0) {
        if (codigoError) *codigoError = LEERINT_EMPTY;
        return NULL;
    }

    // Validación numérica
    int i = 0;
    if (buffer[0] == '-') i++;
    for (; buffer[i] != '\0'; i++) {
        if (!isdigit((unsigned char)buffer[i])) {
            mvprintw(y + 1, x, "Entrada no válida: solo números.");
            refresh();
            if (codigoError) *codigoError = LEERINT_ERROR;
            return NULL;
        }
    }

    // Conversión con control de límites
    char* endptr;
    long numLong = strtol(buffer, &endptr, 10);
    if (*endptr != '\0' || numLong > INT_MAX || numLong < INT_MIN) {
        mvprintw(y + 1, x, "Error: número fuera de rango.");
        refresh();
        if (codigoError) *codigoError = LEERINT_ERROR;
        return NULL;
    }

    int* num = (int*)malloc(sizeof(int));
    if (!num) {
        mvprintw(y + 1, x, "Error al asignar memoria.");
        refresh();
        if (codigoError) *codigoError = LEERINT_ERROR;
        return NULL;
    }

    *num = (int)numLong;
    return num;
}

float* leerFloat(int y, int x, int maxLen, char* pregunta) {
    mvprintw(y, x, "%s: ", pregunta);
    if (maxLen <= 0) {
        mvprintw(y + 1, x, "Error: Longitud máxima inválida.");
        refresh();
        return NULL;
    }

    char buffer[maxLen + 1];
    memset(buffer, 0, maxLen + 1);
    echo();
    mvgetnstr(y, x + strlen(pregunta) + 2, buffer, maxLen);
    noecho();

    if (strlen(buffer) == 0) {
        return NULL;
    }
    // Validación: permitir números con signo y punto decimal
    int i = 0, dotCount = 0;
    if (buffer[0] == '-') {
        i++;  // Saltar el signo negativo
    }

    for (; buffer[i] != '\0'; i++) {
        if (buffer[i] == '.') {
            dotCount++;
            if (dotCount > 1) { // Más de un punto decimal es inválido
                mvprintw(y + 1, x, "Error: Número no válido.");
                refresh();
                return NULL;
            }
        } else if (!isdigit((unsigned char)buffer[i])) {
            mvprintw(y + 1, x, "Error: Solo números válidos.");
            refresh();
            return NULL;
        }
    }
    // Convertir a float usando strtof
    char* endptr;
    float numFloat = strtof(buffer, &endptr);
    if (*endptr != '\0') {
        mvprintw(y + 1, x, "Error: Conversión inválida.");
        refresh();
        return NULL;
    }
    // Reservar memoria para el número y devolverlo
    float* num = (float*)malloc(sizeof(float));
    if (!num) {
        mvprintw(y + 1, x, "Error: No se pudo asignar memoria.");
        refresh();
        return NULL;
    }

    *num = numFloat;
    return num;
}

int leerIntSeguro(int y, int x, int maxLen, char* pregunta) {
    int* valor = NULL;
    int codigoError = 0;

    do {
        // Limpiar la línea donde se mostrará el mensaje de error
        move(y + 1, x);
        clrtoeol();
        refresh();

        valor = leerInt(y, x, maxLen, pregunta, &codigoError);

        // Si valor es NULL, verificamos el código de error
        if (valor == NULL) {
            if (codigoError == LEERINT_ESC) {
                return -1; // Retornar -1 si se presionó ESC
            }
            // Para otros errores (entrada vacía o inválida), continuamos el bucle
        }
    } while (valor == NULL);

    int resultado = *valor;
    free(valor);
    return resultado;
}

float leerFloatSeguro(int y, int x, int maxLen, char* pregunta) {
    float* valor = NULL;
    do {
        valor = leerFloat(y, x, maxLen, pregunta);
        if (valor == NULL) {
            mvprintw(y + 2, x , "X Entrada invalida. Intentalo de nuevo.");
            getch();
            refresh();
        }
    } while (valor == NULL);

    float resultado = *valor;
    free(valor);
    return resultado;
}


char* leerStringSeguro(int y, int x, int maxLen, char* pregunta) {
    char* valor = NULL;
    do {
        valor = leerString(y, x, maxLen, pregunta);
        if (valor == NULL) {
            mvprintw(y + 2, x , "X Entrada invalida. Intentalo de nuevo.");
            refresh();
            getch();
            // salir si es ESC
            return NULL;
        }
    } while (valor == NULL);

    //char* resultado = valor;
    return valor;
    //return leerString(y, x, maxLen, pregunta);
}

void cleanScreen(){
    //clear();
    printf("\033[2J\033[H");
}