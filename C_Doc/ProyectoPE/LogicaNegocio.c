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

#include "ConstantesMotores.h"
#include "Testing.h"

#define MAX_USUARIOS 6
#define MAX_LONGITUD 50

char usuariosRegistrados[MAX_USUARIOS][MAX_LONGITUD] =  {"David","Jose","Admin","Pepe","Luis",""};
char contraseñasUsuarios[MAX_USUARIOS][MAX_LONGITUD] = {"123456789","987654321","01","24680",""};
char* empleado;


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
                empleado = usuarioID;
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
//Aqui iría va la funcion cliente pero esta puesta en DTO USUARIO

int servicio(){
    //Varibales locales
    // Material de la pieza (Hierro, Aluminio, etc.)
    // Nivel de desgaste en porcentaje (0-100%)
    // Tolerancia máxima de desgaste permitida antes de rectificar
    // Medida original de la pieza en mm
    // Medida actual después del desgaste
    //TipoCombustible tipo_combustible = {};
    /**
    char* menuCuatro[SIZE_SEIS] = {"Ingreso datos motor", "Medidas", "Lavado",  "Rectificar", "Ensamble", "Salir"};
    char* menuCinco[SIZE_TRES] = {"CULATA", "MONOBLOCK", "Listar Piezas"};
    */

    int opc = mostrarMenu(4," ");
    RETURN_IF_ESC(opc);
    int opcusrParteMotor;
    switch (opc){
        case 0:{
                clear();
                registrarMotor();
                break;
            }
        case 1:
            //Ingreso culata o monoblock
            clear();
            opcusrParteMotor = mostrarMenu(5," ");
            RETURN_IF_ESC(opcusrParteMotor);
            listarFoliosUsuarios();
            if (opcusrParteMotor == 0){
                if (registrarCulata() != 1){
                    imprimirMensaje(10,10,"¡Hubo un error al crear las piezas -> Culata o No existe un motor previo!");
                }
                return -1;
            }
            if (opcusrParteMotor == 1){
                registrarMonoblock();
                //imprimirMensaje(10,10,"Opcion Monoblock");
            }else if (opcusrParteMotor == 2){
                listarPiezas();
            }
            //printf("Opcion no valida");

            break;
        case 2:{

                /*    Operaciones Realizadas con el motor
                 *  0 : No se han realizado operaciones con el motor
                 *  1 : Desmote del motor
                 *  2 : Lavado inicial
                 *  3 : Rectificacion o Reconstruccion
                 *  4 : Lavado final
                 *  5 : Pruebas Unitarias
                 *  6 : Montado del motor
                 */

                //Operaciones
                /**
                 * Si culata,operacionesMotor == -1 -> Rectificacion
                 * Si culata,operacionesMotor == -2 -> Reconstruccion
                 */
                int bandera = 1;
                int id_usuario = obtenerIdSiExisteUsuario(10,10);
                /*
                ≈ char* numeroSerieMotor = leerStringSeguro(10,10,30,"Ingrese numero de serie motor");
                RETURN_IF_ESC(numeroSerieMotor);
                Motor* motor = obtenerMotorPorNumeroDeSerie(numeroSerieMotor);
                 */
                RETURN_IF_ESC(id_usuario);
                Motor* motor_usr = obtenerMotorByIdUsuario(id_usuario);
                if (motor_usr == NULL || motor_usr->culata == NULL) {
                    imprimirMensaje(10, 10, "El motor no pertenece a ese ID o el motor no tiene culata");
                    return -1;
                }
                clear();
                mvprintw(20,20,"Estado de la pieza %d: ", motor_usr->culata->operacionesMotor);
                getch();
                int operacionesLogicas = motor_usr->culata->operacionesMotor;
                // cada vez que entro a esta funcion, se reinicia el "trabajo"
                motor_usr->culata->estadoTemporalPieza = 0;
                while (bandera == 1){
                    //Desmontado", "Lavado Inicial", "Rectificacion", "Pruebas Unitarias", "Lavado Secundario", "Montar Motor", "Salir"
                    imprimirOperacionesCulata(motor_usr->culata->operacionesMotor);
                    int opcUsr = mostrarMenu(15,"Selecione operacion a realizar");
                    RETURN_IF_ESC(opcUsr);
                    switch (opcUsr){
                    case 0:
                        if (motor_usr->culata->estadoTemporalPieza == 0 ){
                            imprimirBarraDeCarga(50,"Desmontando pieza");
                            //Solo se hace una vez
                            motor_usr->culata->estadoTemporalPieza++;
                            break;
                        }
                        if (motor_usr->culata->estadoTemporalPieza >= 1){
                            imprimirMensaje(10,10,"Esta pieza ya fue Desmontada");
                            break;
                        }
                        imprimirMensaje(10,10,"Esta opcion ya fue hecha");
                        break;
                    case 1:
                        if (motor_usr->culata->estadoTemporalPieza == 1){
                            imprimirBarraDeCarga(25,"Lavando Pieza");
                            //Solo se hace una vez
                            motor_usr->culata->estadoTemporalPieza++;
                            break;
                        }if (motor_usr->culata->estadoTemporalPieza >= 2){
                            imprimirMensaje(10,10,"Esta pieza ya fue Lavada");
                            break;
                        }
                        break;
                    case 2:
                        /**
                        * Si culata,operacionesMotor == -1 -> Rectificacion
                        * Si culata,operacionesMotor == -2 -> Reconstruccion
                        */
                        if (motor_usr->culata->estadoTemporalPieza == 2 && operacionesLogicas == -1){
                            imprimirBarraDeCarga(80,"Rectificando Culata");
                            motor_usr->culata->estadoTemporalPieza++;
                            motor_usr->culata->operacionesMotor = 1;
                            break;
                        }
                        if (motor_usr->culata->estadoTemporalPieza == 2 && operacionesLogicas == -2){
                            imprimirBarraDeCarga(70,"Reconstruyendo Culata");
                            motor_usr->culata->estadoTemporalPieza++;
                            motor_usr->culata->operacionesMotor = 2;
                            break;
                        }if (motor_usr->culata->estadoTemporalPieza >=3){
                            imprimirMensaje(10,10,"Esta pieza ya fue Rectificada / Reconstruida");
                            break;
                        }
                        break;
                    case 3:
                        if (motor_usr->culata->estadoTemporalPieza == 3){
                            imprimirBarraDeCarga(30,"Haciendo una lavada final ");
                            motor_usr->culata->estadoTemporalPieza++;
                            break;
                        }
                        if (motor_usr->culata->estadoTemporalPieza >=4){
                            imprimirMensaje(10,10,"Esta pieza ya fue lavada anteriormente");
                            break;
                        }
                        break;
                    case 4:
                        if (motor_usr->culata->estadoTemporalPieza == 4){
                            imprimirBarraDeCarga(50,"Haciendo Pruebas unitarias");
                            motor_usr->culata->estadoTemporalPieza++;
                            break;
                        }
                        if (motor_usr->culata->estadoTemporalPieza >=5){
                            imprimirMensaje(10,10,"A Esta pieza ya se le hicieron las pruebas unitarias");
                            break;
                        }
                        break;
                    case 5:
                        if (motor_usr->culata->estadoTemporalPieza == 5){
                            imprimirBarraDeCarga(50,"Volviendo a hacer el montaje del motor...");
                            motor_usr->culata->estadoTemporalPieza++;
                            break;
                        }
                        if (motor_usr->culata->estadoTemporalPieza >=6){
                            imprimirMensaje(10,10,"El trabajo de esta pieza ya fue hecho por completo");
                            break;
                        }
                        break;
                    case 6:
                        return -1;
                    default: break;
                    }
                    if (motor_usr->culata->operacionesMotor == 6){
                        imprimirTextoMultilinea(10,10,"El motor ya no tiene operaciones por realizar, puedes ir a generar las ordenes de pago",50);
                        //return -1;
                    }
                }

            }
            break;
/**
 *

                        clear();
        if (mostrarMenu(7, "¿Desea agregar el lavado a su servicio?") == 0) return -1;
        clear();
        int id_usuario = obtenerIdSiExisteUsuario(10,10);
        RETURN_IF_ESC(id_usuario);
        Ticket* ticket = obtenerTicketByIdUsuario(id_usuario);
        ticket->lavado = 1;
        clear();
        //barraDeCarga(/*Tiempo en ms* 8000)
        mvprintw(10,10,"El motor y el carro fueron lavados!     Presione Enter");
        getch();
        */
        case 3:{
                listarMotoresPrecargados();
                /*
                 //Rectificar
                clear();
                int id_usuario = obtenerIdSiExisteUsuario(10,10);
                Motor* motorUsr = obtenerMotorByIdUsuario(id_usuario);
                if (motorUsr != NULL && motorUsr->culata != NULL){
                    rectificarCulata(motorUsr->culata, id_usuario);
                    imprimirBarraDeCarga(150,"Rectificando culata");
                }
                */
            }
            break;
        /*
         *case 4:
            //Ensamble

            break;
        case 5:
            listarMotoresPrecargados();
            break;
        case 6:
            //Menu Anterior
            break;
            */
    default:
        break;
    }
    //Ingresar manualmente que es lo que se quiere reconstruir
    // Cabeza o culata

    return 0;
}

