//
// Created by Jesus Emmanuel Garcia on 4/23/25.
//

#include <stdio.h>
#include <unistd.h>
#include <curses.h>
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
const float precioReconstruccion = 1200.f;
const float precioPruebaPresion = 350.0f;
const float precioLavado = 160.0f ;
const float iva = 0.16f;


/**
 * ANTES DE ASIGNAR UN TICKET AL USUARIO, ASEGURATE DE QUE TENGA UNA CULATA ASIGNADA,
 * ASI VERIFICAS QUE SE HIZO ALGUN TRABAJO EN EL TALLER Y PODRAS COBRAR
 * if (motor->culata == NULL){
        imprimirMensaje(10,10,"ESTE MOTOR NO TIENE ASIGNADO UNA CULATA");
    }
 * @return
 */
int pago(){
    const int id_usuario = obtenerIdSiExisteUsuario(10,10);
    RETURN_IF_ESC(id_usuario);

    clear();
    //NECESARIO PARA NO AGREGAR VALORES NULL Y CAUSAR ERRORES DESPUES AL ASIGNAR TICKETS
    Motor* motor = obtenerMotorByIdUsuario(id_usuario);
    if (!motor) {
        mvprintw(10, 10, "No se encontró ninguna pieza asociada al usuario con ID %d", id_usuario);
        getch();
        return -1;
    }
    if (motor->culata == NULL){
        imprimirMensaje(10,10,"ESTE MOTOR NO TIENE ASIGNADO UNA CULATA -> No puedes crear tickets");
        return -1;
    }

    Ticket ticket = inicializarTicket(obtenerUsuarioByIdUsuario(id_usuario), motor, NULL, NULL);
    // Solo si el ticket es NULL va a guardar el ticket (uno nuevo)
    if (obtenerTicketByIdUsuario(id_usuario) == NULL){
        if (ticket.usuario->motor->culata->operacionesMotor == -1 || ticket.usuario->motor->culata->operacionesMotor == -2){
            clear();
            mvprintw(5,5,"El estado actual de la pieza es: %s  \nPorfavor, ve al apartado de Operaciones en Servicio", estadoPiezaTexto(ticket.usuario->motor->culata->operacionesMotor));
            getch();
            return -1;
        }
        if (guardarTicket(ticket) != 1){
            imprimirMensaje(20,10,"X Error al crear los ticket's. Inténtelo de nuevo.");
            return -1;
        }
        //Q desverge hice, la logica es la siguiente
        /**
         * 1 obtener el usuario si existe, si no existe retorna NULL
         * 2 inicializa el ticket, asignandole usuario y motor AL TICKET
         * 3 Busca si algun ticket TIENE el mismo ID que el usuario de este contexto, si devuelve NULL obtenerTicketByIdUsuario(), significa que el usuario no tiene un ticket
         * 4 Buscamos si el motor / culata tiene operaciones por realizar
         * 5 se guarda el ticket, el ticket previamente
         */

        mvprintw(5,10,"¡Ordenes de pago creadas correctamente - Presione enter !");
        getch();
    }



    const int opcUsr = mostrarMenu(14,"Porfavor selecciona una opcion");
    RETURN_IF_ESC(opcUsr);

    char* nombreArchivo = NULL;
    const char* nombresOperaciones[] = {"Nota","Ticket","Factura"};
    FILE* archivo = NULL;

    switch (opcUsr) {
    case 0: {

            nombreArchivo = obtenerNombreArchivo(nombresOperaciones[0]);
            archivo = fopen(nombreArchivo, "w");
            RETURN_IF_ESC(generarNota(id_usuario, archivo));
            break;
    }
    case 1: {
            nombreArchivo = obtenerNombreArchivo(nombresOperaciones[1]);
            archivo = fopen(nombreArchivo, "w");
            RETURN_IF_ESC(generarTicket(id_usuario, archivo));
            break;
    }
    case 2: {
            nombreArchivo = obtenerNombreArchivo(nombresOperaciones[2]);
            archivo = fopen(nombreArchivo, "w");
            RETURN_IF_ESC(generarFactura(id_usuario, archivo));
            break;
    }
    case 3: {
            clear();
            imprimirDetallesTicket(id_usuario, 1);
            break;
    }
    default: {
            mvprintw(10, 10, "Opcion no valida, Intente de nuevo -> Ticket");
            clear();
            getch();
            break;
    }
    }
    // cerrar si fue abierto
    if (archivo != NULL) fclose(archivo);
    if (nombreArchivo != NULL) free(nombreArchivo);


    return 0;
}

