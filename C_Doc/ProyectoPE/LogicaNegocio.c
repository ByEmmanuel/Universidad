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

char* enterString(int length) {
    char* buffer = (char*)malloc(length + 1); // Reservar espacio para la cadena
    if (buffer == NULL) {
        perror("Error al asignar memoria");
        exit(1);
    }
    if (fgets(buffer, length + 1, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar el salto de línea al final
    }
    return buffer;
}

int loginUsuario(){
    int intentosUsuario = 0;

    do {
        printf("Ingrese Usuario: ");
        // Función para leer cadenas de manera segura
        char* usuarioID = enterString(MAX_LONGITUD);
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
            char* passwUsuario = enterString(MAX_LONGITUD);
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

    const int opc = mostrarMenu(4,".") + 1;
    RETURN_IF_ESC(opc);
    int opcusr;
    switch (opc){
        case 1:
            //Ingreso culata o monoblock
            //mvprintw(10,10,"Ingrese una opcion 1: Culata. 2: Monoblock");
            opcusr = mostrarMenu(5,".") + 1;
            RETURN_IF_ESC(opcusr);
            listarFoliosUsuarios();
            if (opcusr == 1){
                //Esto debe ser el folio, pero esta agregado asi por temas de testeo
                const int id_Usuario = leerIntSeguro(10,10,10000,"Ingrese Id Usuario: ");
                RETURN_IF_ESC(id_Usuario);
                if(obtenerUsuarioById(id_Usuario) == NULL)return -1;
                mvprintw(12, 10, "                                                 ");
                //Generar numero de servicio
                // Ingresar material
                const char* material = leerStringSeguro(12,10,30,"Ingrese material del motor");
                if (material == NULL) {
                    return -1;
                }
                mvprintw(14, 10, "                                                 ");
                // Ingresar desgaste
                const float desgaste = leerFloatSeguro(14, 10, 30,"Ingresar desgaste");
                mvprintw(16, 10, "                                                 ");
                // Ingresar tolerancia
                const float tolerancia = leerFloatSeguro(16, 10, 100, "Ingrese tolerancia");
                mvprintw(18, 10, "                                                 ");
                // Ingresar medidaOriginal
                const float medidaOriginal = leerFloatSeguro(18, 10, 100,"Ingrese medida Original");
                mvprintw(20, 10, "                                                 ");
                // Ingresar medidaActual
                const float medidaActual = leerFloatSeguro(20, 10, 100,"Ingrese Medida Actual");
                mvprintw(22, 10, "                                                 ");
                // comprobar necesitaRectificacion
                //Funcion necesita rectificacion
                // Ingresar numValvulas
                const int numValvulas = leerIntSeguro(22, 10, 50,"Ingrese numero Valvulas");
                mvprintw(24, 10, "                                                 ");
                // Ingresar presionPrueba
                const float presionPrueba = leerFloatSeguro(24, 10, 20,"Ingrese PresionPrueba");
                mvprintw(26, 10, "                                                 ");
                // Ingresar tipoCombustible
                tipo_combustible = mostrarMenu(6,"Ingrese tipo de combustible");

                const int tieneFisuras = mostrarMenu(7,"¿Tiene Fisuras?");

                const int rectificacion = mostrarMenu(7,"¿Necesita Rectificación?");
                // Ahora puedes usar buffer como un char*
                mvprintw(3, 55, "Rectificacion?: %d", rectificacion);
                mvprintw(4, 55, "Tiene Fisuras?: %d", tieneFisuras);
                mvprintw(5, 55, "Tipo Combustible: %d", tipo_combustible);
                const Pieza piezaUsuario = inicializarPieza(id_Usuario, 1, material, desgaste, tolerancia, medidaOriginal, medidaActual, rectificacion);
                //Polimorfismo
                    Culata* pzc = inicializarCulata(piezaUsuario, numValvulas, presionPrueba, tipo_combustible, tieneFisuras);
                    guardarPiezaArray((void*)pzc);  // Se guarda como puntero genérico

                    Usuario* usuario = obtenerUsuarioById(id_Usuario);
                    asignarPiezaUsuario(usuario, pzc);
                mvprintw(8, 55, "Pieza Guardada Correctamente");
                getch();
            }else if (opcusr == 2){
                mvprintw(10,10,"Opcion Monoblock");
            }else if (opcusr == 3){
                listarPiezas();
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
    const int opcUsr = mostrarMenu(8, ".");
    RETURN_IF_ESC(opcUsr);
    switch (opcUsr){
    case 1:
        //const int opcUsrInventario = mostrarMenu(9,".");
        break;
    case 2:
        //const int opcUsrControl = mostrarMenu(10,".");
        break;
    case 3:
        //const int opcUsrHerramientas = mostrarMenu(11,".");
        break;
    case 4:
        //const int opcUsrProveedores = mostrarMenu(12,".");
        break;
    case 5:
        //const int opcUsrReportes = mostrarMenu(13,".");
        break;
    default:

        break;
    }
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

int asignarPiezaUsuario(Usuario* usuario, void* pieza){
    if (usuario == NULL || usuario->activo != 1){
        mvprintw(10,10,"Usuario invalido o no encontrado");
        getch();
        return 0;
    }
    usuario->pieza = pieza;
    return 1;
};


void testing(int encendido) {
    if (encendido) {
        //usleep(200);
        printf("\n------TESTING MODE ON------");
        agregarUsuarios();
        agregarPiezas();
    }
}

void agregarUsuarios() {
    const Usuario usuario1 = inicializarUsuario(0,"00001", "Usuario1", "Apellido 1", 1234567890, "EmailPrueba1@1", "Contacto1");
    guardarUsuarioArray(usuario1);
    const Usuario usuario2 = inicializarUsuario(1,"00002", "Usuario2", "Apellido 2", 1987654321, "EmailPrueba2@2", "Contacto2");
    guardarUsuarioArray(usuario2);
}

void agregarPiezas() {
    Pieza piezaUsuario = inicializarPieza(0, 1, "Metal", .1123f, .1125f, .1300f, .1180f, 0);
    piezaUsuario.tipo = CULATA;
    Culata* pzc = inicializarCulata(piezaUsuario, 16, .10, 2,1);
    guardarPiezaArray((void*)pzc);  // Se guarda como puntero genérico
    Usuario* usuario1 = obtenerUsuarioById(0);
    asignarPiezaUsuario(usuario1, (void*)pzc);

    Pieza piezaUsuario2 = inicializarPieza(1, 2, "Aluminio", 0.1000f, 0.1050f, 0.1250f, 0.1150f, 1);
    piezaUsuario2.tipo = CULATA;
    Culata* pzc2 = inicializarCulata(piezaUsuario2, 18, 0.12, 1, 0);
    guardarPiezaArray((void*)pzc2);

    Usuario* usuario2 = obtenerUsuarioById(1);
    asignarPiezaUsuario(usuario2, pzc2);
}