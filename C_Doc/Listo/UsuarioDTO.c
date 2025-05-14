//USuario DTO
#include "../ProyectoPE/UsuarioDTO.h"

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ProyectoPE/LogicaNegocio.h"
#include "../ProyectoPE/UserInterface.h"

#include "../ProyectoPE/SystemLogs.h"
#include "../ProyectoPE/Util.h"
int id_UsuarioGlobal = 0;
int id_piezaGlobal = 0;
int id_unicoLogs = 0;

ArrayUsuarios arrayUsuarios = {0};
ArrayTickets arrayTickets = {0};
ArrayList array_list;
ArrayPiezas arrayMotoresPrecargados = {0};
ArrayPiezas arrayMotoresUsuarios = {0};
ArrayPiezas arrayPiezas = {0};
ArrayPiezasAlmacen arrayPiezasAlmacen = {0};
Almacen almacenBaseDatos = {0};
ArrayLogs arrayLogs = {0};

Usuario inicializarUsuario(const int id_usuario, char *folio, const char *nombreUsuario, const char *apellido,
                           long long celular, const char *email, const char *contacto) {
    Usuario usr = {0};
    usr.id_usuario = id_usuario;
    asignString(usr.folio, folio, sizeof(usr.folio));
    asignString(usr.nombreUsuario, nombreUsuario, sizeof(usr.nombreUsuario));
    asignString(usr.apellido, apellido, sizeof(usr.apellido));
    usr.celular = celular;
    asignString(usr.email, email, sizeof(usr.email));
    asignString(usr.contacto, contacto, sizeof(usr.contacto));

    usr.motor = NULL;
    usr.activo = 1;
    setIdUsuarioLogico(getIdUsuarioLogico() + 1);

    generarSystemLog(id_usuario, "Inicializar Usuario", "Usuario", folio, INFO, 1,
                     "UsuarioDTO.c", "inicializarUsuario", HTTP_CREATED);

    return usr;
}


Motor *inicializarMotor(Paramsmotor params, const int id_usuario, const int id_pieza, void *tipoDePieza,
                        const int tipoPieza) {
    Motor *pz = (Motor *) malloc(sizeof(Motor));
    if (pz == NULL) {
        generarSystemLog(id_usuario, "Inicializar Motor", "Motor", params.numeroSerie, ERROR, 0,
                         "UsuarioDTO.c", "inicializarMotor", HTTP_INTERNAL_SERVER_ERROR);
        perror("Error al asignar memoria para Motor");
        exit(EXIT_FAILURE);
    }

    pz->id_usuario = id_usuario;
    pz->id_pieza = id_pieza;
    pz->tipoCombustible = params.tipoCombustible;
    asignString(pz->material, params.material, sizeof(pz->material));
    pz->modelo = params.modelo;
    pz->fabricante = params.fabricante;
    pz->carroAsociado = params.carroAsociado;
    pz->numeroSerie = params.numeroSerie;
    pz->anno = params.anno;
    pz->cilindrada = params.cilindrada;
    pz->compresionOriginal = params.compresionOriginal;
    pz->medidaOriginal = params.medidaOriginal;
    pz->medidaActual = params.medidaActual;
    pz->culata = NULL;
    pz->monoblock = NULL;

    generarSystemLog(id_usuario, "Inicializar Motor", "Motor", params.numeroSerie, INFO, 1,
                     "UsuarioDTO.c", "inicializarMotor", HTTP_CREATED);

    return pz;
}

Culata *inicializarCulata(int id_pieza, int numValvulas, double presionPrueba, int fisuras,
                          float alturaOriginal, float alturaActual, float alturaMinima, int id_usuario,
                          int estadoPieza) {
    Culata *culata = malloc(sizeof(Culata));
    if (culata == NULL) {
        generarSystemLog(id_usuario, "Inicializar Culata", "Culata", "UNKNOWN", ERROR, 0,
                         "UsuarioDTO.c", "inicializarCulata", HTTP_INTERNAL_SERVER_ERROR);
        perror("Error al asignar memoria para Culata");
        exit(EXIT_FAILURE);
    }

    culata->id_usuario = id_usuario;
    culata->id_pieza = id_pieza;
    culata->numValvulas = numValvulas;
    culata->presionPrueba = presionPrueba;
    culata->tieneFisuras = fisuras;
    culata->alturaOriginal = alturaOriginal;
    culata->alturaActual = alturaActual;
    culata->alturaMinima = alturaMinima;
    culata->estadoTemporalPieza = -1;
    culata->operacionesMotor = estadoPieza;
    setIdPiezaGlobal(getIdPiezaGlobal() + 1);

    char id_objeto[50];
    snprintf(id_objeto, sizeof(id_objeto), "CULATA_%d", id_pieza);

    generarSystemLog(id_usuario, "Inicializar Culata", "Culata", id_objeto, INFO, 1,
                     "UsuarioDTO.c", "inicializarCulata", HTTP_CREATED);

    return culata;
}

