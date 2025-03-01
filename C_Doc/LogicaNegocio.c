//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//
#include "LogicaNegocio.h"
#include <stdio.h>
#include <string.h>
#include "UsuarioDTO.h"
#include "Util.h"

#define MAX_USUARIOS 6
#define MAX_LONGITUD 50

char usuariosRegistrados[MAX_USUARIOS][MAX_LONGITUD] =  {"David","Jose","Admin","Pepe","Luis","Maria"};
char contraseñasUsuarios[MAX_USUARIOS][MAX_LONGITUD] = {"123456789","987654321","01","24680"};

int loginUsuario(){
    int intentosUsuario = 0;

    do {
        printf("Ingrese Usuario: ");
        char* usuarioID = cinString(MAX_LONGITUD);
        // Buscar el usuario en la lista
        int usuarioIndex = -1;
        for (int i = 0; i < MAX_USUARIOS; i++) {
            if (strcmp(usuarioID, usuariosRegistrados[i]) == 0) {
                usuarioIndex = i;
                break;
            }
        }

        if (usuarioIndex != -1) {
            //char passwUsuario[MAX_LONGITUD];
            printf("Ingrese Contraseña: ");
            char* passwUsuario = cinString(MAX_LONGITUD);
            // Si se encontró el usuario
            //scanf("%s", passwUsuario);

            // Verificar contraseña
            if (strcmp(passwUsuario, contraseñasUsuarios[usuarioIndex]) == 0) {
                printf("Inicio de sesión exitoso.\n");
                return 1;
            }
            printf("Contraseña incorrecta.\n");
        } else {
            printf("Usuario no encontrado.\n");
        }

        intentosUsuario++;
    } while (intentosUsuario < 3);  // Permitir 3 intentos

    printf("Se agotaron los intentos.\n");
    return 0;
}

int servicio(){
    printf("Opcion Servicio ");
    return 0;
}

int pago(){
    printf("Opcion pago ");
    return 0;
}

int almacen(){
    printf("Opcion Almacen");
    return 0;
}

int otro(){
    printf("Opcion otro");
    return 0;
}

int validador(){
    return 0;
}

void imprimirMenuPrincipal(){
    printf("Ingrese la opcion que desea \n");
    for(int i = 0; i < 6; i++){
        char* menuUno[6] = {"Clientes","Pago","Almacen","Dudas","Otros","Salir"};
        printf(menuUno[i]);
        printf("\n");
    }
}

int preguntaSalida(){
    printf("\n  Desea Volver Al menu principal?\n 1 : SI \n 2 : NO \n");
    int opcUsuario;
    scanf("%d", &opcUsuario);
    printf("%i",opcUsuario);
    if(opcUsuario == 1){
        imprimirMenuPrincipal();
        return 1;
    }
    return 0;
}

void mostrarLogo(){
    printf("Bienvenido al sistema\n");
    printf("    ____           __ \n");
    printf("   / __/__    ____/ /___  _________ \n");
    printf("  / /_/ _ \\ / __  / __ / ___/ __ /\n");
    printf(" / __/  __/ /_/ / /_/ / /  / /_/ / \n");
    printf("/_/  \\___/\\__,_/\\____/_/   \\__,_/  \n");
    printf("      /\\     \n");
    printf("     /  \\    \n");
    // Ingresar delay y cambiar la pantalla de color

}