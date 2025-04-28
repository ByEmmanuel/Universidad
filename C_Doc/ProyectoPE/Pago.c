//
// Created by Jesus Emmanuel Garcia on 4/23/25.
//

#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "UsuarioDTO.h"
#include "Util.h"
#include "LogicaNegocio.h"
#include "UserInterface.h"

/**
 * Constantes que son los precios del taller
 */
const float precioRectificado = 850.0f;
const float precioPruebaPresion = 350.0f;
const float precioLavado = 160.0f ;
const float iva = 0.16f;

int pago(){
    const int id_usuario = obtenerIdSiExisteUsuario();
    RETURN_IF_ESC(id_usuario);

    clear();
    void* pieza = obtenerPiezaByIdUsuario(id_usuario);
    if (!pieza) {
        mvprintw(10, 10, "No se encontró ninguna pieza asociada al usuario con ID %d", id_usuario);
        getch();
        return -1;
    }

    /**
    Culata* culata = NULL;
    Monoblock* monoblock = NULL;
    */

    Motor* motorBase = (Motor*)pieza;
    /**
    if (motorBase->tipoPieza == CULATA) {
        culata = (Culata*)pieza;
    } else if (motorBase->tipoPieza == MONOBLOCK) {
        monoblock = (Monoblock*)pieza;
    }
    */

    Ticket ticket = inicializarTicket(obtenerUsuarioByIdUsuario(id_usuario), motorBase, NULL, NULL);
    if (obtenerTicketByIdUsuario(id_usuario) == NULL){
        if (guardarTicket(ticket) != 1){
            mvprintw(20,10,"X Error al crear los ticket's. Inténtelo de nuevo.");
            getch();
            return -1;
        }
        mvprintw(5,10,"¡Ordenes de pago creadas correctamente - Presione enter !");
        getch();
    }

    const int opcUsr = mostrarMenu(14,"Porfavor selecciona una opcion");
    RETURN_IF_ESC(opcUsr);

    //GENERAR nota GENERAR ticket GENERAR factura listar

    switch (opcUsr){
        case 0:{
                RETURN_IF_ESC(generarNota(id_usuario));
        }break;
        case 1:{
                RETURN_IF_ESC(generarTicket(id_usuario));
        }break;
        case 2:{
                RETURN_IF_ESC(generarFactura(id_usuario));
        }break;
        case 3:{
                imprimirDetallesTicket(id_usuario);
        }break;
        default:
                mvprintw(10,10,"Opcion no valida, Intente de nuevo -> Ticket");
            clear();
            getch();
            break;
    }

    return 0;
}

int generarNota(int id_usuario){
    clear();
    Ticket* ticket = obtenerTicketByIdUsuario(id_usuario);

    if (ticket == NULL){
        mvprintw(5, 5, "==============================================");
        mvprintw(6, 10, "ERROR: Ticket no encontrado");
        mvprintw(7, 5, "==============================================");
        mvprintw(9, 10, "No existe un ticket vinculado al ID ingresado.");
        mvprintw(11, 10, "Presione cualquier tecla para continuar...");
        getch();
        return -1;
    }

    if (ticket->detalles == NULL && ticket->detalles2 == NULL){
        char* detalles = leerStringSeguro(10, 5, 255, "Ingrese detalles de la operación para OPCION NOTA -MAX 255 & MIN 1 caracter-");
        char* detalles2 = leerStringSeguro(13, 5, 255, "Ingrese detalles adicionales -MAX 255 & MIN 1 caracter-");
        if (detalles == NULL || detalles2 == NULL){
            clear();
            mvprintw(10,10,"Ocurrio un error al crear la nota, intente de nuevo");
            getch();
            return -1;
        };
        ticket->detalles = detalles;
        ticket->detalles2 = detalles2;
    }

    clear();
    int fila = 2;
    mvprintw(fila++, 5, "==============================================");
    mvprintw(fila++, 15, "NOTA DE OPERACION");
    mvprintw(fila++, 5, "==============================================");

    mvprintw(fila++, 5, "Detalles proporcionados:");
    fila++; // espacio visual
    mvprintw(fila++, 5, "Nombre del Cliente: %s", ticket->usuario->nombreUsuario);
    mvprintw(fila++, 5, "Fabricante del motor: %s", ticket->usuario->motor->fabricante);
    mvprintw(fila++, 5, "Numero de serie: %s", ticket->usuario->motor->numeroSerie);
    mvprintw(fila++, 5, "Material del motor: %s", ticket->usuario->motor->material);

    imprimirTextoMultilinea(fila+=2, 5, ticket->detalles, 60);
    fila += 4; // espacio estimado, puedes ajustarlo dinámicamente
    imprimirTextoMultilinea(fila, 5, ticket->detalles2, 60);
    fila += 5;

    mvprintw(fila++, 5, "----------------------------------------------");
    mvprintw(fila++, 10, "Presione cualquier tecla para continuar...");
    getch();

    return 1;
}

