//
// Created by Jesus Emmanuel Garcia on 5/7/25.
//

#include <curses.h>
#include <stddef.h>
#include <stdlib.h>

#include "LogicaNegocio.h"
#include "SystemLogs.h"
#include "Util.h"
// Función para agregar un usuario a la lista
int guardarUsuarioArray(Usuario usuario) {
    if (arrayUsuarios.tamanno >= arrayUsuarios.capacidad) {
        const int nuevaCapacidad = arrayUsuarios.capacidad == 0 ? 1 : arrayUsuarios.capacidad * 2;
        Usuario* nuevoArray = realloc(arrayUsuarios.datos, nuevaCapacidad * sizeof(Usuario));
        if (nuevoArray == NULL) {
            printf("Error al redimensionar el array de usuarios.\n");
            generarSystemLog(usuario.id_usuario, "Guardar", "Array", "Usuario", WARN, 0, "UsuarioDAO", "guardarUsuarioArray", HTTP_BAD_REQUEST);
            return -1;
        }
        arrayUsuarios.datos = nuevoArray;
        arrayUsuarios.capacidad = nuevaCapacidad;
    }
    generarSystemLog(usuario.id_usuario, "Guardar", "Array", "Usuario", INFO, 1, "UsuarioDAO", "guardarUsuarioArray", HTTP_OK);
    arrayUsuarios.datos[arrayUsuarios.tamanno] = usuario;
    arrayUsuarios.tamanno++;
    return 1; // Retorna 1 si se guardó correctamente
}

int guardarMotorArray(void* motor, const int id_usuario) {
    if (arrayMotoresUsuarios.tamanno >= arrayMotoresUsuarios.capacidad) {
        const int nuevaCapacidad = arrayMotoresUsuarios.capacidad == 0 ? 1 : arrayMotoresUsuarios.capacidad * 2;
        void* nuevoArray = realloc(arrayMotoresUsuarios.datos, nuevaCapacidad * sizeof(void*));
        if (nuevoArray == NULL) {
            generarSystemLog(id_usuario, "Redimensionar Array", "Motor", "motor", ERROR, 0,
                             "UsuarioDAO", "guardarMotorArray", HTTP_INTERNAL_SERVER_ERROR);
            printf("Error al redimensionar el array de Piezas.\n");
            return -1;
        }
        arrayMotoresUsuarios.datos = nuevoArray;
        arrayMotoresUsuarios.capacidad = nuevaCapacidad;
        generarSystemLog(id_usuario, "Redimensionar Array", "Motor", "motor", INFO, 1,
                         "UsuarioDAO", "guardarMotorArray", HTTP_OK);
    }

    arrayMotoresUsuarios.datos[arrayMotoresUsuarios.tamanno] = motor;
    arrayMotoresUsuarios.tamanno++;
    arrayMotoresUsuarios.id_usuario = id_usuario;
    generarSystemLog(id_usuario, "Guardar Motor", "Motor", "motor", INFO, 1,
                     "UsuarioDAO", "guardarMotorArray", HTTP_CREATED);
    return 1;
}
//Tipo Pieza "culata" o "monoblock"
int guardarPiezaArray(void* pieza, int id_usuario, char* tipoPieza){
    if (arrayPiezas.tamanno >= arrayPiezas.capacidad) {
        const int nuevaCapacidad = arrayPiezas.capacidad == 0 ? 1 : arrayPiezas.capacidad * 2;
        void** nuevoArray = realloc(arrayPiezas.datos, nuevaCapacidad * sizeof(void*));
        if (nuevoArray == NULL) {
            generarSystemLog(id_usuario, "Redimensionar Array", tipoPieza, "Pieza", ERROR, 0,
                             "UsuarioDAO", "guardarPiezaArray", HTTP_INTERNAL_SERVER_ERROR);
            printf("Error al redimensionar el array de Piezas.\n");
            return -1;
        }
        arrayPiezas.datos = nuevoArray;
        arrayPiezas.capacidad = nuevaCapacidad;
        generarSystemLog(id_usuario, "Redimensionar Array", tipoPieza, tipoPieza, INFO, 1,
                         "UsuarioDAO", "guardarPiezaArray", HTTP_OK);
    }

    arrayPiezas.datos[arrayPiezas.tamanno] = pieza;
    arrayPiezas.tamanno++;
    arrayPiezas.id_usuario = id_usuario;
    generarSystemLog(id_usuario, "Guardar Pieza", tipoPieza, "Pieza", INFO, 1,
                     "UsuarioDAO", "guardarPiezaArray", HTTP_CREATED);
    return 1;
}

