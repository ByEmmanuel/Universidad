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
#include "UsuarioDTO.h"
#include "UserInterface.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "Util.h"


// Simulación de base de datos de usuarios y contraseñas

int bandera = 1;
int id_Usuario;

// Variable global para controlar el hilo del reloj
volatile int running = 1;

int main(){
    // Inicio del programa
    testing(1);
    system("reset");
    clear();
    refresh();
    mostrarLogo();
    // Borra toda la pantalla y mueve el cursor al inicio

    sleep(1);
    if (loginUsuario() == 1){
        //imprimirMenuPrincipal();
        //mostrarVentana(1);
        menuPrincipal();
    }
    //imprimirPiezasPorUsuario(0);


    return 0;
}

void menuPrincipal(){
    initscr();
    while (bandera){
        int opc = mostrarMenu(1,".");
        ejecutarOpcion(opc);
    }

};