int generarTicket(int id_usuario){
    clear();
    Ticket* ticket = obtenerTicketByIdUsuario(id_usuario);

    if (ticket == NULL){
        mvprintw(5, 5, "==============================================");
        mvprintw(6, 10, "ERROR: Ticket no encontrado");
        mvprintw(7, 5, "==============================================");
        mvprintw(9, 10, "No existe un ticket vinculado al ID ingresado.");
        mvprintw(11, 10, "Presione cualquier tecla para continuar...");
        getch();
        return -1;
    }

    Usuario* usr = ticket->usuario;
    Motor* motor = ticket->usuario->motor;

    /**
    Culata* culata = ticket->culata;
    Monoblock* monoblock = ticket->monoblock;
    if (culata != NULL) motor = &culata->motor;
    else if (monoblock != NULL) motor = &monoblock->motor;
    */


    if (motor == NULL) {
        mvprintw(13, 10, "Motor no asignado. No se puede generar el ticket.");
        getch();
        return -1;
    }

    // Simulación de precios
    const float precioFinalRectificado = motor->necesitaRectificacion ? precioRectificado : 0.0f;
    const float precioFinalPruebaPresion = (motor->culata != NULL) ? precioPruebaPresion : 0.0f;
    const float precioFinalLavado =  ticket->lavado ? precioLavado : 0.0f;
    const float subtotal = precioFinalRectificado + precioFinalPruebaPresion + precioFinalLavado;
    const float impuesto = subtotal * iva;
    const float total = subtotal + impuesto;

    int fila = 2;
    mvprintw(fila++, 5, "==================================================");
    mvprintw(fila++, 15, "TICKET DE SERVICIO - ID USUARIO: %d", usr->id_usuario);
    mvprintw(fila++, 5, "==================================================");

    mvprintw(fila++, 5, "Cliente: %s %s", usr->nombreUsuario, usr->apellido);
    mvprintw(fila++, 5, "Folio: %s", usr->folio);
    mvprintw(fila++, 5, "Contacto: %s", usr->contacto);
    mvprintw(fila++, 5, "Email: %s", usr->email);
    mvprintw(fila++, 5, "Celular: %lld", usr->celular);
    fila++;

    mvprintw(fila++, 5, "---------------- DATOS DEL MOTOR -----------------");
    mvprintw(fila++, 5, "Nombre: %s", motor->nombre);
    mvprintw(fila++, 5, "Fabricante: %s", motor->fabricante);
    mvprintw(fila++, 5, "Serie: %s", motor->numeroSerie);
    mvprintw(fila++, 5, "Combustible: %s", tipoCombustibleToStr(motor->tipoCombustible));
    mvprintw(fila++, 5, "Tipo: %s", motor->culata != NULL ? "Culata" : "Culata no asignada");
    mvprintw(fila++, 5, "Material: %s", motor->material);
    mvprintw(fila++, 5, "Medida Original: %.2f mm", motor->medidaOriginal);
    mvprintw(fila++, 5, "Medida Actual: %.2f mm", motor->medidaActual);
    mvprintw(fila++, 5, "Rectificar: %s", motor->necesitaRectificacion ? "Sí" : "No");

    if (motor->culata != NULL) {
        mvprintw(fila++, 5, "N° Válvulas: %d", motor->culata->numValvulas);
        mvprintw(fila++, 5, "Presión Prueba: %.2f bar", motor->culata->presionPrueba);
        mvprintw(fila++, 5, "Fisuras: %s", motor->culata->tieneFisuras ? "Sí" : "No");
    }

    fila++;
    mvprintw(fila++, 5, "----------------- RESUMEN DE COSTOS ------------------");
    mvprintw(fila++, 5, "Rectificación:       $ %.2f", precioFinalRectificado);
    mvprintw(fila++, 5, "Prueba de Presión:   $ %.2f", precioFinalPruebaPresion);
    mvprintw(fila++, 5, "Lavado de motor:     $ %.2f", precioFinalLavado);
    mvprintw(fila++, 5, "------------------------------------------------------");
    mvprintw(fila++, 5, "Subtotal:            $ %.2f", subtotal);
    mvprintw(fila++, 5, "IVA (16%%):           $ %.2f", impuesto);
    mvprintw(fila++, 5, "TOTAL:               $ %.2f", total);
    mvprintw(fila++, 5, "==================================================");

    mvprintw(fila + 1, 5, "Presione cualquier tecla para continuar...");
    getch();

    return 1;
}

