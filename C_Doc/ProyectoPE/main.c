//Main
#include <curses.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "LogicaNegocio.h"
#include "reloj.h"
#include "UserInterface.h"
#include "Testing.h"

int id_Usuario;

volatile int running = 1;
int testingMode;

int main() {
    testingMode = 1;
    testing(testingMode);
    system("reset");
    clear();
    refresh();
    mostrarLogo();


    if (loginUsuario() == 1) {
        cargarAlmacen();
        menuPrincipal();
    }


    return 0;
}

void menuPrincipal() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);


    ClockData clock_data;
    clock_data.win = stdscr;
    clock_data.running = 1;

    pthread_t clock_tid;
    pthread_create(&clock_tid, NULL, clock_thread, &clock_data);

    while (1) {
        const int opc = mostrarMenu(1, " ");
        if (opc == -1) {
            clock_data.running = 0;
            pthread_join(clock_tid, NULL);
            endwin();
            break;
        }
        ejecutarOpcion(opc);
    }
}
