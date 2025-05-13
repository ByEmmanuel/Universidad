//
// Created by Jesus Emmanuel Garcia on 5/12/25.
//

#include "SystemLogs.h"
#include <stdio.h>
#include <time.h>
#include "Util.h"

#include <ctype.h>
#include <limits.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "UserInterface.h"
#include "LogicaNegocio.h"


//-----------------------------------------------------Logs

void enviarLogsSistema(char* nombreArchivo, FILE* archivo) {
    if (!archivo) {
        fprintf(stderr, "Error al abrir el archivo de logs: %s\n", nombreArchivo ? nombreArchivo : "NULL");
        return;
    }

    if (fprintf(archivo, "======= SISTEMA DE LOGS =======\n") < 0 ||
        fprintf(archivo, "Cantidad de registros: %d\n\n", arrayLogs.tamanno) < 0) {
        fprintf(stderr, "Error al escribir el encabezado en el archivo: %s\n", nombreArchivo);
        fclose(archivo);
        return;
    }

    for (int i = 0; i < arrayLogs.tamanno; i++) {
        const SystemLogs* log = &arrayLogs.datos[i];

        const char* fecha = log->fecha[0] ? log->fecha : "UNKNOWN";
        const char* modulo = log->origen_modulo[0] ? log->origen_modulo : "UNKNOWN";
        const char* objeto = log->objeto[0] ? log->objeto : "UNKNOWN";
        const char* id_objeto = log->id_objeto[0] ? log->id_objeto : "UNKNOWN";
        const char* accion = log->accion[0] ? log->accion : "UNKNOWN";
        const char* ip = log->nombreFuncion[0] ? log->nombreFuncion : "UNKNOWN";

        if (fprintf(archivo, "[%s] [%s] ID_LOG: %d | USUARIO_ID: %d | OBJETO: %s | ID_OBJETO: %s | SEVERIDAD: %s\n",
                    fecha, modulo, log->id_unico, log->usuario_id, objeto, id_objeto,
                    obtenerNombreSeveridad(log->nivel_severidad)) < 0) {
            fprintf(stderr, "Error al escribir log %d en el archivo: %s\n", log->id_unico, nombreArchivo);
            fclose(archivo);
            return;
        }

        if (fprintf(archivo, "└── ACCIÓN: %s | NAME_FUNC: %s | RESULTADO: %s | CÓDIGO: %d\n",
                    accion, ip, log->exito ? "ÉXITO" : "ERROR", log->codigoEstado) < 0) {
            fprintf(stderr, "Error al escribir detalles del log %d en el archivo: %s\n", log->id_unico, nombreArchivo);
            fclose(archivo);
            return;
        }

        fprintf(archivo, "\n");
    }
    printf("Logs escritos correctamente en el archivo: %s\n", nombreArchivo);
}

const char* obtenerNombreSeveridad(NivelSeveridad severidad) {
    switch (severidad) {
        case INFO: return "INFO";
        case WARN: return "WARNING";
        case ERROR: return "ERROR";
        default: return "DESCONOCIDO";
    }
}

const char* obtenerMensajeHttp(HttpStatusCode code) {
    switch (code) {
    case HTTP_OK: return "Éxito (200 OK)";
    case HTTP_CREATED: return "Recurso creado (201 Created)";
    case HTTP_ACCEPTED: return "Petición aceptada (202 Accepted)";
    case HTTP_NO_CONTENT: return "Sin contenido (204 No Content)";
    case HTTP_BAD_REQUEST: return "Solicitud incorrecta (400 Bad Request)";
    case HTTP_UNAUTHORIZED: return "No autorizado (401 Unauthorized)";
    case HTTP_FORBIDDEN: return "Prohibido (403 Forbidden)";
    case HTTP_NOT_FOUND: return "No encontrado (404 Not Found)";
    case HTTP_CONFLICT: return "Conflicto (409 Conflict)";
    case HTTP_UNPROCESSABLE_ENTITY: return "Entidad no procesable (422 Unprocessable Entity)";
    case HTTP_INTERNAL_SERVER_ERROR: return "Error interno (500 Internal Server Error)";
    case HTTP_NOT_IMPLEMENTED: return "No implementado (501 Not Implemented)";
    case HTTP_SERVICE_UNAVAILABLE: return "Servicio no disponible (503 Service Unavailable)";
    default: return "Código desconocido";
    }
}

void agregarSystemLog(int usuario_id, char* accion, char* objeto, char* id_objeto,
                      NivelSeveridad severidad, int exito, char* modulo, char* nombreFuncion,
                      HttpStatusCode codigoEstado) {
    char fecha[50];
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(fecha, sizeof(fecha), "%Y-%m-%d %H:%M:%S", tm_info);

    int log_id = getIdLog();
    setIdLog(log_id + 1); // Incrementar ID único

    SystemLogs log = inicializarLogs(fecha, log_id, accion, objeto, id_objeto, severidad, exito, modulo,
        nombreFuncion, codigoEstado);
    log.usuario_id = usuario_id;

    if (guardarSystemLogs(log) == -1) {
        mvprintw(5, 5, "Error al guardar el log. ID: %d, Acción: %s", log_id, accion);
        refresh();
        getch();
    }
}

SystemLogs inicializarLogs(char* fecha, int log_id, char* accion, char* objeto, char* id_objeto,
                           NivelSeveridad severidad, int exito, char* modulo, char* nombreFuncion,
                           HttpStatusCode codigoEstado) {
    SystemLogs log = {0};

    asignString(log.fecha, fecha, sizeof(log.fecha));
    asignString(log.accion, accion, sizeof(log.accion));
    log.usuario_id = 1; // Valor fijo, ajusta según necesidad
    log.id_unico = log_id;
    asignString(log.objeto, objeto, sizeof(log.objeto));
    asignString(log.id_objeto, id_objeto, sizeof(log.id_objeto));
    asignString(log.origen_modulo, modulo, sizeof(log.origen_modulo));
    log.nivel_severidad = severidad;
    log.exito = exito;
    asignString(log.nombreFuncion, nombreFuncion, sizeof(log.nombreFuncion));
    log.codigoEstado = codigoEstado;

    return log;
}

int guardarSystemLogs(SystemLogs log) {
    if (log.accion[0] == '\0') {
        return -1; // No se necesita liberar nada, todos los campos son estáticos
    }
    if (arrayLogs.tamanno >= arrayLogs.capacidad) {
        int nuevaCapacidad = arrayLogs.capacidad == 0 ? 1 : arrayLogs.capacidad * 2;
        SystemLogs* nuevoArray = realloc(arrayLogs.datos, nuevaCapacidad * sizeof(SystemLogs));
        if (nuevoArray == NULL) {
            fprintf(stderr, "Error al redimensionar el array de logs.\n");
            return -1;
        }
        arrayLogs.datos = nuevoArray;
        arrayLogs.capacidad = nuevaCapacidad;
    }

    arrayLogs.datos[arrayLogs.tamanno] = log;
    arrayLogs.tamanno++;

    return 1;
}