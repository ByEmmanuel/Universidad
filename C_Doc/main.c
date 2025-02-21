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
#include <string.h>
#include <_time.h>
#include <regex.h>
#include "LogicaNegocio.h"
#include "UsuarioDTO.h"


//variables
const int *pattern = "^[0-9]+$";  // Solo numeros

// Simulación de base de datos de usuarios y contraseñas

int bandera = 1;
int id_Usuario;

void menuPrincipal(int bandera){
    while (bandera){
        int opc;
        scanf("%i",&opc);
        //printf("Opcio usuario");
        printf("%i",opc);
        printf("\n");

        switch (opc){
        case 1:
            cliente();
            bandera = preguntaSalida();
            break;
        case 2:
            servicio();
            bandera = preguntaSalida();
            break;
        case 3:
            pago();
            bandera = preguntaSalida();
            break;
        case 4:
            almacen();
            bandera = preguntaSalida();
            break;
        case 5:
            otro();
            bandera = preguntaSalida();
            break;
        case 6:
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


int main(){
    mostrarLogo();
    if (loginUsuario() == 1){
        imprimirMenuPrincipal();
        menuPrincipal(bandera);
    }


    return 0;

}