int generarFactura(int id_usuario){
    clear();
    Ticket* ticket = obtenerTicketByIdUsuario(id_usuario);

    if (ticket == NULL){
        mvprintw(5, 5, "==================================================");
        mvprintw(6, 10, "FACTURA NO DISPONIBLE: Ticket no encontrado");
        mvprintw(7, 5, "==================================================");
        mvprintw(9, 10, "No existe información fiscal asociada al usuario.");
        mvprintw(11, 10, "Presione cualquier tecla para continuar...");
        getch();
        return -1;
    }

    Usuario* usr = ticket->usuario;
    Motor* motor = ticket->usuario->motor;
    /**
    Culata* culata = ticket->culata;
    Monoblock* monoblock = ticket->monoblock;
    if (culata != NULL) motor = &culata->motor;
    else if (monoblock != NULL) motor = &monoblock->motor;
    */



    if (motor == NULL){
        mvprintw(13, 10, "Motor no asignado al usuario. No se puede facturar.");
        getch();
        return -1;
    }

    // Generar fecha actual
    time_t t = time(NULL);
    struct tm fecha = *localtime(&t);

    // Simulación de precios
    const float precioFinalRectificado = motor->necesitaRectificacion ? precioRectificado : 0.0f;
    const float precioFinalPruebaPresion = (motor->culata != NULL) ? precioPruebaPresion : 0.0f;
    const float precioFinalLavado =  ticket->lavado ? precioLavado : 0.0f;
    const float subtotal = precioFinalRectificado + precioFinalPruebaPresion + precioFinalLavado;
    const float impuesto = subtotal * iva;
    const float total = subtotal + impuesto;

    int fila = 2;
    mvprintw(fila++, 5, "============================================================");
    mvprintw(fila++, 18, "FACTURA ELECTRÓNICA DE SERVICIO AUTOMOTRIZ");
    mvprintw(fila++, 5, "============================================================");
    mvprintw(fila++, 5, "Folio Interno: %s", usr->folio);
    mvprintw(fila++, 5, "Fecha Emisión: %02d/%02d/%04d %02d:%02d",
             fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900,
             fecha.tm_hour, fecha.tm_min);
    mvprintw(fila++, 5, "RFC Cliente: CLI890123XYZ");  // Ficticio
    mvprintw(fila++, 5, "Nombre Cliente: %s %s", usr->nombreUsuario, usr->apellido);
    mvprintw(fila++, 5, "Correo: %s", usr->email);
    mvprintw(fila++, 5, "Domicilio Fiscal: Calle Ficticia 123, Ciudad Ejemplo, MX");
    mvprintw(fila++, 5, "------------------------------------------------------------");
    mvprintw(fila++, 5, "Descripción del Servicio:");
    fila++;

    if (motor->necesitaRectificacion)
        mvprintw(fila++, 7, "- Rectificación de pieza               $ %.2f", precioFinalRectificado);
    if (motor->culata != NULL)
        mvprintw(fila++, 7, "- Prueba de presión en culata          $ %.2f", precioFinalPruebaPresion);
    mvprintw(fila++, 7, "- Lavado general                       $ %.2f", precioFinalLavado);
    fila++;

    mvprintw(fila++, 5, "------------------------------------------------------------");
    mvprintw(fila++, 5, "Subtotal:                              $ %.2f", subtotal);
    mvprintw(fila++, 5, "IVA (16%%):                             $ %.2f", impuesto);
    mvprintw(fila++, 5, "TOTAL A PAGAR:                         $ %.2f", total);
    mvprintw(fila++, 5, "============================================================");

    mvprintw(fila++, 5, "Condiciones de pago: Contado");
    mvprintw(fila++, 5, "Forma de pago: Efectivo / Transferencia");
    mvprintw(fila++, 5, "Uso CFDI: G03 - Gastos en general");
    mvprintw(fila++, 5, "Método de pago: PUE - Pago en una sola exhibición");
    mvprintw(fila++, 5, "============================================================");

    mvprintw(fila++, 5, "Gracias por confiar en nuestros servicios.");
    mvprintw(fila++, 5, "Presione cualquier tecla para finalizar...");
    getch();

    return 1;


}

