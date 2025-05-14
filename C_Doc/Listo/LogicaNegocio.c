//LogicaNegocio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>

#include "../ProyectoPE/UsuarioDTO.h"
#include "../ProyectoPE/Util.h"
#include "../ProyectoPE/UserInterface.h"
#include "../ProyectoPE/LogicaNegocio.h"

#include <time.h>

#include "../ProyectoPE/SystemLogs.h"
#include "../ProyectoPE/Testing.h"

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

            clear();
            opcusrParteMotor = mostrarMenu(5, " ");
            RETURN_IF_ESC(opcusrParteMotor);
            listarFoliosUsuarios();

            if (opcusrParteMotor == 0 && registrarCulata() != 1)
                imprimirMensaje(10, 10, "¡Error al crear piezas (Culata) o no hay motor previo!");
            else if (opcusrParteMotor == 1)
                registrarMonoblock();

            break;

        case 2: {
            realizarOperacionesMotor();
        }
        break;
        case 3:

            listarMotoresPrecargados();
            break;

        default:
            break;
    }

    return 0;
}

int opcUsr = -2;
int subOpcUsr = -2;

int almacen() {
    opcUsr = mostrarMenu(8, " ");
    RETURN_IF_ESC(opcUsr);
    switch (opcUsr) {
        case 0:
            subOpcUsr = mostrarMenu(9, " ");
            RETURN_IF_ESC(subOpcUsr);
            ejecutarOpcionAlmacen(opcUsr, subOpcUsr);
            break;
        case 1:
            subOpcUsr = mostrarMenu(10, " ");
            RETURN_IF_ESC(subOpcUsr);
            break;
        case 2:
            subOpcUsr = mostrarMenu(11, " ");
            RETURN_IF_ESC(subOpcUsr);
            break;
        case 3:
            subOpcUsr = mostrarMenu(12, " ");
            RETURN_IF_ESC(subOpcUsr);
            break;
        case 4:
            subOpcUsr = mostrarMenu(13, " ");
            RETURN_IF_ESC(subOpcUsr);
            break;
        default:
            break;
    }
    return 0;
}

int otro() {
    int opcUsr = mostrarMenu(16, " ");
    switch (opcUsr) {
        case 0:
            imprimirMensaje(10, 10, "Reportar Bug");

            break;
        case 1:
            listarPiezas();
            break;
        case 2:
            imprimirMensaje(10, 10, "Ver Historial de tickets");


            if (mostrarMenu(
                7, "Estas apunto de generar un archivo con todos los tickets del dia, ¿Deseas generarlo?")) {
                historialTickets();
            }
            break;
        case 3:
            imprimirMensaje(10, 10, "Limpieza de cache - Reinicio local del sistema");

            break;
        case 4:
            imprimirMensaje(10, 10, "Enviar Logs del sistema");

            char *nombreArchivo = obtenerNombreArchivo("Logs-Sistema");

            FILE *archivo = fopen(nombreArchivo, "w");

            enviarLogsSistema(nombreArchivo, archivo);

            fclose(archivo);
            break;
        case 5:
            if (mostrarMenu(
                7, "Estas apunto de generar un archivo con todos los detalles del sistema, ¿Deseas Generarlo?")) {
                exportarDetallesTodoElSistema();
            }
            break;
        case 6:

            return -1;
        default: break;
    }
    return 0;
}


int dudas() {
    int opcUsr = mostrarMenu(17, " ");
    switch (opcUsr) {
        case 0:
            imprimirMensaje(10, 10, "Consulta Tecnica");

            break;
        case 1:
            imprimirMensaje(10, 10, "Consultar Version");

            break;
        case 2:
            imprimirMensaje(10, 10, "Manual de usuario");

            break;
        case 3:
            imprimirMensaje(10, 10, "Documentacion");

            break;
        case 4:
            return -1;
        default: break;
    }
    return 0;
}

int salir() {
    listarPiezas();
    exit(0);
}