int generarNota(int id_usuario, FILE *archivo) {
    if (!archivo) return -1; // Verificar que el archivo sea válido

    Ticket *ticket = obtenerTicketByIdUsuario(id_usuario);

    if (ticket == NULL) {
        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "ERROR: Ticket no encontrado\n");
        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "No existe un ticket vinculado al ID ingresado.\n");
        return -1;
    }

    if (ticket->detalles == NULL && ticket->detalles2 == NULL) {
        char *detalles = leerStringSeguro(10, 5, 255, "Ingrese detalles de la operación para OPCION NOTA -MAX 255 & MIN 1 caracter-");
        char *detalles2 = leerStringSeguro(13, 5, 255, "Ingrese detalles adicionales -MAX 255 & MIN 1 caracter-");
        if (detalles == NULL || detalles2 == NULL) {
            fprintf(archivo, "Ocurrió un error al crear la nota, intente de nuevo\n");
            return -1;
        }
        ticket->detalles = detalles;
        ticket->detalles2 = detalles2;
    }

    fprintf(archivo, "==============================================\n");
    fprintf(archivo, "NOTA DE OPERACION\n");
    fprintf(archivo, "==============================================\n");
    fprintf(archivo, "Le Atendio:  %s \n\n", empleado);
    fprintf(archivo, "Detalles proporcionados:\n\n");
    fprintf(archivo, "Nombre del Cliente: %s\n", ticket->usuario->nombreUsuario);
    fprintf(archivo, "Fabricante del motor: %s\n", ticket->usuario->motor->fabricante);
    fprintf(archivo, "Numero de serie: %s\n", ticket->usuario->motor->numeroSerie);
    fprintf(archivo, "Material del motor: %s\n\n", ticket->usuario->motor->material);

    fprintf(archivo, "Detalles:\n");
    imprimirTextoMultilineaArchivo(archivo, ticket->detalles, 60);
    fprintf(archivo, "\nDetalles adicionales:\n");
    imprimirTextoMultilineaArchivo(archivo, ticket->detalles2, 60);
    fprintf(archivo, "----------------------------------------------\n");

    return 1;
}

int generarTicket(int id_usuario, FILE *archivo) {
    if (!archivo) return -1; // Verificar que el archivo sea válido

    Ticket *ticket = obtenerTicketByIdUsuario(id_usuario);

    if (ticket == NULL) {
        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "ERROR: Ticket no encontrado\n");
        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "No existe un ticket vinculado al ID ingresado.\n");
        return -1;
    }

    Usuario *usr = ticket->usuario;
    Motor *motor = ticket->usuario->motor;

    if (motor == NULL) {
        fprintf(archivo, "Motor no asignado. No se puede generar el ticket.\n");
        return -1;
    }

    // Simulación de precios
    float precioFinalEstadoPieza = 0;
    if (motor->culata->operacionesMotor == 1) {
        precioFinalEstadoPieza = precioRectificado;
    } else if (motor->culata->operacionesMotor == 2) {
        precioFinalEstadoPieza = precioReconstruccion;
    }
    const float precioFinalPruebaPresion = (motor->culata != NULL) ? precioPruebaPresion : 0.0f;
    const float precioFinalLavado = ticket->lavado ? precioLavado : 0.0f;
    const float subtotal = precioFinalEstadoPieza + precioFinalPruebaPresion + precioFinalLavado;
    const float impuesto = subtotal * iva;
    const float total = subtotal + impuesto;

    fprintf(archivo, "==================================================\n");
    fprintf(archivo, "TICKET DE SERVICIO - Le Atendio: %s\n", empleado);
    fprintf(archivo, "ID USUARIO: %d\n", usr->id_usuario);
    fprintf(archivo, "==================================================\n");
    fprintf(archivo, "Cliente: %s %s\n", usr->nombreUsuario, usr->apellido);
    fprintf(archivo, "Folio: %s\n", usr->folio);
    fprintf(archivo, "Contacto: %s\n", usr->contacto);
    fprintf(archivo, "Email: %s\n", usr->email);
    fprintf(archivo, "Celular: %lld\n\n", usr->celular);

    fprintf(archivo, "---------------- DATOS DEL MOTOR -----------------\n");
    fprintf(archivo, "Nombre: %s\n", motor->modelo);
    fprintf(archivo, "Fabricante: %s\n", motor->fabricante);
    fprintf(archivo, "Serie: %s\n", motor->numeroSerie);
    fprintf(archivo, "Combustible: %s\n", tipoCombustibleToStr(motor->tipoCombustible));
    fprintf(archivo, "Tipo: %s\n", motor->culata != NULL ? "Culata" : "Culata no asignada");
    fprintf(archivo, "Material: %s\n", motor->material);
    fprintf(archivo, "Medida Original: %.2f mm\n", motor->medidaOriginal);
    fprintf(archivo, "Medida Actual: %.2f mm\n", motor->medidaActual);
    fprintf(archivo, "Estado de la Pieza: %s\n", estadoPiezaTexto(motor->culata->operacionesMotor));

    if (motor->culata != NULL) {
        fprintf(archivo, "N° Válvulas: %d\n", motor->culata->numValvulas);
        fprintf(archivo, "Presión Prueba: %.2f bar\n", motor->culata->presionPrueba);
        fprintf(archivo, "Fisuras: %s\n", motor->culata->tieneFisuras ? "Sí" : "No");
    }

    fprintf(archivo, "\n----------------- RESUMEN DE COSTOS ------------------\n");
    fprintf(archivo, "Estado de la Pieza: %s\n", estadoPiezaTexto(motor->culata->operacionesMotor));
    const char *estado = estadoPiezaTexto(motor->culata->operacionesMotor);
    fprintf(archivo, "Trabajo requerido - %s: $ %.2f\n", estado, precioFinalEstadoPieza);
    fprintf(archivo, "Prueba de Presión:   $ %.2f\n", precioFinalPruebaPresion);
    fprintf(archivo, "Lavado de motor:     $ %.2f\n", precioFinalLavado);
    fprintf(archivo, "------------------------------------------------------\n");
    fprintf(archivo, "Subtotal:            $ %.2f\n", subtotal);
    fprintf(archivo, "IVA (16%%):           $ %.2f\n", impuesto);
    fprintf(archivo, "TOTAL:               $ %.2f\n", total);
    fprintf(archivo, "==================================================\n");

    return 1;
}

