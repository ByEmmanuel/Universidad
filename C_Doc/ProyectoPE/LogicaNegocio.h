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

int servicio();

int pago();

int almacen();

int otro();

int dudas();

int salir();

Usuario* obtenerUsuarioByIdUsuario(int id);
void* obtenerPiezaByIdUsuario(int id);
Ticket* obtenerTicketByIdUsuario(int id_usuario);
int obtenerIdSiExisteUsuario();

void imprimirDetallesTicket(int id);

int asignarPiezaUsuario(Usuario* usuario, Culata* culata, Monoblock* monoblock );

/**
 * @deprecated
 */
void printCulata(const Culata* c);

const char* tipoCombustibleToStr(TipoCombustible tipo);


// FUNCIONES DE USO EXCLUSIVAMENTE PARA TICKETS
int generarNota(int id);
int generarTicket(int id);
int generarFactura(int id);

//FUNCIONEs DE TESTEO, NO TENER EN PRODUCCION
void testing(int encendido);
void agregarUsuarios();
void agregarPiezas();



#endif //LOGICANEGOCIO_H