void mostrarLogo() {
    printf("\nBienvenido al sistema\n");

    printf("    ____           __ \n");

    printf("   / __/__    ____/ /___  _________ \n");

    printf("  / /_/ _ \\ / __  / __ / ___/ __ /\n");

    printf(" / __/  __/ /_/ / /_/ / /  / /_/ / \n");

    printf("/_/  \\___/\\__,_/\\____/_/   \\__,_/  \n");

    printf("      /\\     \n");
    printf("     /  \\    \n");
    printf("    /    \\    \n");
}

int asignarMotorUsuario(Usuario *usuario, Motor *motor) {
    if (usuario == NULL || usuario->activo != 1) {
        imprimirMensaje(10, 10, "Usuario invalido o no encontrado");
        return 0;
    }
    if (usuario->motor != NULL) {
        imprimirMensaje(10, 10, "La pieza ya fue asignada anteriormente");
        return 0;
    }
    if (motor != NULL) usuario->motor = motor;
    return 1;
};

int asignarPiezaMotor(Usuario *usuario, void *pieza, int tipoDePieza) {
    if (tipoDePieza == 1) {
        usuario->motor->culata = (Culata *) pieza;
        return 1;
    }
    if (tipoDePieza == 2) {
        usuario->motor->monoblock = (Monoblock *) pieza;
        return 1;
    }
    return 0;
};


int evaluarEstadoCulata(const float alturaOriginal, const float alturaActual, const float alturaMinima,
                        const float tolerancia) {
    const float desgaste = alturaOriginal - alturaActual;

    if (alturaActual >= alturaMinima && desgaste <= tolerancia) {
        return -1;
    }
    if (alturaActual < alturaMinima) {
        return -2;
    }
    return 0;
}

const char *imprimirOperacionesEstadoPieza(int estado, int tipoPieza) {
    const char *mensajes[7] = {
        "Montado inicial", "Desmontado", "Lavado inicial", "Rectificación/Reconstrucción",
        "Pruebas Unitarias", "Lavado posterior", "Montado final"
    };

    if (estado < 0 || estado > 6) {
        return strdup("Ocurrió un error al obtener el estado de la pieza - Ve al siguiente apartado");
    }
    char *base = tipoPieza == 0 ? "El estado actual de la culata es: " : "El estado actual de la pieza es: ";
    const char *adicional = " - Ve al siguiente apartado";

    size_t tam = strlen(base) + strlen(mensajes[estado]) + strlen(adicional) + 1;

    char *resultado = (char *) malloc(tam);
    if (!resultado) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(resultado, base);
    strcat(resultado, mensajes[estado]);
    strcat(resultado, adicional);

    return resultado;
}

int realizarOperacionesMotor() {
    if (mostrarMenu(5, "Seleccione la parte que se Trabajara") == 0) {
        realizarOperacionesPiezaMotor(0);
    } else {
        realizarOperacionesPiezaMotor(1);
    }
    return 0;
}