int generarFactura(int id_usuario, FILE *archivo) {
    if (!archivo) return -1; // Verificar que el archivo sea válido

    Ticket *ticket = obtenerTicketByIdUsuario(id_usuario);

    if (ticket == NULL) {
        fprintf(archivo, "==================================================\n");
        fprintf(archivo, "FACTURA NO DISPONIBLE: Ticket no encontrado\n");
        fprintf(archivo, "==================================================\n");
        fprintf(archivo, "No existe información fiscal asociada al usuario.\n");
        return -1;
    }

    Usuario *usr = ticket->usuario;
    Motor *motor = ticket->usuario->motor;

    if (motor == NULL) {
        fprintf(archivo, "Motor no asignado al usuario. No se puede facturar.\n");
        return -1;
    }

    // Generar fecha actual
    time_t t = time(NULL);
    struct tm fecha = *localtime(&t);

    // Simulación de precios
    float precioFinalEstadoPieza = 0;
    if (motor->culata->operacionesMotor == 1) {
        precioFinalEstadoPieza = precioRectificado;
    } else if (motor->culata->operacionesMotor == 2) {
        precioFinalEstadoPieza = precioReconstruccion;
    }
    const float precioFinalPruebaPresion = (motor->culata != NULL) ? precioPruebaPresion : 0.0f;
    const float precioFinalLavado = ticket->lavado ? precioLavado : 0.0f;
    const float subtotal = precioFinalEstadoPieza + precioFinalPruebaPresion + precioFinalLavado;
    const float impuesto = subtotal * iva;
    const float total = subtotal + impuesto;

    fprintf(archivo, "============================================================");
    fprintf(archivo, "FACTURA ELECTRÓNICA DE SERVICIO AUTOMOTRIZ\n");
    fprintf(archivo, "============================================================");
    fprintf(archivo, "Folio Interno: %s\n", usr->folio);
    fprintf(archivo, "Fecha Emisión: %02d/%02d/%04d %02d:%02d\n",
            fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900,
            fecha.tm_hour, fecha.tm_min);
    fprintf(archivo, "RFC Cliente: CLI890123XYZ\n"); // Ficticio
    fprintf(archivo, "Nombre Cliente: %s %s\n", usr->nombreUsuario, usr->apellido);
    fprintf(archivo, "Correo: %s\n", usr->email);
    fprintf(archivo, "Domicilio Fiscal: Calle Ficticia 123, Ciudad Ejemplo, MX\n");
    fprintf(archivo, "------------------------------------------------------------\n");
    fprintf(archivo, "Descripción del Servicio:\n");

    if (motor->culata->operacionesMotor == 1)
        fprintf(archivo, "  - Rectificación de pieza               $ %.2f\n", precioFinalEstadoPieza);
    if (motor->culata->operacionesMotor == 2)
        fprintf(archivo, "  - Reconstrucción de pieza              $ %.2f\n", precioFinalEstadoPieza);
    if (motor->culata != NULL)
        fprintf(archivo, "  - Prueba de presión en culata          $ %.2f\n", precioFinalPruebaPresion);
    fprintf(archivo, "  - Lavado general                       $ %.2f\n", precioFinalLavado);
    fprintf(archivo, "\n");

    fprintf(archivo, "------------------------------------------------------------\n");
    fprintf(archivo, "Subtotal:                              $ %.2f\n", subtotal);
    fprintf(archivo, "IVA (16%%):                             $ %.2f\n", impuesto);
    fprintf(archivo, "TOTAL A PAGAR:                         $ %.2f\n, ", total);
    fprintf(archivo, "============================================================");
    fprintf(archivo, "Condiciones de pago: Contado\n");
    fprintf(archivo, "Forma de pago: Efectivo / Transferencia\n");
    fprintf(archivo, "Uso CFDI: G03 - Gastos en general\n");
    fprintf(archivo, "Método de pago: PUE - Pago en una sola exhibición\n");
    fprintf(archivo, "============================================================");
    fprintf(archivo, "Gracias por confiar en nuestros servicios.\n");

    return 1;
}

