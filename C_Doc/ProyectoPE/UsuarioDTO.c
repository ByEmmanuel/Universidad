//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//

#include "UsuarioDTO.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LogicaNegocio.h"
#include "UserInterface.h"
#include "ConstantesMotores.h"
#include "Util.h"
//Variable encapsulada -> Private
int id_UsuarioGlobal = 0;
int id_piezaGlobal = 0;
//int id_Pieza = 0;
// Declaración global de array's
ArrayUsuarios arrayUsuarios = {0};
ArrayTickets arrayTickets = {0};  // ← variable global
ArrayList array_list;
ArrayPiezas arrayMotoresPrecargados = {0};
ArrayPiezas arrayMotoresUsuarios = {0};
ArrayPiezas arrayPiezas = {0};


//Funciones Importantes para la ejecucion detodo el programa y evitar la reutilizacion de codigo

Usuario inicializarUsuario(const int id_usuario,const char* folio , const char* nombreUsuario, const char* apellido,
                           long long celular, const char* email, const char* contacto) {
    Usuario usr = {0}; // Inicializa la estructura en 0 para evitar datos basura
    usr.id_usuario = id_usuario;
    asignString(usr.folio, folio, sizeof(usr.folio));
    asignString(usr.nombreUsuario, nombreUsuario, sizeof(usr.nombreUsuario));
    asignString(usr.apellido, apellido, sizeof(usr.apellido));
    usr.celular = celular;
    asignString(usr.email, email, sizeof(usr.email));
    asignString(usr.contacto, contacto, sizeof(usr.contacto));

    usr.motor = NULL;
    usr.activo = 1;
    //Adiciona 1 al ID usuario desde aqui para que el usuario nunca tenga el mismo ID sin importar si es valido el usuario o no
    setIdUsuarioLogico(getIdUsuarioLogico() + 1);
    return usr;
}

/**
 * Solo se pasaran commo variables estaticas
 * Las variables que no pertenecen unicamente del motor
 * @param params
 * @param paramsmotor
 * @param id_usuario,
 * @param id_pieza,
 * @param numero_serie
 * @param tipoDePieza
 * @param tipoPieza -> MONOBLOCK = 0, CULATA = 1.
 *
 */
Motor* inicializarMotor(Paramsmotor params, const int id_usuario, const int id_pieza, void* tipoDePieza, const int tipoPieza) {
    Motor* pz = (Motor*)malloc(sizeof(Motor));
    if (pz == NULL) {
        perror("Error al asignar memoria para Motor");
        exit(EXIT_FAILURE);
    }

    // Inicialización básica
    pz->id_usuario = id_usuario;
    pz->id_pieza = id_pieza;
    pz->tipoCombustible = params.tipoCombustible;

    // Copia profunda de material
    asignString(pz->material, params.material, sizeof(pz->material));
    pz->modelo = params.modelo;
    pz->fabricante = params.fabricante;
    pz->carroAsociado = params.carroAsociado;
    pz->numeroSerie = params.numeroSerie;

    // Datos técnicos
    pz->anno = params.anno;
    pz->cilindrada = params.cilindrada;
    pz->compresionOriginal = params.compresionOriginal;
    pz->medidaOriginal = params.medidaOriginal;
    pz->medidaActual = params.medidaActual;

    // Relaciones
    pz->culata = NULL;
    pz->monoblock = NULL;

    return pz;
}

Culata* inicializarCulata(int id_pieza , int numValvulas, double presionPrueba,int fisuras,
    float alturaOriginal, float alturaActual, float alturaMinima, int id_usuario, int estadoPieza){

    //Variables que estan en Culata
    Culata* culata = malloc(sizeof(Culata));
    if (culata == NULL) {
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
    // 0 = No valido, -1 = Rectificacion, -2 = Reconstruccion
    culata->operacionesMotor = estadoPieza;
    //Sumar 1 al contador de piezas globales
    id_piezaGlobal++;
    return culata;
}


//Getters y setters
void setIdUsuarioLogico(const int nuevoId){
    id_UsuarioGlobal = nuevoId;
};
int getIdUsuarioLogico(){
    return id_UsuarioGlobal;
};

//Funcion para clonar el contenido de una variable a otra nueva variable
//-> Esto no pasaria con POO ya que cada nuevo objeto es una nueva direccion en memoria, y si quiero asignar, se asignan los valores de esa direccion PROPIA
Motor* clonarMotor(Motor* original, int nuevoIdUsuario){
    if (original == NULL) return NULL;

    Motor* copia = malloc(sizeof(Motor));
    if (!copia) return NULL;

    *copia = *original; // copia los valores primitivos

    // Copiar strings dinámicamente (si no son constantes)
    copia->modelo = strdup(original->modelo);
    copia->fabricante = strdup(original->fabricante);
    copia->carroAsociado = strdup(original->carroAsociado);

    //copia->material = strdup(original->material);
    imprimirMensaje(5,5,"Depuracion FUN CLONAR MOTOR usuarioDTO.c");
    asignString(copia->material, original->material, sizeof(copia->material));
    copia->numeroSerie = strdup(original->numeroSerie);

    copia->id_usuario = nuevoIdUsuario;
    copia->culata = NULL; // No copiamos la culata aquí, puede hacerse por separado

    return copia;
}