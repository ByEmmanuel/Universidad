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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LogicaNegocio.h"
#include "UsuarioDTO.h"
#include "UserInterface.h"
#include <pthread.h>
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
    mostrarLogo();
    // Borra toda la pantalla y mueve el cursor al inicio
    cleanScreen();
    sleep(1);
    if (loginUsuario() == 1){
        //imprimirMenuPrincipal();
        mostrarVentana(1);
        menuPrincipal(bandera);
    }
    //imprimirPiezasPorUsuario(0);
    listarPiezas();

    return 0;
}

void menuPrincipal(int bandera){
    while (bandera){
        int opc;
        scanf("%d",&opc);
        //printf("Opcio usuario");
        printf("%i",opc);
        printf("\n");

        switch (opc){
        case 1:
            cleanScreen();
            cliente();
            bandera = preguntaSalida();
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
            printf("Gracias por usar el sistema");
            bandera = 0;
            opc = 0;
            break;
        default:
            printf(" introdujo una opcion Invalida");
            bandera = 0;
        }
    }

};