void imprimirDetallesTicket(int id_usuario, int fila){
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

            if (motor == NULL) {
                mvprintw(fila++, 2, "Motor: No asignado.");
                getch();
                return;
            }

            imprimirDetallesMotor(motor);

            //mvprintw(fila++, 2, "Rectificacion: %s", motor->necesitaRectificacion ? "Si" : "No");
            mvprintw(fila++, 2, "Lavado?: %s", arrayTickets.datos[i].lavado ? "Si" : "No");

            if (motor->culata != NULL) {
                mvprintw(fila++, 4, "----------- CULATA -----------");
                mvprintw(fila++, 4, "Numero Valvulas: %d", culata->numValvulas);
                mvprintw(fila++, 4, "Presion de Prueba: %.2f bar", culata->presionPrueba);
                mvprintw(fila++, 4, "Fisuras: %s", culata->tieneFisuras ? "Si" : "No");
                mvprintw(fila++, 2, "Estado de la Pieza: %s", estadoPiezaTexto(culata->operacionesMotor));
            } else if (motor->monoblock != NULL) {
                mvprintw(fila++, 4, "---------- MONOBLOCK ---------");
                mvprintw(fila++, 4, "Numero Cilindros: %d", monoblock->numCilindros);
                mvprintw(fila++, 4, "Diametro: %.2f mm", monoblock->diametroCilindro);
                mvprintw(fila++, 4, "Ovalizacion: %.2f mm", monoblock->ovalizacion_max);
                mvprintw(fila++, 4, "Desalineacion: %.2f mm", monoblock->desalineacion_bancadas);
                mvprintw(fila++, 2, "Estado de la Pieza: %s", estadoPiezaTexto(monoblock->estado_diagnostico));
            }

            mvprintw(fila++, 4, "==============================================");
            mvprintw(fila++, 10, "Presiona cualquier tecla para continuar...");
            getch();
            return;
        }
    }
}

