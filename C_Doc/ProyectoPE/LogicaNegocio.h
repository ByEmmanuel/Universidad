//
// Created by Jesus Emmanuel Garcia on 2/17/25.
// Este es el archivo que simula ser una interface
// y desde aqui se declaran las funciones para tener un mejor control

#ifndef LOGICANEGOCIO_H
#define LOGICANEGOCIO_H

#include "UsuarioDTO.h"

//No Usar variables en haders
//char* empleado;

void mostrarLogo();

void menuPrincipal();

int loginUsuario();

int preguntaSalida();

int cliente();

int servicio();

int pago();

int almacen();

int otro();

int dudas();

int salir();

Usuario* obtenerUsuarioByIdUsuario(int id);
Motor* obtenerMotorPorNumeroDeSerie(const ArrayPiezas* array, const char* numeroDeSerieMotor) ;
Motor* obtenerMotorByIdUsuario(int id);
Ticket* obtenerTicketByIdUsuario(int id_usuario);
int obtenerIdSiExisteUsuario(int POS_Y, int POS_X);

// FUNCIONES EXCLUSIVAS DE REGISTRAR MOTORES

int registrarMotor();
int registrarCulata();
int registrarMonoblock();
void rectificarCulata(Culata* culata, int id_usuario);
int asignarMotorUsuario(Usuario* usuario, Motor* motor);
int asignarPiezaMotor(Usuario* usuario, void* pieza, int tipoDePieza);
int evaluarEstadoCulata(float alturaOriginal, float alturaActual, float alturaMinima, float tolerancia);
const char* estadoPiezaTexto(int estadoPieza);
void imprimirDetallesMotor(Motor* motor);
char* imprimirOperacionesCulata(int operacion);
int realizarOperacionesMotor();

/**
 * @deprecated
 */
void printCulata(const Culata* c);

const char* tipoCombustibleToStr(TipoCombustible tipo);


// FUNCIONES DE USO EXCLUSIVAMENTE PARA TICKETS
int generarNota(int id);
int generarTicket(int id);
int generarFactura(int id);
void imprimirDetallesTicket(int id, int fila);

//Funciones OTROS
int validarArchivo(FILE* archivo);
void historialTickets();
int exportarDetallesUsuarios(const char* nombreArchivo,FILE* archivo);
int exportarMotoresUsuarios(const char* nombreArchivo,FILE* archivo);
int exportarDetallesPiezas(const char* nombreArchivo,FILE* archivo);
int exportarDetallesTickets(const char* nombreArchivo, FILE* archivo);
int exportarMotoresPrecargados(const char* nombreArchivo,FILE* archivo);

void exportarDetallesTodoElSistema();
char* obtenerNombreArchivo(char* textoInicial);



#endif //LOGICANEGOCIO_H
