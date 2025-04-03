#include "UserInterface.h"
#include "LogicaNegocio.h"
#include "UsuarioDTO.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OPTIONS 7

int (*funcionesInt[NUM_OPTIONS])() = {
    cliente, NULL, NULL, NULL, NULL, NULL, NULL // Solo "Clientes" está implementado
};

void mainMenu(int highlight) {
    char* menuUno[NUM_OPTIONS] = {"Clientes", "Servicio", "Pago", "Almacen", "Otros", "Dudas", "Salir"};
    clear();
    for (int i = 0; i < NUM_OPTIONS; i++) {
        if (i == highlight) {
            attron(A_REVERSE);
        }
        mvprintw(i + 5, 10, "%s", menuUno[i]);
        attroff(A_REVERSE);
    }
    refresh();
}

/*void menuModificarCliente(int highlight ) {
    char* menuUno[7] = {"Nombre", "Apellido", "Num Celular", "Email", "Contacto", "Salir"};
    clear();
    for (int i = 0; i < NUM_OPTIONS; i++) {
        if (i == highlight) {
            attron(A_REVERSE);
        }
        mvprintw(i + 5, 10, "%s", menuUno[i]);
        attroff(A_REVERSE);
    }
    refresh();
}*/

int menuCliente() {
    int opcion = 0;
    int ch;
    const int numOpciones = 4;
     clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    clear();  // Limpia la pantalla antes de mostrar el menú
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
                return opcion + 1;
        }
    }
    return 0;
}

void ejecutarOpcion(int opcion) {
    clear();
    if (funcionesInt[opcion] != NULL) {
        mvprintw(10, 10, "Has seleccionado: Opción %d", opcion + 1);
        refresh();
        funcionesInt[opcion]();  // Ejecuta la función de la opción
    } else {
        mvprintw(10, 10, "Opción %d no implementada aún.", opcion + 1);
        refresh();
    }
    mvprintw(1, 60, "Presiona cualquier tecla para volver al menu...");
    refresh();
    getch();
}

void mostrarVentana(int menuventana) {
    int ch, highlight = 0;

    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    while (1) {
        switch (menuventana) {
            case 1:
                mainMenu(highlight);
                break;
            default:
                mvprintw(10, 10, "Opción no válida o ocurrió un error");
                refresh();
                getch();
                endwin();
                return;
        }
        ch = getch();

        switch (ch) {
            case KEY_UP:
                highlight = (highlight == 0) ? NUM_OPTIONS - 1 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == NUM_OPTIONS - 1) ? 0 : highlight + 1;
                break;
            case 10:  // ENTER
                if (highlight == NUM_OPTIONS - 1) { // "Salir"
                    endwin();
                    return;
                }
                ejecutarOpcion(highlight);
                break;
        }
    }
    endwin();
}

// Función auxiliar para leer una cadena con ncurses
char* leerEntrada(int y, int x, int maxLen) {
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