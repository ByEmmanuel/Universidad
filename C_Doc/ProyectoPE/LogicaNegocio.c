//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>

#include "UsuarioDTO.h"
#include "Util.h"
#include "UserInterface.h"
#include "LogicaNegocio.h"

#include <time.h>

#include "SystemLogs.h"
#include "Testing.h"

int servicio() {
    int opc = mostrarMenu(4, " ");
    RETURN_IF_ESC(opc);
    int opcusrParteMotor;

    switch (opc) {
        case 0:
            clear();
            registrarMotor();
            break;

        case 1:
            //Registrar Culata
            clear();
            opcusrParteMotor = mostrarMenu(5, " ");
            RETURN_IF_ESC(opcusrParteMotor);
            listarFoliosUsuarios();

            if (opcusrParteMotor == 0 && registrarCulata() != 1)
                imprimirMensaje(10, 10, "¡Error al crear piezas (Culata) o no hay motor previo!");
            else if (opcusrParteMotor == 1)
                registrarMonoblock();
            else if (opcusrParteMotor == 2)
                listarPiezas();
            break;

        case 2: {
                //LogicaNegocio
            realizarOperacionesMotor();
            }
        break;
        case 3:
            //Testing
            listarMotoresPrecargados();
            break;

        default:
            break;
    }

    return 0;
}
int opcUsr = -2;
int subOpcUsr = -2;
int almacen(){
    /*
8     "Inventario General / Stock","Herramientas y Equipos","Proveedores y Compras","Reportes"};
|
v
(0) 9     "Ver piezas", "Buscar / Filtrar","Agregar / Editar / Eliminar"};
(1) 10    "Entradas / Salidas","Alertas de stock mínimo","Historial de movimientos"};
(2) 11    "Estado de herramientas", "Registro de mantenimiento","Asignación"};
(3) 12    "Registro de proveedor","Historial de compras","Pedidos pendientes"};
(4) 13    "Movimientos","Piezas más usadas","Piezas inactivas"};
     */
    opcUsr = mostrarMenu(8, " ");
    RETURN_IF_ESC(opcUsr);
    switch (opcUsr){
    case 0:
        subOpcUsr = mostrarMenu(9," ");
        RETURN_IF_ESC(subOpcUsr);
        ejecutarOpcionAlmacen(opcUsr,subOpcUsr);
        break;
    case 1:
        subOpcUsr = mostrarMenu(10," ");
        RETURN_IF_ESC(subOpcUsr);
        break;
    case 2:
        subOpcUsr = mostrarMenu(11," ");
        RETURN_IF_ESC(subOpcUsr);
        break;
    case 3:
        subOpcUsr = mostrarMenu(12," ");
        RETURN_IF_ESC(subOpcUsr);
        break;
    case 4:
        subOpcUsr = mostrarMenu(13," ");
        RETURN_IF_ESC(subOpcUsr);
        break;
    default:
        break;
    }
    return 0;
}
/**
*
* Otros {"Reportar Bug", "Solicitar Mejora", "Ver Historial de tickets", "Limpieza de cache - Reinicio local del sistema", "Enviar Logs del sistema", "Salir"};
    //Dudas
    {"Consulta Tecnica", "Consultar Version", "Manual de usuario", "Documentacion", "Salir"};
 */

