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
#include "NegocioDTO.h"



//variables
const int *pattern = "^[0-9]+$";  // Solo numeros

// Simulación de base de datos de usuarios y contraseñas

int bandera = 1;
int id_Usuario;


int main(){
    printf("Bienvenido al sistema\n");
printf("    ____         __ \n");
printf("   / __/__  ____/ /___  _________ _\n");
printf("   / __/__  ____/ /___  _________ _\n");
printf("  / /_/ _ \\/ __  / __ \\/ ___/ __ `/\n");
printf("/ __/  __/ /_/ / /_/ / /  / /_/ / \n");
printf("/_/  \\___/\\__,_/\\____/_/   \\__,_/  \n");
printf("      /\\     \n");
printf("     /  \\    \n");

    if (loginUsuario() == 1){
        imprimirMenuPrincipal();
        menuPrincipal(bandera);
    }


    return 0;

}