void imprimirDetallesTicket(int id_usuario){
    int fila = 1;
    clear();
    mvprintw(fila++, 4, "IMPRIMIR DETALLES TICKET USUARIO ON");
    mvprintw(fila++, 4, "Tamanno array %d", arrayTickets.tamanno);

    for (int i = 0; i < arrayTickets.tamanno; i++){
        if (arrayTickets.datos[i].usuario->id_usuario == id_usuario){
            Usuario* usr = arrayTickets.datos[i].usuario;

            mvprintw(fila++, 4, "==============================================");
            mvprintw(fila++, 10, "INFORMACION DEL USUARIO");
            mvprintw(fila++, 4, "==============================================");
            mvprintw(fila++, 2, "ID Usuario: %d", usr->id_usuario);
            mvprintw(fila++, 2, "Folio: %s", usr->folio);
            mvprintw(fila++, 2, "Nombre: %s %s", usr->nombreUsuario, usr->apellido);
            mvprintw(fila++, 2, "Celular: %lld", usr->celular);
            mvprintw(fila++, 2, "Email: %s", usr->email);
            mvprintw(fila++, 2, "Contacto: %s", usr->contacto);
            mvprintw(fila++, 2, "Activo: %s", usr->activo ? "Si" : "No");

            Motor* motor = usr->motor;
            Culata* culata = usr->motor->culata;
            Monoblock* monoblock = usr->motor->monoblock;

            /*
             if (culata != NULL) {
                motor = &culata->motor;
            } else if (monoblock != NULL) {
                motor = &monoblock->motor;
            }
            */

            if (motor == NULL) {
                mvprintw(fila++, 2, "Motor: No asignado.");
                getch();
                return;
            }

            mvprintw(fila++, 4, "==============================================");
            mvprintw(fila++, 10, "INFORMACION DE LA PIEZA / MOTOR");
            mvprintw(fila++, 4, "==============================================");

            mvprintw(fila++, 2, "ID Pieza: %d", motor->id_pieza);
            mvprintw(fila++, 2, "ID Usuario: %d", motor->id_usuario);
            mvprintw(fila++, 2, "Nombre Motor: %s", motor->nombre);
            mvprintw(fila++, 2, "Fabricante: %s", motor->fabricante);
            mvprintw(fila++, 2, "Numero Serie: %s", motor->numeroSerie);
            mvprintw(fila++, 2, "Cilindrada: %.2f L", motor->cilindrada);
            mvprintw(fila++, 2, "Compresion Original: %.2f psi", motor->compresionOriginal);
            mvprintw(fila++, 2, "Combustible: %s", tipoCombustibleToStr(motor->tipoCombustible));
            mvprintw(fila++, 2, "Material: %s", motor->material);
            mvprintw(fila++, 2, "Desgaste: %.2f%%", motor->desgaste * 100);
            mvprintw(fila++, 2, "Tolerancia: %.4f mm", motor->tolerancia);
            mvprintw(fila++, 2, "Medida Original: %.4f mm", motor->medidaOriginal);
            mvprintw(fila++, 2, "Medida Actual: %.4f mm", motor->medidaActual);
            mvprintw(fila++, 2, "Rectificacion: %s", motor->necesitaRectificacion ? "Si" : "No");
            mvprintw(fila++, 2, "Lavado?: %s", arrayTickets.datos[i].lavado ? "Si" : "No");

            if (motor->culata != NULL) {
                mvprintw(fila++, 4, "----------- CULATA -----------");
                mvprintw(fila++, 4, "Numero Valvulas: %d", culata->numValvulas);
                mvprintw(fila++, 4, "Presion de Prueba: %.2f bar", culata->presionPrueba);
                mvprintw(fila++, 4, "Fisuras: %s", culata->tieneFisuras ? "Si" : "No");
            } else if (motor->monoblock != NULL) {
                mvprintw(fila++, 4, "---------- MONOBLOCK ---------");
                mvprintw(fila++, 4, "Numero Cilindros: %d", monoblock->numCilindros);
                mvprintw(fila++, 4, "Diametro: %.2f mm", monoblock->diametroCilindro);
                mvprintw(fila++, 4, "Ovalizacion: %.2f mm", monoblock->ovalizacion);
                mvprintw(fila++, 4, "Alineacion Ciguenal: %.2f mm", monoblock->alineacionCiguenal);
            }

            mvprintw(fila++, 4, "==============================================");
            mvprintw(fila++, 10, "Presiona cualquier tecla para continuar...");
            getch();
            return;
        }
    }
}