int otro(){
    int opcUsr = mostrarMenu(16, " ");
    switch (opcUsr) {
        case 0:
            imprimirMensaje(10,10,"Reportar Bug");
            //reportarBug();
            break;
        case 1:
            imprimirMensaje(10,10,"Solicitar Mejora");
            //solicitarFeature();
            break;
        case 2:
            imprimirMensaje(10,10,"Ver Historial de tickets");
            //Buscar ticket por ID
            //Lo ideal seria imprimir todos los tickets porque ya puedo impimir un ticket individual por usuario
            if (mostrarMenu(7, "Estas apunto de generar un archivo con todos los tickets del dia, ¿Deseas generarlo?")) {
                historialTickets();
            }
        break;
        case 3:
            imprimirMensaje(10,10,"Limpieza de cache - Reinicio local del sistema");
            //limpiezaCache();
        break;
        case 4:
            imprimirMensaje(10,10,"Enviar Logs del sistema");

            char* nombreArchivo = obtenerNombreArchivo("Logs-Sistema");

            FILE* archivo = fopen(nombreArchivo,"w");

            enviarLogsSistema(nombreArchivo, archivo);

            fclose(archivo);
        break;
        case 5:
            if (mostrarMenu(7,"Estas apunto de generar un archivo con todos los detalles del sistema, ¿Deseas Generarlo?")){
                exportarDetallesTodoElSistema();
            }
        break;
        case 6:
            //imprimirMensaje(10,10,"Salir");
                return -1;
        default: break;
    }
    return 0;
}
//Dudas
// {"Consulta Tecnica", "Consultar Version", "Manual de usuario", "Documentacion", "Salir"};
int dudas(){
    int opcUsr = mostrarMenu(17, " ");
    switch (opcUsr) {
        case 0:
            imprimirMensaje(10,10,"Consulta Tecnica");
            //consultaTecnica();
        break;
        case 1:
            imprimirMensaje(10,10,"Consultar Version");
            //imprimirVersion(versionSoftware);
        break;
        case 2:
            imprimirMensaje(10,10,"Manual de usuario");
            //manualUsuario();
        break;
        case 3:
            imprimirMensaje(10,10,"Documentacion");
            //documentacion();-> Redireccionamiento al navegador
        break;
        case 4:
            return -1;
        default: break;
    }
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

char* imprimirOperacionesCulata(int estado) {
    const char* mensajes[7] = {
        "Montado inicial", "Desmontado", "Lavado inicial", "Rectificación/Reconstrucción",
        "Pruebas Unitarias", "Lavado posterior", "Montado final"
    };

    if (estado < 0 || estado > 6) {
        return strdup("Ocurrió un error al obtener el estado de la pieza - Ve al siguiente apartado");
    }

    const char* base = "El estado actual de la culata es: ";
    const char* adicional = " - Ve al siguiente apartado";

    size_t tam = strlen(base) + strlen(mensajes[estado]) + strlen(adicional) + 1;

    char* resultado = (char*)malloc(tam);
    if (!resultado) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(resultado, base);
    strcat(resultado, mensajes[estado]);
    strcat(resultado, adicional);

    return resultado;
}
int realizarOperacionesMotor(){
    clear();
    int id_usuario = obtenerIdSiExisteUsuario(5, 5);
    RETURN_IF_ESC(id_usuario);

    Motor* motor_usr = obtenerMotorByIdUsuario(id_usuario);
    if (motor_usr == NULL || motor_usr->culata == NULL){
        imprimirMensaje(10, 10, "Motor inválido o sin culata");
        return -1;
    }

    int* estado = &motor_usr->culata->estadoTemporalPieza;
    int operacionesLogicas = motor_usr->culata->operacionesMotor;
    if (motor_usr->culata->estadoTemporalPieza < 0 || motor_usr->culata->estadoTemporalPieza > 5)
        motor_usr->culata->estadoTemporalPieza = 0;

    const char* mensajes[] = {
        "Desmontando pieza", "Lavando Pieza",
        (operacionesLogicas == -1) ? "Rectificando Culata" : "Reconstruyendo Culata",
        "Haciendo Pruebas unitarias", "Haciendo una lavada final",
        "Montando motor"
    };
    //TIEMPOS DE CARGA EN LAS OPERACIONES DEL MOTOR
    const int tiempos_test[] = {5, 6, (operacionesLogicas == -1) ? 5 : 6, 5, 5, 5};
    const int tiempos_default[] = {50, 25, (operacionesLogicas == -1) ? 80 : 70, 10, 30, 50};

    const int* tiempos = (testingMode >= 1) ? tiempos_test : tiempos_default;

    //
    while (1){
        int opcUsr = mostrarMenu(15, "Seleccione operación a realizar");
        RETURN_IF_ESC(opcUsr);
        if (opcUsr == 6) return -1;
        if (opcUsr < 0 || opcUsr > 5) continue;

        if (opcUsr == *estado && *estado < 6){
            imprimirBarraDeCarga(tiempos[opcUsr], mensajes[opcUsr]);
            (*estado)++;
            if (opcUsr == 2)
                motor_usr->culata->operacionesMotor = (operacionesLogicas == -1) ? 1 : 2;
        }
        else if (opcUsr < *estado){
            imprimirMensaje(10, 10, "Operación ya realizada.");
        }
        else{
            clear();
            mvprintw(20, 20, "Estado de la pieza %s: ", imprimirOperacionesCulata(*estado));
            getch();
        }

        if (motor_usr->culata->estadoTemporalPieza > 5){
            imprimirTextoMultilinea(10, 10,
                                    "El motor ya no tiene operaciones por realizar, puedes ir a generar las ordenes de pago",
                                    50);
            break;
        }
    }
    return 0;
}
