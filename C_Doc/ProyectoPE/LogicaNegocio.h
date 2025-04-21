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

Usuario* obtenerUsuarioById(const int id);

int asignarPiezaUsuario(Usuario* usuario, void* pieza);

void printCulata(const Culata* c);

//FUNCIONEs DE TESTEO, NO TENER EN PRODUCCION
void testing(int encendido);
void agregarUsuarios();
void agregarPiezas();



#endif //LOGICANEGOCIO_H
