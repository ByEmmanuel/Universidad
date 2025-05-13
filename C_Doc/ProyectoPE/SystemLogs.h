//
// Created by Jesus Emmanuel Garcia on 5/12/25.
//

#ifndef SYSTEMLOGS_H
#define SYSTEMLOGS_H

#include <stdio.h>

typedef enum {
    INFO,
    WARN,
    ERROR,
    CRITICAL
} NivelSeveridad;

typedef enum {
    HTTP_OK = 200,
    HTTP_CREATED = 201,
    HTTP_ACCEPTED = 202,
    HTTP_NO_CONTENT = 204,
    HTTP_BAD_REQUEST = 400,
    HTTP_UNAUTHORIZED = 401,
    HTTP_FORBIDDEN = 403,
    HTTP_NOT_FOUND = 404,
    HTTP_CONFLICT = 409,
    HTTP_UNPROCESSABLE_ENTITY = 422,
    HTTP_INTERNAL_SERVER_ERROR = 500,
    HTTP_NOT_IMPLEMENTED = 501,
    HTTP_SERVICE_UNAVAILABLE = 503
} HttpStatusCode;

typedef struct {
    int id_unico;
    char fecha[50]; // Arreglo estático en lugar de char*
    int usuario_id;
    char accion[50];
    char objeto[50];
    char id_objeto[50];
    NivelSeveridad nivel_severidad;
    char nombreFuncion[30];
    char origen_modulo[50];
    int exito;
    HttpStatusCode codigoEstado;
} SystemLogs;


// Array de logs
typedef struct {
    SystemLogs* datos; // Datos del sistema
    int tamanno;    // tamanno actual de datos que hay en el array
    int capacidad;  // tammano de la capacidad total del array disponible
}ArrayLogs;


void agregarSystemLog(int usuario_id, char* accion, char* objeto, char* id_objeto,
                      NivelSeveridad severidad, int exito, char* modulo, char* nombreFuncion, HttpStatusCode codigoEstado);
SystemLogs inicializarLogs(char* fecha, int log_id, char* accion, char* objeto, char* id_objeto,
                      NivelSeveridad severidad, int exito, char* modulo, char* nombreFuncion, HttpStatusCode codigoEstado);

int guardarSystemLogs(SystemLogs log);



extern ArrayLogs arrayLogs;


//LOGS
const char* obtenerNombreSeveridad(NivelSeveridad severidad);
const char* obtenerMensajeHttp(HttpStatusCode code);
void enviarLogsSistema(char* nombreArchivo, FILE* archivo);

#endif //SYSTEMLOGS_H