int realizarOperacionesPiezaMotor(int tipoPieza) {
    int id_usuario = obtenerIdSiExisteUsuario(5, 5);
    RETURN_IF_ESC(id_usuario);

    const int tiempos_test[] = {5, 6, 6, 5, 5, 5};
    const int tiempos_default[] = {50, 25, 70, 10, 30, 50};
    const int *tiempos = (testingMode >= 1) ? tiempos_test : tiempos_default;

    Motor *motor_usr = obtenerMotorByIdUsuario(id_usuario);
    if (motor_usr == NULL) {
        imprimirMensaje(10, 10, "No hay un motor asociado al ID propocionado");
        return -1;
    }

    if (tipoPieza == 0) {
        clear();
        mvprintw(0, 0, "Operaciones culata");

        if (motor_usr->culata == NULL) {
            imprimirMensaje(10, 10, "Motor inválido o sin culata");
            return -1;
        }

        int *estado = &motor_usr->culata->estadoTemporalPieza;
        int operacionesLogicas = motor_usr->culata->operacionesMotor;
        if (motor_usr->culata->estadoTemporalPieza < 0 || motor_usr->culata->estadoTemporalPieza > 5)
            motor_usr->culata->estadoTemporalPieza = 0;
        const char *mensajes[] = {
            "Desmontando pieza", "Lavando Pieza",
            (operacionesLogicas == -1) ? "Rectificando Culata" : "Reconstruyendo Culata",
            "Haciendo Pruebas unitarias", "Haciendo una lavada final",
            "Montando motor"
        };
        while (1) {
            int opcUsr = mostrarMenu(15, "Seleccione operación a realizar");
            RETURN_IF_ESC(opcUsr);
            if (opcUsr == 6) return -1;
            if (opcUsr < 0 || opcUsr > 5) continue;

            if (opcUsr == *estado && *estado < 6) {
                imprimirBarraDeCarga(tiempos[opcUsr], mensajes[opcUsr]);
                (*estado)++;
                if (opcUsr == 2)
                    motor_usr->culata->operacionesMotor = (operacionesLogicas == -1) ? 1 : 2;
            } else if (opcUsr < *estado) {
                imprimirMensaje(10, 10, "Operación ya realizada.");
            } else {
                clear();
                mvprintw(20, 20, "Estado de la pieza %s: ", imprimirOperacionesEstadoPieza(*estado, 0));
                getch();
            }

            if (motor_usr->culata->estadoTemporalPieza > 5) {
                imprimirTextoMultilinea(10, 10,
                                        "El motor ya no tiene operaciones por realizar, puedes ir a generar las ordenes de pago",
                                        50);
                break;
            }
            generarSystemLog(id_usuario, "Operaciones Culata", "Culata", motor_usr->numeroSerie, INFO, 1,
                             "LogicaNegocio.c", "RealizarOperacionesPiezaMotor", HTTP_ACCEPTED);
        }
    } else if (tipoPieza == 1) {
        clear();
        mvprintw(0, 0, "Operaciones Monoblock");
        if (motor_usr->monoblock == NULL) {
            imprimirMensaje(10, 10, "Motor inválido o sin Monoblock");
            return -1;
        }
        int *estado = &motor_usr->monoblock->estadoTemporalPieza;
        int operacionesLogicas = motor_usr->monoblock->operacionesMotor;
        if (motor_usr->monoblock->estadoTemporalPieza < 0 || motor_usr->monoblock->estadoTemporalPieza > 5)
            motor_usr->monoblock->estadoTemporalPieza = 0;
        const char *mensajes[] = {
            "Desmontando Monoblock", "Lavando Pieza",
            (operacionesLogicas == -1) ? "Rectificando Monoblock" : "Reconstruyendo Monoblock",
            "Haciendo Pruebas unitarias", "Haciendo una lavada final",
            "Montando Monoblock"
        };
        while (1) {
            int opcUsr = mostrarMenu(15, "Seleccione operación a realizar");
            RETURN_IF_ESC(opcUsr);
            if (opcUsr == 6) return -1;
            if (opcUsr < 0 || opcUsr > 5) continue;

            if (opcUsr == *estado && *estado < 6) {
                imprimirBarraDeCarga(tiempos[opcUsr], mensajes[opcUsr]);
                (*estado)++;
                if (opcUsr == 2)
                    motor_usr->monoblock->operacionesMotor = (operacionesLogicas == -1) ? 1 : 2;
            } else if (opcUsr < *estado) {
                imprimirMensaje(10, 10, "Operación ya realizada.");
            } else {
                clear();
                mvprintw(20, 20, "Estado de la pieza %s: ", imprimirOperacionesEstadoPieza(*estado, 1));
                getch();
            }

            if (motor_usr->monoblock->estadoTemporalPieza > 5) {
                imprimirTextoMultilinea(10, 10,
                                        "Monoblock ya no tiene operaciones por realizar, puedes ir a generar las ordenes de pago",
                                        50);
                break;
            }
            generarSystemLog(id_usuario, "Operaciones Monoblock", "Monoblock", motor_usr->numeroSerie, INFO, 1,
                             "LogicaNegocio.c", "RealizarOperacionesPiezaMotor", HTTP_ACCEPTED);
        }
    }
    return 0;
};
