//
// Created by Jesus Emmanuel Garcia on 2/17/25.
// Interface principal: Declaración de funciones del sistema de rectificación
//

#ifndef LOGICANEGOCIO_H
#define LOGICANEGOCIO_H

// ------------------------------------- Includes
#include "UsuarioDTO.h"
#include <stdio.h>

// ------------------------------------- Modulo Principal
void menuPrincipal();
extern char* empleado;

// ------------------------------------- UI y flujo principal
void mostrarLogo();
int servicio();
int almacen();
int otro();
int dudas();
int salir();

// -------------------------------------  Clientes
int loginUsuario();
int cliente();
int modificarCliente();
void listarFoliosUsuarios();
void listarPiezas();


// -------------------------------------  UsuarioDAO
Usuario* obtenerUsuarioByIdUsuario(int id);
Motor* obtenerMotorPorNumeroDeSerie(const ArrayPiezas* array, const char* numeroDeSerieMotor);
Motor* obtenerMotorByIdUsuario(int id);
Ticket* obtenerTicketByIdUsuario(int id_usuario);
int obtenerIdSiExisteUsuario(int POS_Y, int POS_X);

Ticket inicializarTicket(Usuario* usuario,Motor* motor ,char* detalles, char* detalles2);
int guardarUsuarioArray(Usuario usuario);
int guardarMotorArray(void* motor, int id_usuario);
int guardarPiezaArray(void* pieza, int id_usuario,char* tipoPieza);
int guardarTicket(Ticket ticket);

// -------------------------------------  Registrar Motores
int registrarMotor();
int registrarCulata();
int registrarMonoblock();
void rectificarCulata(Culata* culata, int id_usuario);
void imprimirDetallesMotor(Motor* motor);
int asignarMotorUsuario(Usuario* usuario, Motor* motor);
int asignarPiezaMotor(Usuario* usuario, void* pieza, int tipoDePieza);
int evaluarEstadoCulata(float alturaOriginal, float alturaActual, float alturaMinima, float tolerancia);
const char* imprimirOperacionesEstadoPieza(int estado, int tipoPieza);
int realizarOperacionesMotor();
int realizarOperacionesPiezaMotor(int tipoPieza);

int evaluarDiametrosCilindros(float* diametros, int numCilindros, int y, int* necesitaReconstruccion);
int evaluarConicidadCilindros(const float* conicidades, int numCilindros, int y);
int evaluarDesalineacionCilindros(float* desalineaciones, int numCilindros, int y);
int evaluarDiametrosBancadas(float* bancadas, int num_bancadas, int y);
int evaluarOvalidad(float oval, int y);
int evaluarPlanitud(float planitud, int y);
int evaluarJuegoAxial(int y, float* grosorLaina);
void actualizarStockLaina(float grosor, int cantidad);
void registrarUsoHerramienta(char* idHerramienta, char* etapa);

// -------------------------------------  Utilidades
const char* tipoCombustibleToStr(TipoCombustible tipo);
char* obtenerNombreArchivo(const char* textoInicial);

// -------------------------------------  Tickets y Pagos
int pago();
int generarNota(int id, FILE* archivo);
int generarTicket(int id, FILE* archivo);
int generarFactura(int id, FILE* archivo);
void imprimirDetallesTicket(int id, int fila);
const char* estadoPiezaTexto(int estadoPieza);

// -------------------------------------  Exportaciones
int exportarDetallesUsuarios(const char* nombreArchivo, FILE* archivo);
int exportarDetallesPiezasAlmacen(const char* nombreArchivo, FILE* archivo);
int exportarDetallesTickets(const char* nombreArchivo, FILE* archivo);
int exportarDetallesMotoresPrecargados(const char* nombreArchivo, FILE* archivo);
void exportarDetallesTodoElSistema();

// -------------------------------------  Historial y validaciones
int validarArchivo(FILE* archivo);
void historialTickets();

// -------------------------------------  Almacen
int cargarAlmacen();
void precargarPiezasAlmacen(PiezaAlmacen pieza_almacen[], int cantidad);
PiezaAlmacen* buscarPiezaPorIdUnico(ArrayPiezasAlmacen* inventario, int numPiezas, char *id_unico);
void imprimirArrayPiezasAlmacen();
void ejecutarOpcionAlmacen(int opcionMenu, int opcionSubMenu);
int listarPiezasAlmacen();
int buscarPiezasAlmacen();
int agregarPizasAlmacen();
int eliminarPiezasAlmacen();
void imprimirArrayPiezasAlmacenArchivo(FILE* archivo);
Herramienta* incializarHerramienta(char* id_herramienta, char* tipo, int usos, char* compatibilidad,
    float rango, char* material, int cantidad);

#endif //LOGICANEGOCIO_H