int guardarTicket(Ticket ticket) {
    int usuario_id = ticket.usuario ? ticket.usuario->id_usuario : 0;

    if (arrayTickets.tamanno >= arrayTickets.capacidad) {
        const int nuevaCapacidad = arrayTickets.capacidad == 0 ? 1 : arrayTickets.capacidad * 2;
        Ticket* nuevoArray = realloc(arrayTickets.datos, nuevaCapacidad * sizeof(Ticket));
        if (nuevoArray == NULL) {
            generarSystemLog(usuario_id, "Redimensionar Array", "Ticket", "Ticket", ERROR, 0,
                             "UsuarioDAO", "guardarTicket", HTTP_INTERNAL_SERVER_ERROR);
            printf("Error al redimensionar el array de tickets.\n");
            return -1;
        }
        arrayTickets.datos = nuevoArray;
        arrayTickets.capacidad = nuevaCapacidad;
        generarSystemLog(usuario_id, "Redimensionar Array", "Ticket", "Ticket", INFO, 1,
                         "UsuarioDAO", "guardarTicket", HTTP_OK);
    }

    arrayTickets.datos[arrayTickets.tamanno] = ticket;
    arrayTickets.tamanno++;
    generarSystemLog(usuario_id, "Guardar Ticket", "Ticket", "Ticket", INFO, 1,
                     "UsuarioDAO", "guardarTicket", HTTP_CREATED);
    return 1;
}

/**
 *
 * Esto asigna al ticket, un usuario siempre que usuario no sea null.
 * Esto asigna al ticket, un motor AL Usuario del ticket siempre que usuario y motor no sea null.
 * @param usuario
 * @param motor
 * @param detalles
 * @param detalles2
 * @return
 */
Ticket inicializarTicket(Usuario* usuario,Motor* motor,char* detalles, char* detalles2){
    Ticket ticket = {0};
    if (usuario != NULL) ticket.usuario = usuario;
    if (motor != NULL && usuario != NULL) ticket.usuario->motor = motor;
    ticket.detalles = detalles;
    ticket.detalles2 = detalles2;

    return ticket;
}

// Función para obtener un usuario por ID
Usuario* obtenerUsuarioByIdUsuario(const int id) {
    for (int i = 0; i < arrayUsuarios.tamanno; i++) {
        if (arrayUsuarios.datos[i].id_usuario == id) {
            return &arrayUsuarios.datos[i];
        }
    }
    // Retorna NULL si el usuario no existe
    mvprintw(12, 5, "Usuario no encontrado, no corresponde a un numero de ID, o Esta Eliminado");
    getch();
    return NULL;
}

Motor* obtenerMotorByIdUsuario(const int id) {
    for (int i = 0; i < arrayMotoresUsuarios.tamanno; i++) {
        Motor* motor = (Motor*)arrayMotoresUsuarios.datos[i]; // <-- Convertir el void* a Motor* CORRECTAMENTE
        if (motor->id_usuario == id) {
            return motor;  // Ya es un puntero, no necesito &
        }
    }
    // Retorna NULL si no encuentra
    clear();
    mvprintw(12, 10, "X Motor no encontrado o ID de usuario invalido");
    getch();
    return NULL;
}

Motor* obtenerMotorPorNumeroDeSerie(const ArrayPiezas* array, const char* numeroDeSerieMotor) {
    for (int i = 0; i < array->tamanno; i++) {
        Motor* motor = (Motor*) array->datos[i];
        if (strEquals(motor->numeroSerie, numeroDeSerieMotor)){
            return motor;
        }
    }
    clear();
    mvprintw(12, 10, "El numero de serie ingresado no coincide con ningun registro.");
    getch();
    return NULL;
}


Ticket* obtenerTicketByIdUsuario(int id_usuario){
    for (int i = 0; i < arrayTickets.tamanno; i++) {
        if (arrayTickets.datos[i].usuario->id_usuario == id_usuario) {
            //mostrarUsuario(arrayUsuarios.datos[i]);
            return &arrayTickets.datos[i];
        }
    }
    // Retorna NULL si el usuario no existe
    return NULL;

}

int obtenerIdSiExisteUsuario(const int POS_Y, const int POS_X){
    const int id_usuario = leerIntSeguro(POS_Y,POS_X,10000,"Ingrese Id Usuario: ");
    RETURN_IF_ESC(id_usuario);
    const Usuario* usuario = obtenerUsuarioByIdUsuario(id_usuario);
    if (usuario == NULL || usuario->activo == 0) {
        return -1;
    }
    return id_usuario;
}
