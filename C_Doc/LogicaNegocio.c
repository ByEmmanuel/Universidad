//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//
#include "LogicaNegocio.h"
#include <stdio.h>
#include <string.h>

#include "NegocioDTO.h"

#define MAX_USUARIOS 6
#define MAX_LONGITUD 50

char usuariosRegistrados[MAX_USUARIOS][MAX_LONGITUD] =  {"David","Jose","Admin","Pepe","Luis","Maria"};
char contraseñasUsuarios[MAX_USUARIOS][MAX_LONGITUD] = {"123456789","987654321","01","24680"};

int loginUsuario(){
    int intentosUsuario = 0;

    do {
        char usuarioID[MAX_LONGITUD];
        printf("Ingrese Usuario: ");
        scanf("%s", usuarioID);

        // Buscar el usuario en la lista
        int usuarioIndex = -1;
        for (int i = 0; i < MAX_USUARIOS; i++) {
            if (strcmp(usuarioID, usuariosRegistrados[i]) == 0) {
                usuarioIndex = i;
                break;
            }
        }

        if (usuarioIndex != -1) {
            char passwUsuario[MAX_LONGITUD];
            // Si se encontró el usuario
            printf("Ingrese Contraseña: ");
            scanf("%s", passwUsuario);

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

int menuPrincipal(int bandera){
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
    scanf("%i", &opcUsuario);
    printf("%i",opcUsuario);
    if(opcUsuario == 1){
        imprimirMenuPrincipal();
        return 1;
    }
    return 0;
}