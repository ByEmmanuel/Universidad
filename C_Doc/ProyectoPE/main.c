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
    testing(0);
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
    //listarPiezas();

    return 0;
}

void menuPrincipal(){
    while (bandera){

        /*int* ptr_id_Cliente = leerInt(11, 15, 2);// Leer el entero
        if (ptr_id_Cliente == NULL) {
            mvprintw(12,15,"Error al leer Entrada.\n");
            return;
        }
        int opc = *ptr_id_Cliente;
        free(ptr_id_Cliente);  // Liberamos la memoria

        if (ptr_id_Cliente != NULL) {
            char buffer[12]; // Buffer para la cadena (suficiente para un int, incluyendo signo y terminador)
            snprintf(buffer, sizeof(buffer), "%d", opc); // Convertir el entero a cadena
            mvprintw(10, 15, buffer); // Mostrar la cadena en la pantalla
        } else {
            mvprintw(14, 10, "Entrada inválida"); // Manejar el caso de entrada inválida
        }
        refresh(); // Actualizar la pantalla*/
        int opc = mostrarVentana(1);
        //printf("%d",opc);
        ejecutarOpcion(opc);

        /*switch (opc){
        case 1:
            cleanScreen();
            cliente();
            //bandera = preguntaSalida();
            bandera = 0;
            break;
        case 2:
            cleanScreen();
            servicio();
            bandera = preguntaSalida();
            break;
        case 3:
            cleanScreen();
            pago();
            bandera = preguntaSalida();
            break;
        case 4:
            cleanScreen();
            almacen();
            bandera = preguntaSalida();
            break;
        case 5:
            cleanScreen();
            otro();
            bandera = preguntaSalida();
            break;
        case 6:
            cleanScreen();
            dudas();
            bandera = preguntaSalida();
            break;
        case 7:
            cleanScreen();
            mvprintw(10,15,"Gracias por usar el sistema");
            bandera = 0;
            break;
        default:
            mvprintw(10,15,"Introdujo una opcion Invalida");
            bandera = 0;
        }
        */

    }


};