int almacen(){
    const int opcUsr = mostrarMenu(8, " ") + 1;
    RETURN_IF_ESC(opcUsr);
    switch (opcUsr){
    case 1:
        //const int opcUsrInventario = mostrarMenu(9,".");
            clear();
            mvprintw(10,10,"Atiende: %s",empleado);
            getch();
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

int asignarMotorUsuario(Usuario* usuario, Motor* motor ){
    if (usuario == NULL || usuario->activo != 1){
        imprimirMensaje(10,10,"Usuario invalido o no encontrado");
        return 0;
    }
    if (usuario->motor != NULL){
        imprimirMensaje(10,10,"La pieza ya fue asignada anteriormente");
        return 0;
    }
    if (motor != NULL) usuario->motor = motor;
    return 1;
};
// 1 CULATA , 2  MONOBLOCK
int asignarPiezaMotor(Usuario* usuario, void* pieza, int tipoDePieza){
    if (tipoDePieza == 1){
        usuario->motor->culata = (Culata*)pieza;
        return 1;
    }
    if (tipoDePieza == 2){
        usuario->motor->monoblock = (Monoblock*)pieza;
        return 1;
    }
    return 0;
};

/**
 * Verifica si se debe rectificar o reconstruir una culata
 * Devuelve:
 * 0 = No intervención
 * 1 = Rectificación
 * 2 = Reconstrucción
 */

/**
 *RECTIFICACION
alturaOriginal = 130.0;
alturaActual   = 128.9;
alturaMinima   = 128.5;
tolerancia     = 1.5;
// desgaste = 1.1 → válido
 */

/**
 *RECONSTRUCCION
alturaOriginal = 130.0;
alturaActual   = 127.0;
alturaMinima   = 127.5;
tolerancia     = 2.0;
alturaActual < alturaMinima → reconstrucción
 */
int evaluarEstadoCulata(const float alturaOriginal, const float alturaActual, const float alturaMinima, const float tolerancia) {
    const float desgaste = alturaOriginal - alturaActual;

    if (alturaActual >= alturaMinima && desgaste <= tolerancia) {
        return -1; // Rectificación
    }
    if (alturaActual < alturaMinima) {
        return -2; // Reconstrucción
    }
    return 0; // No válido o error

}

void imprimirOperacionesCulata(int estado){
    switch (estado){
    case 1:
        mvprintw(50,30,"El estado actual de la culata es Desmontado");
        break;
    case 2:
        mvprintw(50,30,"El estado actual de la culata es Lavado incial");
        break;
    case 3:
        mvprintw(50,30,"El estado actual de la culata es Rectificacion/Reconstruccion");
        break;
    case 4:
        mvprintw(50,30,"El estado actual de la culata es Pruebas Unitarias");
        break;
    case 5:
        mvprintw(50,30,"El estado actual de la culata es Lavado Posterior");
        break;
    case 6:
        mvprintw(50,30,"El estado actual de la culata es Montado, la pieza ya no necesita mas operaciones");
        break;

        default: break;
    }
}