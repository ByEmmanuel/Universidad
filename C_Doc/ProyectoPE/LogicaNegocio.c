//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include "UsuarioDTO.h"
#include "Util.h"
#include "UserInterface.h"
#include "LogicaNegocio.h"

#define MAX_USUARIOS 6
#define MAX_LONGITUD 50

char usuariosRegistrados[MAX_USUARIOS][MAX_LONGITUD] =  {"David","Jose","Admin","Pepe","Luis",""};
char contraseñasUsuarios[MAX_USUARIOS][MAX_LONGITUD] = {"123456789","987654321","01","24680",""};

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
            if (strEquals(passwUsuario, contraseñasUsuarios[usuarioIndex])) {
                printf("Inicio de sesión exitoso.\n");
                //printf("\033[2J\033[H");
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
//Aqui iría va la funcion cliente pero esta puesta en DTO USUARIO

int servicio(){
    //Varibales locales
    // Material de la pieza (Hierro, Aluminio, etc.)
    // Nivel de desgaste en porcentaje (0-100%)
    // Tolerancia máxima de desgaste permitida antes de rectificar
    // Medida original de la pieza en mm
    // Medida actual después del desgaste
    TipoCombustible tipo_combustible = {};

    int opc = mostrarMenu(4,".");

    int opcusr;
    switch (opc){
        case 1:
            //Ingreso culata o monoblock
            //mvprintw(10,10,"Ingrese una opcion 1: Culata. 2: Monoblock");
            opcusr = mostrarMenu(5,".");
            if (opcusr == 1){
                 mvprintw(9,10,"Ingrese Id Usuario: ");
                //Esto debe ser el folio, pero esta agregado asi por temas de testeo
                const int id_Usuario = *leerInt(10,10,10000);
                //scanf("%d", &id_Usuario);
                //Generar numero de servicio

                // Ingresar material
                mvprintw(11,10,"Ingrese material del motor");
                const char* material = leerString(12,10,30);

                // Ingresar desgaste
                mvprintw(13,10,"Ingresar desgaste");
                const float desgaste = *leerFloat(14, 10, 30);
                // Ingresar tolerancia
                mvprintw(15,10,"Ingrese tolerancia");
                const float tolerancia = *leerFloat(16, 10, 100);
                // Ingresar medidaOriginal
                mvprintw(17,10,"Ingrese medida Original");
                const float medidaOriginal = *leerFloat(18, 10, 100);
                // Ingresar medidaActual
                mvprintw(19,10,"Ingrese Medida Actual");
                const float medidaActual = *leerFloat(20, 10, 100);
                // comprobar necesitaRectificacion
                //Funcion necesita rectificacion
                // Ingresar numValvulas
                mvprintw(21,10,"Ingrese numero Valvulas\n");
                const int numValvulas = *leerInt(22, 10, 50);
                // Ingresar presionPrueba
                mvprintw(23,10,"Ingrese PresionPrueba");
                const float presionPrueba = *leerFloat(24, 10, 20);
                // Ingresar tipoCombustible
                mvprintw(25,10,"Ingrese tipo de combustible");
                const int opcCombustible = mostrarMenu(6,".");

                switch (opcCombustible){
                case 1:
                    tipo_combustible = 0;
                    break;
                case 2:
                    tipo_combustible = 1;
                    break;
                case 3:
                    tipo_combustible = 2;
                    break;
                default:
                    tipo_combustible = 0;
                    break;
                }
                //Selectiva multiple
                // Ingresar tiene fisuras

                const int tieneFisuras = mostrarMenu(7,"¿Tiene Fisuras?");

                const int rectificacion = mostrarMenu(7,"¿Necesita Rectificación?");

                const Pieza piezaUsuario = inicializarPieza(id_Usuario, 1, material, desgaste, tolerancia, medidaOriginal, medidaActual, rectificacion);
                //Polimorfismo
                /*printf("Num valvulas %d,\nPresion Prueba %f,\nTipoCombustible %d,\nFisuras? %d\n", numValvulas,
                       presionPrueba, tipo_combustible, tieneFisuras);*/
                    Culata* pzc = malloc(sizeof(Culata));  // Reservamos memoria para Culata
                    *pzc = inicializarCulata(piezaUsuario, numValvulas, presionPrueba, tipo_combustible, tieneFisuras);
                    guardarPiezaArray((void*)pzc);  // Se guarda como puntero genérico

            }else if (opcusr == 2){

            }
            printf("Opcion no valida");

            break;
        case 2:
        //Lavado

            break;
        case 3:
        //Medidas

            break;
        case 4:
        //Rectificar

            break;
        case 5:
            //Ensamble

            break;
        case 6:
            //Menu Anterior
            return 1;
    default:
        break;
    }
    //Ingresar manualmente que es lo que se quiere reconstruir
    // Cabeza o culata

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

int dudas(){
    printf("Opcion Dudas");
    return 0;
}
// AQUI VAN LAS FUNCIONES QUE QUIERES QUE SE EJECUTEN ANTES DE QUE TERMINE EL PROGRAMA
int salir() {
    listarPiezas();
    exit(0);  // Finaliza el programa pero la terminal permanecerá abierta
}

void imprimirMenuPrincipal() {
    /*cleanScreen();
    usleep(2000);
    printf("┌──────────────────────────────┐\n");
    printf("│        MENÚ PRINCIPAL        │\n");
    printf("├──────────────────────────────┤\n");
    char* menuUno[7] = {"Clientes", "Servicio", "Pago", "Almacen", "Otros", "Dudas", "Salir"};
    for (int i = 0; i < 7; i++) {
        printf("│   %d - %-23s│\n", i+1, menuUno[i]);
    }
    printf("│                              │\n");
    printf("└──────────────────────────────┘\n");
    printf("\033[10;1HSeleccione una opción: ");*/

    //mainMenu();
}

void imprimirMenuServicio(){
    //menuServicio(0);

    /*
     *printf("\n┌──────────────────────────────┐\n");
    printf("│        MENÚ Servicio         │\n");
    printf("├──────────────────────────────┤\n");
    char* menu[6] = {"Ingreso","Lavado","Medidas","Rectificar","Ensamble","Salir O regresar"};
    for (int i = 0; i < 6; i++) {
        printf("│   %d - %-23s│\n", i+1, menu[i]);
    }
    printf("│                              │\n");
    printf("└──────────────────────────────┘\n");
    printf("\033[10;1HSeleccione una opción: ");
    */


}

int preguntaSalida(){
    /*cleanScreen();
    mvprintw(10,30,"Desea Volver Al menu principal? 1 : SI - 2 : NO ");
    int* opcUsuario = leerInt(10,30,2);
    mvprintw(10,15,"%d",*opcUsuario);
    if(*opcUsuario == 1){
        //imprimirMenuPrincipal();
        free(opcUsuario);
        return 1;
    }*/
    return 0;
}

void mostrarLogo(){
    printf("\nBienvenido al sistema\n");
    //usleep(300000);
    printf("    ____           __ \n");
    //usleep(300000);
    printf("   / __/__    ____/ /___  _________ \n");
    //usleep(300000);
    printf("  / /_/ _ \\ / __  / __ / ___/ __ /\n");
    //usleep(300000);
    printf(" / __/  __/ /_/ / /_/ / /  / /_/ / \n");
    //usleep(300000);
    printf("/_/  \\___/\\__,_/\\____/_/   \\__,_/  \n");
    //usleep(800000);
    printf("      /\\     \n");
    printf("     /  \\    \n");
    printf("    /    \\    \n");
    //sleep(1);
    // Ingresar delay y cambiar la pantalla de color

}

void testing(int encendido) {
    if (encendido) {
        usleep(200);
        printf("\n------TESTING MODE ON------");
        agregarUsuarios();
        agregarPiezas();
    }
}

void agregarUsuarios() {
    Usuario usuario1 = inicializarUsuario(0,"00001", "Usuario1", "Apellido 1", 1234567890, "EmailPrueba1@1", "Contacto1");
    guardarUsuarioArray(usuario1);
    Usuario usuario2 = inicializarUsuario(1,"00002", "Usuario2", "Apellido 2", 1987654321, "EmailPrueba2@2", "Contacto2");
    guardarUsuarioArray(usuario2);
}

void agregarPiezas() {
    Pieza piezaUsuario = inicializarPieza(0, 1, "Metal", .1123, .1125, .1300, .1180, 2);
    Culata* pzc = malloc(sizeof(Culata));
    *pzc = inicializarCulata(piezaUsuario, 16, .10, 2,2);
    guardarPiezaArray((void*)pzc);  // Se guarda como puntero genérico

    Pieza piezaUsuario2 = inicializarPieza(1, 2, "Aluminio", 0.1000, 0.1050, 0.1250, 0.1150, 1);
    Culata* pzc2 = malloc(sizeof(Culata));
    *pzc2 = inicializarCulata(piezaUsuario, 18, 0.12, 1, 3);
    guardarPiezaArray((void*)pzc2);
}