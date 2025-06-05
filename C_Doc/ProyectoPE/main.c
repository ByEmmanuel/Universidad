#include <curses.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "LogicaNegocio.h"
#include "reloj.h"
#include "UserInterface.h"
#include "Testing.h"

// Simulacion de base de datos de usuarios y contraseñas
int id_Usuario;

// Variable global para controlar el hilo del reloj
volatile int running = 1;
int testingMode;

int main() {
    // Inicio del programa
    /** TESTING MODE
     *  motoresDB = CANTIDAD DE MOTORES QUE TIENE EN EL SISTEMA (Precargando su informacion total) USANDO NUMERO DE SERIE
     *  variable donde se guardanLosMotoresPrecargados : (arrayMotoresPrecargados);
     *  Funcion donde se precargan los motores (precargarMotoresDB(););
     *  0 = no testing mode
     *  1 = agregar usuarios
     *  2 = agregar motores y piezas -> Estos pertenecen a un usuario --> ¿Porque agregarias motores sin un usuario?
     *  3 = agregar usuarios y (motores y piezas) -> Estos pertenecen a un usuario
     *  4 = agregar usuarios con motoresDB precargados
     *  5 = agregar usuarios, (motores y piezas) y agregar MotoresPrecargados;
     *  6 = solo precargar motores (arrayMotoresPrecargados)
    precargarMotoresDB(motoresExistentesSINCulatasAsignadas, cantidadMotores);
     */
    testingMode = 0;

    system("reset");
    printf("Las credenciales son:\n Usuario ADMIN(Testing Mode) : 'Admin' \n Password : '01'\n Usuario (Empleado): 'Pepe' \n Password : '24680',\n Usuario (Tecnico) : 'Tecnico' \n Password : '0001'");
    testing(testingMode);
    clear();
    refresh();
    mostrarLogo();

    //sleep(3);
    switch (loginUsuario()) {
        case 1:
            //sleep(1);
            cargarAlmacen();
            menuPrincipal();
        break;
        case 2:
            testingMode = 4;
            printf("\nTesting Mode: %d",testingMode);
            printf("\nCargando...");
            testing(testingMode);
            sleep(3);
            cargarAlmacen();
            menuPrincipal();
            break;
        case 3:
            testingMode = 5;
            printf("\nTesting Mode: %d",testingMode);
            printf("\nCargando...");
            testing(testingMode);
            sleep(3);
            cargarAlmacen();
            menuPrincipal();
            break;
        default:
            printf("Opcion no valida");
            break;
    }
    printf("\033[31m\n\033[0m\n");
    printf("\033[31m\n\033[0m\n");
    printf("\033[31m\n\033[0m\n");
    printf("\033[31m\n\033[0m\n");
    printf("\033[31m\n\033[0m\n");
    printf("\033[31m\n\033[0m\n");
    printf("\033[31m\nLogin Invalido\033[0m\n");
    printf("\033[31m\n\033[0m\n");
    printf("\033[31m\n\033[0m\n");
    printf("\033[31m\n\033[0m\n");
    printf("\033[31m\n\033[0m\n");
    //imprimirPiezasPorUsuario(0);

    return 0;
}

void menuPrincipal() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);


    //ClockData clock_data;
    //clock_data.win = stdscr;
    //clock_data.running = 1;

    //pthread_t clock_tid;
    //pthread_create(&clock_tid, NULL, clock_thread, &clock_data);

    while (1) {
        const int opc = mostrarMenu(1, " ");
        if (opc == -1) {
    //        clock_data.running = 0;
      //      pthread_join(clock_tid, NULL);
            /*
            clock_data.running = 0;
            pthread_join(clock_tid, NULL);
            */
            endwin();
            break;
        }
        ejecutarOpcion(opc);
    }
}