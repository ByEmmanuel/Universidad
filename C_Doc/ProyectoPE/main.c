/*
 * Hacer un programa de interface de usuario
 * Crear una constante de usuarios y contraseñas
 * Hacer logo
 * Esperar 3 segundos
 * Ingresar a interface de login
 * pasar a la pantalla de login y pedir usuario
 * si el usuario es valido entrar a la pantalla de contraseñas
 * maximo 3 intentos
 * si el usuario y contraseña son validos acceder al menu
 * si no salir y camniar el color de la terminal
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LogicaNegocio.h"
#include "UserInterface.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "Testing.h"

// Simulación de base de datos de usuarios y contraseñas

int bandera = 1;
int id_Usuario;

// Variable global para controlar el hilo del reloj
volatile int running = 1;

int main(){
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
     */
    testing(0);
    system("reset");
    clear();
    refresh();
    mostrarLogo();
    // Borra toda la pantalla y mueve el cursor al inicio

    //sleep(1);
    if (loginUsuario() == 1){
        menuPrincipal();
    }
    //imprimirPiezasPorUsuario(0);

    return 0;
}

void menuPrincipal(){
    initscr();
    while (bandera){
        const int opc = mostrarMenu(1," ");
        ejecutarOpcion(opc);
    }

};