//  FALTA AGREGAR MAS COSAS PARA IMPRIMIR
// CADA VEZ QUE LLAME A ESTA FUNCION DEBO CERRAR EL ARCHIVO CON fclose(archivo);
int exportarDetallesTickets(const char* nombreArchivo, FILE* archivo) {
    if (!archivo) {
        perror("No se pudo abrir el archivo");
        return -1;
    }

    fprintf(archivo, "EXPORTANDO DETALLES DE TODOS LOS TICKETS\n");
    fprintf(archivo, "Tamaño del array: %d\n\n", arrayTickets.tamanno);

    for (int i = 0; i < arrayTickets.tamanno; i++) {
        Usuario* usr = arrayTickets.datos[i].usuario;
        if (!usr) continue;

        Ticket* ticket = obtenerTicketByIdUsuario(usr->id_usuario);
        if (!ticket) {
            fprintf(stderr, "ERROR: Ticket no encontrado para el usuario ID %d\n", usr->id_usuario);
            continue;
        }

        Motor* motor = usr->motor;

        // Validación de motor
        if (!motor) {
            fprintf(stderr, "ERROR: Motor no asignado para usuario ID %d. No se puede exportar.\n", usr->id_usuario);
            continue;
        }

        // Simulación de precios
        float precioFinalEstadoPieza = 0;
        if (motor->culata && motor->culata->operacionesMotor == 1) {
            precioFinalEstadoPieza = precioRectificado;
        } else if (motor->culata && motor->culata->operacionesMotor == 2) {
            precioFinalEstadoPieza = precioReconstruccion;
        }

        const float precioFinalPruebaPresion = (motor->culata != NULL) ? precioPruebaPresion : 0.0f;
        const float precioFinalLavado = ticket->lavado ? precioLavado : 0.0f;
        const float subtotal = precioFinalEstadoPieza + precioFinalPruebaPresion + precioFinalLavado;
        const float impuesto = subtotal * iva;
        const float total = subtotal + impuesto;

        fprintf(archivo, "==================================================\n");
        fprintf(archivo, "TICKET DE SERVICIO - ID USUARIO: %d\n", usr->id_usuario);
        fprintf(archivo, "==================================================\n");

        fprintf(archivo, "Cliente: %s %s\n", usr->nombreUsuario, usr->apellido);
        fprintf(archivo, "Folio: %s\n", usr->folio);
        fprintf(archivo, "Contacto: %s\n", usr->contacto);
        fprintf(archivo, "Email: %s\n", usr->email);
        fprintf(archivo, "Celular: %lld\n", usr->celular);
        fprintf(archivo, "\n");

        fprintf(archivo, "---------------- DATOS DEL MOTOR -----------------\n");
        fprintf(archivo, "Nombre: %s\n", motor->modelo);
        fprintf(archivo, "Fabricante: %s\n", motor->fabricante);
        fprintf(archivo, "Serie: %s\n", motor->numeroSerie);
        fprintf(archivo, "Combustible: %s\n", tipoCombustibleToStr(motor->tipoCombustible));
        fprintf(archivo, "Tipo: %s\n", motor->culata != NULL ? "Culata" : "Culata no asignada");
        fprintf(archivo, "Material: %s\n", motor->material);
        fprintf(archivo, "Medida Original: %.2f mm\n", motor->medidaOriginal);
        fprintf(archivo, "Medida Actual: %.2f mm\n", motor->medidaActual);
        if (motor->culata) {
            fprintf(archivo, "Estado de la Pieza: %s\n", estadoPiezaTexto(motor->culata->operacionesMotor));
            fprintf(archivo, "N° Válvulas: %d\n", motor->culata->numValvulas);
            fprintf(archivo, "Presión Prueba: %.2f bar\n", motor->culata->presionPrueba);
            fprintf(archivo, "Fisuras: %s\n", motor->culata->tieneFisuras ? "Sí" : "No");
        }

        fprintf(archivo, "\n----------------- RESUMEN DE COSTOS ------------------\n");
        if (motor->culata)
            fprintf(archivo, "Estado de la Pieza: %s\n", estadoPiezaTexto(motor->culata->operacionesMotor));
        const char* estado = motor->culata ? estadoPiezaTexto(motor->culata->operacionesMotor) : "No definido";
        fprintf(archivo, "Trabajo requerido - %s: $ %.2f\n", estado, precioFinalEstadoPieza);
        fprintf(archivo, "Prueba de Presión:   $ %.2f\n", precioFinalPruebaPresion);
        fprintf(archivo, "Lavado de motor:     $ %.2f\n", precioFinalLavado);
        fprintf(archivo, "------------------------------------------------------\n");
        fprintf(archivo, "Subtotal:            $ %.2f\n", subtotal);
        fprintf(archivo, "IVA (16%%):           $ %.2f\n", impuesto);
        fprintf(archivo, "TOTAL:               $ %.2f\n", total);
        fprintf(archivo, "==================================================\n\n");
    }

    //printf("Archivo generado exitosamente: %s\n", nombreArchivo);
    return 1;
}



// 0 = Verificación (no se requiere nada)
// 1 = Rectificación
// 2 = Reconstrucción
const char* estadoPiezaTexto(int estadoPieza) {
    switch (estadoPieza) {
    case -2: return "Falta trabajo en la pieza, (Reconstruccion) ve al apartado de Servicio-Operaciones";
    case -1: return "Falta trabajo en la pieza, (Rectificacion) ve al apartado de Servicio-Operaciones";
    case 1: return "Rectificación";
    case 2: return "Reconstrucción";
    default: return "Verificación";
    }
}