Monoblock *inicializarMonoblock(int id_pieza, int id_usuario, int numCilindros, const float *diametroCilindro,
                                const float *conicidad_max, int num_bancadas, const float *diametro_bancadas,
                                const float *desalineacion_bancadas,
                                float ovalizacion_max, float planitud_superficie, int flags, char *numero_serie,
                                char *observaciones,
                                int estado_diagnostico) {
    Monoblock *mono = malloc(sizeof(Monoblock));
    if (!mono) {
        perror("Fallo al asignar memoria para Monoblock");
        exit(EXIT_FAILURE);
    }

    mono->id_pieza = id_pieza;
    mono->id_usuario = id_usuario;
    mono->numCilindros = numCilindros;
    mono->num_bancadas = num_bancadas;
    mono->ovalizacion_max = ovalizacion_max;
    mono->planitud_superficie = planitud_superficie;
    mono->flags = flags;
    mono->estado_diagnostico = estado_diagnostico;

    mono->diametroCilindro = malloc(numCilindros * sizeof(float));
    mono->conicidad_max = malloc(numCilindros * sizeof(float));
    mono->desalineacion_bancadas = malloc(numCilindros * sizeof(float));
    mono->diametro_bancadas = malloc(num_bancadas * sizeof(float));

    if (!mono->diametroCilindro || !mono->conicidad_max || !mono->diametro_bancadas || !mono->desalineacion_bancadas) {
        perror("Fallo en malloc de arrays");
        free(mono);
        exit(EXIT_FAILURE);
    }

    memcpy(mono->diametroCilindro, diametroCilindro, numCilindros * sizeof(float));
    memcpy(mono->conicidad_max, conicidad_max, numCilindros * sizeof(float));
    memcpy(mono->diametro_bancadas, diametro_bancadas, num_bancadas * sizeof(float));
    memcpy(mono->desalineacion_bancadas, desalineacion_bancadas, num_bancadas * sizeof(float));

    mono->numero_serie = numero_serie;
    mono->observaciones = observaciones;

    if (!mono->numero_serie || !mono->observaciones) {
        perror("Fallo en malloc de cadenas");
        free(mono);
        exit(EXIT_FAILURE);
    }

    return mono;
}


void setIdUsuarioLogico(const int nuevoId) {
    id_UsuarioGlobal = nuevoId;
};

int getIdUsuarioLogico() {
    return id_UsuarioGlobal;
};

void setIdLog(const int id) {
    id_unicoLogs = id;
}

int getIdLog() {
    return id_unicoLogs;
}

void setIdPiezaGlobal(const int id) {
    id_piezaGlobal = id;
}

int getIdPiezaGlobal() {
    return id_piezaGlobal;
}


Motor *clonarMotor(Motor *original, int nuevoIdUsuario) {
    if (original == NULL) {
        generarSystemLog(nuevoIdUsuario, "Clonar Motor", "Motor", "NULL", ERROR, 0,
                         "UsuarioDTO.c", "clonarMotor", HTTP_UNPROCESSABLE_ENTITY);
        return NULL;
    }

    Motor *copia = malloc(sizeof(Motor));
    if (!copia) {
        generarSystemLog(nuevoIdUsuario, "Clonar Motor", "Motor", "NULL", ERROR, 0,
                         "UsuarioDTO.c", "clonarMotor", HTTP_INTERNAL_SERVER_ERROR);
        return NULL;
    }

    *copia = *original;
    copia->modelo = strdup(original->modelo);
    copia->fabricante = strdup(original->fabricante);
    copia->carroAsociado = strdup(original->carroAsociado);
    asignString(copia->material, original->material, sizeof(copia->material));
    copia->numeroSerie = strdup(original->numeroSerie);
    copia->id_usuario = nuevoIdUsuario;
    copia->culata = NULL;

    generarSystemLog(nuevoIdUsuario, "Clonar Motor", "Motor", copia->numeroSerie, INFO, 1,
                     "UsuarioDTO.c", "clonarMotor", HTTP_CREATED);

    return copia;
}

void liberarMonoblock(Monoblock *mono) {
    if (!mono) return;

    free(mono->diametroCilindro);
    free(mono->conicidad_max);
    free(mono->desalineacion_bancadas);
    free(mono->diametro_bancadas);
    free(mono->numero_serie);
    free(mono->observaciones);
    free(mono);
}
