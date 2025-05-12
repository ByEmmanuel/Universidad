//
// Created by pollofeliz on 12/05/25.
//

#ifndef ALMACENYOTROS_H
#define ALMACENYOTROS_H

typedef enum {
    INFO,
    WARN,
    ERROR,
    CRITICAL
} NivelSeveridad;


typedef struct {
    int id_unico;
    char fecha[50]; // Arreglo estático en lugar de char*
    int usuario_id;
    char accion[50];
    char objeto[50];
    char id_objeto[50];
    NivelSeveridad nivel_severidad;
    char ip_origen[20];
    char origen_modulo[50];
    int exito;
    char* codigo_error; // Único campo dinámico
} SystemLogs;


// Array de logs
typedef struct {
   SystemLogs* datos; // Datos del sistema
    int tamanno;    // tamanno actual de datos que hay en el array
    int capacidad;  // tammano de la capacidad total del array disponible
}ArrayLogs;


void agregarSystemLog(int usuario_id, char* accion, char* objetoAfectado, char* id_objeto, NivelSeveridad nivelSeveridad,
    int exito, char* origenModulo, char* ip_origen, char* codigoError);
SystemLogs inicializarLogs(char* fecha, int log_id, char* accion, char* objeto, char* id_objeto,
                      NivelSeveridad severidad, int exito, char* modulo, char* ip, char* codigoError);

int guardarSystemLogs(SystemLogs log);



extern ArrayLogs arrayLogs;




#endif //ALMACENYOTROS_H
