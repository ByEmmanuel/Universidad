#include "UserInterface.h"

#include <ctype.h>

#include "LogicaNegocio.h"
#include "UsuarioDTO.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <arm/limits.h>

#define NUM_OPTIONS 7

int (*funcionesInt[NUM_OPTIONS])() = {
    cliente, /*servicio*/ NULL, NULL, NULL, NULL, NULL, salir // Solo "Clientes" está implementado
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
int mostrarVentana(int menuventana)
{
    int ch, highlight = 0;
    char* menuUno[NUM_OPTIONS] = {"Clientes", "Servicio", "Pago", "Almacen", "Otros", "Dudas", "Salir"};

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    while (1)
    {
        switch (menuventana)
        {
        case 1:
            clear();
            for (int i = 0; i < NUM_OPTIONS; i++)
            {
                if (i == highlight)
                {
                    attron(A_REVERSE);
                }
                mvprintw(i + 5, 10, "%s", menuUno[i]);
                attroff(A_REVERSE);
            }
            refresh();
            break;
        default:
            mvprintw(10, 10, "Opción no válida o ocurrió un error");
            refresh();
            getch();
        //@Deprecated
        //endwin();
            return -1; // Retorno de error
        }

        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            highlight = (highlight == 0) ? NUM_OPTIONS - 1 : highlight - 1;
            break;
        case KEY_DOWN:
            highlight = (highlight == NUM_OPTIONS - 1) ? 0 : highlight + 1;
            break;
        case 10: // ENTER
            //endwin();
            return highlight + 1; // Retorna la opción seleccionada
        }
    }
}

//------------------------------------------- FUNCIONES MENU CLIENTES ------------------------


int menuCliente() {
    int opcion = 0;
    int ch;
    const int numOpciones = 4;
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    // Solo un clear() es suficiente
    while (1) {
        for (int i = 0; i < numOpciones; i++) {
            if (i == opcion) {
                attron(A_REVERSE);
            }
            switch (i) {
            case 0: mvprintw(5, 10, "Agregar Cliente"); break;
            case 1: mvprintw(6, 10, "Editar Cliente"); break;
            case 2: mvprintw(7, 10, "Listar Cliente"); break;
            case 3: mvprintw(8, 10, "Menu Principal"); break;
            }
            attroff(A_REVERSE);
        }
        refresh();
        ch = getch();

        switch (ch) {
        case KEY_UP:
            opcion = (opcion == 0) ? numOpciones - 1 : opcion - 1;
            break;
        case KEY_DOWN:
            opcion = (opcion == numOpciones - 1) ? 0 : opcion + 1;
            break;
        case 10:  // ENTER: Confirmar selección
            return opcion+1;
        }
    }
    return 0; // Nunca se alcanza, pero por seguridad
}

int menuModificarCliente() {
    int opcion = 0;
    int ch;
    const int numOpciones = 6;
    char* opciones[numOpciones] = {"Nombre", "Apellido", "Num Celular", "Email", "Contacto", "Salir"};

    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);


    while (1) {
        for (int i = 0; i < numOpciones; i++) {
            if (i == opcion) {
                attron(A_REVERSE);
            }
            mvprintw(i + 5, 10, "%s", opciones[i]);
            attroff(A_REVERSE);
        }
        refresh();

        ch = getch();

        switch (ch) {
        case KEY_UP:
            opcion = (opcion == 0) ? numOpciones - 1 : opcion - 1;
            break;
        case KEY_DOWN:
            opcion = (opcion == numOpciones - 1) ? 0 : opcion + 1;
            break;
        case 10:  // ENTER: Confirmar selección
            return opcion + 1;
        default: break;
        }
    }
}
//------------------------------------------- FUNCIONES MENU SERVICIO ------------------------
int menuServicio(){

}

;


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