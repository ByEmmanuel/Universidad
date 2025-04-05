#include "UserInterface.h"

#include <ctype.h>

#include "LogicaNegocio.h"
#include "UsuarioDTO.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SIZE_DOS 2
#define SIZE_TRES 3
#define SIZE_CUATRO 4
#define SIZE_CINCO 5
#define SIZE_SEIS 6
#define SIZE_SIETE 7
int numOpciones = 0;


char** menuActual = NULL; // Apuntador genérico para evitar repetición de código.

int (*funcionesInt[SIZE_SIETE])() = {
    cliente, servicio, NULL, NULL, NULL, NULL, salir // Solo "Clientes" está implementado
};

void ejecutarOpcion(int opcion) {
    clear();
    opcion-=1;
    if (funcionesInt[opcion] != NULL) {
        mvprintw(10, 10, "Has seleccionado: Opción %d", opcion+1);
        refresh();
        funcionesInt[opcion]();  // Ejecuta la función de la opción
    } else {
        mvprintw(10, 10, "Opción %d no implementada aún.", opcion+1);
        refresh();
    }
    mvprintw(1, 60, "Presiona cualquier tecla para volver al menu...");
    refresh();
    getch();
}
//-------------------------------------FUNCION PRINCIPAL (VENTANA) --------------------------
void imprimirMenu(char* menu[], int numOpciones, int highlight) {
    for (int i = 0; i < numOpciones; i++) {
        if (i == highlight) {
            attron(A_REVERSE);
        }
        mvprintw(i + 5, 10, "%s", menu[i]);
        attroff(A_REVERSE);
    }
    refresh();
}

int mostrarMenu(int menuventana, const char* pregunta) {
    int ch, highlight = 0;
    char* menuUno[SIZE_SIETE] = {"Clientes", "Servicio", "Pago", "Almacen", "Otros", "Dudas", "Salir"};
    char* menuDos[SIZE_CUATRO] = {"Agregar Cliente", "Editar Cliente", "Listar Cliente", "Menu Principal"};
    char* menuTres[SIZE_SEIS] = {"Nombre", "Apellido", "Num Celular", "Email", "Contacto", "Salir"};
    char* menuCuatro[SIZE_SEIS] = {"Ingreso", "Lavado", "Medidas", "Rectificar", "Ensamble", "Salir"};
    char* menuCinco[SIZE_DOS] = {"CULATA", "MONOBLOCK"};
    char* menuSeis[SIZE_TRES] = {"1 : Gasolina","2: Diesel","3: Electrico"};
    char* menuSiete[SIZE_DOS] = {"SI","NO"};

    char** menuActual = NULL;
    int numOpciones = 0;
    switch (menuventana) {
    case 1: menuActual = menuUno; numOpciones = SIZE_SIETE; break;
    case 2: menuActual = menuDos; numOpciones = SIZE_CUATRO; break;
    case 3: menuActual = menuTres; numOpciones = SIZE_SEIS; break;
    case 4: menuActual = menuCuatro; numOpciones = SIZE_SEIS; break;
    case 5: menuActual = menuCinco; numOpciones = SIZE_DOS; break;
    case 6: menuActual = menuSeis; numOpciones = SIZE_TRES; break;
    case 7: menuActual = menuSiete; numOpciones = SIZE_DOS; break;
    default:
        mvprintw(10, 10, "Opción no válida o ocurrió un error");
        refresh();
        getch();
        return -1;
    }

    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    while (1) {
        clear();
        mvprintw(2, 10, "%s", pregunta); // Mostrar pregunta arriba
        imprimirMenu(menuActual, numOpciones, highlight); // El menú comienza en línea 5
        ch = getch();

        switch (ch) {
        case KEY_UP: highlight = (highlight == 0) ? numOpciones - 1 : highlight - 1; break;
        case KEY_DOWN: highlight = (highlight == numOpciones - 1) ? 0 : highlight + 1; break;
        case 10: return highlight + 1; // ENTER
        }
    }
}

// Función auxiliar para leer una cadena con ncurses
char* leerString(int y, int x, int maxLen) {
    char* buffer = (char*)malloc(maxLen + 1);
    if (!buffer) {
        mvprintw(y, x, "Error: No se pudo asignar memoria.");
        refresh();
        return NULL;
    }

    memset(buffer, 0, maxLen + 1); // Inicializa el buffer con ceros para evitar residuos
    echo(); // Mostrar lo que el usuario escribe
    mvgetnstr(y, x, buffer, maxLen); // Leer cadena con límite
    noecho(); // Desactivar eco después de leer

    // Si el usuario solo presiona ENTER, devolver NULL para manejarlo en otro lado
    if (strlen(buffer) == 0) {
        free(buffer);
        return NULL;
    }
    return buffer;
}

int* leerInt(int y, int x, int maxLen) {
    // Validar maxLen
    if (maxLen <= 0) {
        mvprintw(y + 1, x, "Error: Longitud máxima inválida.");
        refresh();
        return NULL;
    }
    char buffer[maxLen + 1];
    memset(buffer, 0, maxLen + 1);
    echo();
    mvgetnstr(y, x, buffer, maxLen);
    noecho();
    // Si la entrada está vacía, devolver NULL
    if (strlen(buffer) == 0) {
        return NULL;
    }
    // Verificar si es un número válido (incluyendo signo negativo)
    int i = 0;
    if (buffer[0] == '-') {
        i++; // Saltar el signo negativo
    }
    for (; buffer[i] != '\0'; i++) {
        if (!isdigit((unsigned char)buffer[i])) {
            mvprintw(y + 1, x, "Entrada no válida: solo números.");
            refresh();
            return NULL;
        }
    }
    // Convertir a entero con manejo de desbordamiento
    char* endptr;
    long numLong = strtol(buffer, &endptr, 10);
    if (*endptr != '\0' || numLong > INT_MAX || numLong < INT_MIN) {
        mvprintw(y + 1, x, "Error: Número fuera de rango.");
        refresh();
        return NULL;
    }
    // Asignar memoria para el resultado
    int* num = (int*)malloc(sizeof(int));
    if (!num) {
        mvprintw(y + 1, x, "Error: No se pudo asignar memoria.");
        refresh();
        return NULL;
    }
    *num = (int)numLong;
    return num;
}

float* leerFloat(int y, int x, int maxLen) {
    if (maxLen <= 0) {
        mvprintw(y + 1, x, "Error: Longitud máxima inválida.");
        refresh();
        return NULL;
    }
    char buffer[maxLen + 1];
    memset(buffer, 0, maxLen + 1);
    echo();
    mvgetnstr(y, x, buffer, maxLen);
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
            mvprintw(y + 1, x, "Error: Solo números Enteros.");
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