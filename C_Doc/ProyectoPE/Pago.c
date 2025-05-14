//Pago
#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>

#include "UsuarioDTO.h"
#include "Util.h"
#include "LogicaNegocio.h"
#include "UserInterface.h"


const float precioRectificadoCulata = 850.0f;
const float precioReconstruccionCulata = 1200.f;
const float precioRectificacionMonoblock = 1100.0f;
const float precioReconstruccionMonoblock = 1500.0f;
const float precioPruebaPresion = 350.0f;
const float precioLavado = 160.0f;
const float iva = 0.16f;


int pago() {
    const int id_usuario = obtenerIdSiExisteUsuario(10, 10);
    RETURN_IF_ESC(id_usuario);

    clear();
    Motor *motor = obtenerMotorByIdUsuario(id_usuario);
    if (!motor) {
        mvprintw(10, 10, "No se encontró ninguna pieza asociada al usuario con ID %d", id_usuario);
        getch();
        return -1;
    }
    if (motor->culata == NULL && motor->monoblock == NULL) {
        imprimirMensaje(10, 10, "ESTE MOTOR NO TIENE ASIGNADO NI CULATA NI MONOBLOCK"
                        " -> No puedes crear tickets");
        getch();
        return -1;
    }

    Ticket ticket = inicializarTicket(obtenerUsuarioByIdUsuario(id_usuario), motor, NULL, NULL);
    if (obtenerTicketByIdUsuario(id_usuario) == NULL) {
        int operacion = 0;
        if (motor->culata != NULL && motor->culata->operacionesMotor != -1 && motor->culata->operacionesMotor != -2) {
            operacion = 1;
        } else if (motor->monoblock != NULL && motor->monoblock->operacionesMotor != -1 && motor->monoblock->
                   operacionesMotor != -2) {
            operacion = 1;
        }

        if (!operacion) {
            clear();
            const char *estado_texto = "No disponible";
            if (motor->culata != NULL) {
                estado_texto = estadoPiezaTexto(motor->culata->operacionesMotor);
            } else if (motor->monoblock != NULL) {
                estado_texto = estadoPiezaTexto(motor->monoblock->operacionesMotor);
            }
            mvprintw(5, 5, "El estado actual de la pieza es: %s\nPor favor, ve al apartado de Operaciones en Servicio",
                     estado_texto);
            getch();
            return -1;
        }

        if (guardarTicket(ticket) != 1) {
            imprimirMensaje(20, 10, "X Error al crear los ticket's. Inténtelo de nuevo.");
            getch();
            return -1;
        }

        mvprintw(5, 10, "¡Ordenes de pago creadas correctamente - Presione enter !");
        getch();
    }

    const int opcUsr = mostrarMenu(14, "Por favor selecciona una opción");
    RETURN_IF_ESC(opcUsr);

    char *nombreArchivo = NULL;
    const char *nombresOperaciones[] = {"Nota", "Ticket", "Factura"};
    FILE *archivo = NULL;

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
            mvprintw(10, 10, "Opción no válida, Intente de nuevo -> Ticket");
            clear();
            getch();
            break;
        }
    }

    if (archivo != NULL) fclose(archivo);
    if (nombreArchivo != NULL) free(nombreArchivo);

    return 0;
}

int generarNota(int id_usuario, FILE *archivo) {
    if (!archivo) return -1;

    Ticket *ticket = obtenerTicketByIdUsuario(id_usuario);
    if (ticket == NULL) {
        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "ERROR: Ticket no encontrado\n");
        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "No existe un ticket vinculado al ID ingresado.\n");
        return -1;
    }

    Usuario *usr = ticket->usuario;
    if (usr == NULL) {
        fprintf(archivo, "Usuario no asignado. No se puede generar la nota.\n");
        mvprintw(10, 10, "Error: Usuario no asignado para el ticket.");
        getch();
        return -1;
    }

    Motor *motor = usr->motor;
    if (motor == NULL) {
        fprintf(archivo, "Motor no asignado. No se puede generar la nota.\n");
        mvprintw(10, 10, "Error: Motor no asignado para el usuario.");
        getch();
        return -1;
    }


    if (ticket->detalles == NULL && ticket->detalles2 == NULL) {
        char *detalles = leerStringSeguro(
            10, 5, 255, "Ingrese detalles de la operación para OPCION NOTA -MAX 255 & MIN 1 caracter-");
        char *detalles2 = leerStringSeguro(13, 5, 255, "Ingrese detalles adicionales -MAX 255 & MIN 1 caracter-");
        if (detalles == NULL || detalles2 == NULL) {
            fprintf(archivo, "Ocurrió un error al crear la nota, intente de nuevo\n");
            mvprintw(10, 10, "Error: No se pudieron ingresar los detalles de la nota.");
            getch();
            free(detalles);
            free(detalles2);
            return -1;
        }
        ticket->detalles = detalles;
        ticket->detalles2 = detalles2;
    }


    fprintf(archivo, "==============================================\n");
    fprintf(archivo, "NOTA DE OPERACIÓN\n");
    fprintf(archivo, "==============================================\n");
    fprintf(archivo, "Le Atendió: %s\n", empleado ? empleado : "No especificado");
    fprintf(archivo, "ID Usuario: %d\n\n", usr->id_usuario);

    fprintf(archivo, "---------------- DATOS DEL CLIENTE ----------------\n");
    fprintf(archivo, "Nombre: %s %s\n", usr->nombreUsuario, usr->apellido);
    fprintf(archivo, "Folio: %s\n", usr->folio);

    fprintf(archivo, "\n---------------- DATOS DEL MOTOR -----------------\n");
    fprintf(archivo, "Fabricante: %s\n", motor->fabricante ? motor->fabricante : "No disponible");
    fprintf(archivo, "Número de Serie: %s\n", motor->numeroSerie ? motor->numeroSerie : "No disponible");
    fprintf(archivo, "Material: %s\n", motor->material ? motor->material : "No disponible");
    fprintf(archivo, "Modelo: %s\n", motor->modelo ? motor->modelo : "No disponible");

    fprintf(archivo, "\n---------------- DETALLES DE LA OPERACIÓN --------\n");
    fprintf(archivo, "Detalles:\n");
    imprimirTextoMultilineaArchivo(archivo, ticket->detalles ? ticket->detalles : "No proporcionado", 60);
    fprintf(archivo, "\nDetalles Adicionales:\n");
    imprimirTextoMultilineaArchivo(archivo, ticket->detalles2 ? ticket->detalles2 : "No proporcionado", 60);
    fprintf(archivo, "==============================================\n");

    return 1;
}

int generarTicket(int id_usuario, FILE *archivo) {
    if (!archivo) return -1;

    Ticket *ticket = obtenerTicketByIdUsuario(id_usuario);
    if (ticket == NULL) {
        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "ERROR: Ticket no encontrado\n");
        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "No existe un ticket vinculado al ID ingresado.\n");
        return -1;
    }

    Usuario *usr = ticket->usuario;
    if (usr == NULL) {
        fprintf(archivo, "Usuario no asignado. No se puede generar el ticket.\n");
        return -1;
    }

    Motor *motor = usr->motor;
    if (motor == NULL) {
        fprintf(archivo, "Motor no asignado. No se puede generar el ticket.\n");
        return -1;
    }


    float precioCulata = 0.0f;
    float precioMonoblock = 0.0f;
    const char *estadoCulata = "No asignada";
    const char *estadoMonoblock = "No asignada";


    if (motor->culata != NULL) {
        if (motor->culata->operacionesMotor == 1) {
            precioCulata = precioRectificadoCulata;
            estadoCulata = estadoPiezaTexto(motor->culata->operacionesMotor);
        } else if (motor->culata->operacionesMotor == 2) {
            precioCulata = precioReconstruccionCulata;
            estadoCulata = estadoPiezaTexto(motor->culata->operacionesMotor);
        }
    }


    if (motor->monoblock != NULL) {
        if (motor->monoblock->estado_diagnostico == 1) {
            precioMonoblock = precioRectificacionMonoblock;
            estadoMonoblock = estadoPiezaTexto(motor->monoblock->operacionesMonoblock);
        } else if (motor->monoblock->estado_diagnostico == 2) {
            precioMonoblock = precioReconstruccionMonoblock;
            estadoMonoblock = estadoPiezaTexto(motor->monoblock->operacionesMonoblock);
        }
    }

    const float precioFinalPruebaPresion = (motor->culata != NULL) ? precioPruebaPresion : 0.0f;
    const float precioFinalLavado = ticket->lavado ? precioLavado : 0.0f;
    const float subtotal = precioCulata + precioMonoblock + precioFinalPruebaPresion + precioFinalLavado;
    const float impuesto = subtotal * iva;
    const float total = subtotal + impuesto;


    fprintf(archivo, "==================================================\n");
    fprintf(archivo, "TICKET DE SERVICIO - Le Atendió: %s\n", empleado);
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
    fprintf(archivo, "Material: %s\n", motor->material);
    fprintf(archivo, "Medida Original: %.2f mm\n", motor->medidaOriginal);
    fprintf(archivo, "Medida Actual: %.2f mm\n", motor->medidaActual);

    fprintf(archivo, "\n---------------- DATOS DE CULATA -----------------\n");
    if (motor->culata != NULL) {
        fprintf(archivo, "Tipo: Culata\n");
        fprintf(archivo, "Estado: %s\n", estadoCulata);
        fprintf(archivo, "N° Válvulas: %d\n", motor->culata->numValvulas);
        fprintf(archivo, "Presión Prueba: %.2f bar\n", motor->culata->presionPrueba);
        fprintf(archivo, "Fisuras: %s\n", motor->culata->tieneFisuras ? "Sí" : "No");
    } else {
        fprintf(archivo, "Culata: No asignada\n");
    }

    fprintf(archivo, "\n---------------- DATOS DE MONOBLOCK --------------\n");
    if (motor->monoblock != NULL) {
        fprintf(archivo, "Tipo: Monoblock\n");
        fprintf(archivo, "Estado: %s\n", estadoMonoblock);
        fprintf(archivo, "N° Cilindros: %d\n", motor->monoblock->numCilindros);
        fprintf(archivo, "N° Serie: %s\n", motor->monoblock->numero_serie);
        fprintf(archivo, "Bancadas: %d\n", motor->monoblock->num_bancadas);
        fprintf(archivo, "Planitud Superficie: %.2f mm\n", motor->monoblock->planitud_superficie);
    } else {
        fprintf(archivo, "Monoblock: No asignado\n");
    }

    fprintf(archivo, "\n----------------- RESUMEN DE COSTOS ------------------\n");
    if (motor->culata != NULL) {
        fprintf(archivo, "Trabajo en Culata (%s): $ %.2f\n", estadoCulata, precioCulata);
    }
    if (motor->monoblock != NULL) {
        fprintf(archivo, "Trabajo en Monoblock (%s): $ %.2f\n", estadoMonoblock, precioMonoblock);
    }
    fprintf(archivo, "Prueba de Presión: $ %.2f\n", precioFinalPruebaPresion);
    fprintf(archivo, "Lavado de motor: $ %.2f\n", precioFinalLavado);
    fprintf(archivo, "------------------------------------------------------\n");
    fprintf(archivo, "Subtotal: $ %.2f\n", subtotal);
    fprintf(archivo, "IVA (%.0f%%): $ %.2f\n", iva * 100, impuesto);
    fprintf(archivo, "TOTAL: $ %.2f\n", total);
    fprintf(archivo, "==================================================\n");

    return 1;
}

int generarFactura(int id_usuario, FILE *archivo) {
    if (!archivo) return -1;

    Ticket *ticket = obtenerTicketByIdUsuario(id_usuario);
    if (ticket == NULL) {
        fprintf(archivo, "==================================================\n");
        fprintf(archivo, "FACTURA NO DISPONIBLE: Ticket no encontrado\n");
        fprintf(archivo, "==================================================\n");
        fprintf(archivo, "No existe información fiscal asociada al usuario.\n");
        mvprintw(10, 10, "Error: No se encontró ticket para el usuario ID %d", id_usuario);
        getch();
        return -1;
    }

    Usuario *usr = ticket->usuario;
    if (usr == NULL) {
        fprintf(archivo, "Usuario no asignado. No se puede facturar.\n");
        mvprintw(10, 10, "Error: Usuario no asignado para el ticket.");
        getch();
        return -1;
    }

    Motor *motor = usr->motor;
    if (motor == NULL) {
        fprintf(archivo, "Motor no asignado al usuario. No se puede facturar.\n");
        mvprintw(10, 10, "Error: Motor no asignado para el usuario.");
        getch();
        return -1;
    }

    time_t t = time(NULL);
    struct tm fecha = *localtime(&t);

    float precioCulata = 0.0f;
    float precioMonoblock = 0.0f;
    const char *estadoCulata = "No asignada";
    const char *estadoMonoblock = "No asignada";

    if (motor->culata != NULL) {
        if (motor->culata->operacionesMotor == 1) {
            precioCulata = precioRectificadoCulata;
            estadoCulata = estadoPiezaTexto(motor->culata->operacionesMotor);
        } else if (motor->culata->operacionesMotor == 2) {
            precioCulata = precioReconstruccionCulata;
            estadoCulata = estadoPiezaTexto(motor->culata->operacionesMotor);
        }
    }

    if (motor->monoblock != NULL) {
        if (motor->monoblock->estado_diagnostico == 1) {
            precioMonoblock = precioRectificacionMonoblock;
            estadoMonoblock = estadoPiezaTexto(motor->monoblock->estado_diagnostico);
        } else if (motor->monoblock->estado_diagnostico == 2) {
            precioMonoblock = precioReconstruccionMonoblock;
            estadoMonoblock = estadoPiezaTexto(motor->monoblock->estado_diagnostico);
        }
    }

    const float precioFinalPruebaPresion = (motor->culata != NULL) ? precioPruebaPresion : 0.0f;
    const float precioFinalLavado = ticket->lavado ? precioLavado : 0.0f;
    const float subtotal = precioCulata + precioMonoblock + precioFinalPruebaPresion + precioFinalLavado;
    const float impuesto = subtotal * iva;
    const float total = subtotal + impuesto;

    fprintf(archivo, "============================================================\n");
    fprintf(archivo, "FACTURA ELECTRÓNICA DE SERVICIO AUTOMOTRIZ\n");
    fprintf(archivo, "============================================================\n");
    fprintf(archivo, "Folio Interno: %s\n", usr->folio);
    fprintf(archivo, "Fecha Emisión: %02d/%02d/%04d %02d:%02d\n",
            fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900,
            fecha.tm_hour, fecha.tm_min);
    fprintf(archivo, "RFC Cliente: %s\n", "CLI890123XYZ");
    fprintf(archivo, "Nombre Cliente: %s %s\n", usr->nombreUsuario, usr->apellido);
    fprintf(archivo, "Correo: %s\n", usr->email);

    fprintf(archivo, "------------------------------------------------------------\n");
    fprintf(archivo, "Descripción del Servicio:\n");

    if (motor->culata != NULL && motor->culata->operacionesMotor == 1) {
        fprintf(archivo, "  - Rectificación de culata              $ %.2f\n", precioCulata);
    } else if (motor->culata != NULL && motor->culata->operacionesMotor == 2) {
        fprintf(archivo, "  - Reconstrucción de culata             $ %.2f\n", precioCulata);
    }
    if (motor->monoblock != NULL && motor->monoblock->estado_diagnostico == 1) {
        fprintf(archivo, "  - Rectificación de monoblock           $ %.2f\n", precioMonoblock);
    } else if (motor->monoblock != NULL && motor->monoblock->estado_diagnostico == 2) {
        fprintf(archivo, "  - Reconstrucción de monoblock          $ %.2f\n", precioMonoblock);
    }
    if (motor->culata != NULL) {
        fprintf(archivo, "  - Prueba de presión en culata          $ %.2f\n", precioFinalPruebaPresion);
    }
    if (ticket->lavado) {
        fprintf(archivo, "  - Lavado general                       $ %.2f\n", precioFinalLavado);
    }
    fprintf(archivo, "\n");

    fprintf(archivo, "------------------------------------------------------------\n");
    fprintf(archivo, "Subtotal:                              $ %.2f\n", subtotal);
    fprintf(archivo, "IVA (%.0f%%):                          $ %.2f\n", iva * 100, impuesto);
    fprintf(archivo, "TOTAL A PAGAR:                         $ %.2f\n", total);
    fprintf(archivo, "============================================================\n");
    fprintf(archivo, "Condiciones de pago: Contado\n");
    fprintf(archivo, "Forma de pago: Efectivo / Transferencia\n");
    fprintf(archivo, "Uso CFDI: G03 - Gastos en general\n");
    fprintf(archivo, "Método de pago: PUE - Pago en una sola exhibición\n");
    fprintf(archivo, "============================================================\n");
    fprintf(archivo, "Gracias por confiar en nuestros servicios.\n");

    return 1;
}

void imprimirDetallesTicket(int id_usuario, int fila) {
    mvprintw(fila++, 4, "IMPRIMIR DETALLES TICKET USUARIO ON");
    mvprintw(fila++, 4, "Tamanno array %d", arrayTickets.tamanno);

    for (int i = 0; i < arrayTickets.tamanno; i++) {
        if (arrayTickets.datos[i].usuario->id_usuario == id_usuario) {
            Usuario *usr = arrayTickets.datos[i].usuario;

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

            Motor *motor = usr->motor;
            Culata *culata = usr->motor->culata;
            Monoblock *monoblock = usr->motor->monoblock;

            if (motor == NULL) {
                mvprintw(fila++, 2, "Motor: No asignado.");
                getch();
                return;
            }

            imprimirDetallesMotor(motor);

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

                mvprintw(fila++, 4, "Ovalizacion: %.2f mm", monoblock->ovalizacion_max);

                mvprintw(fila++, 2, "Estado de la Pieza: %s", estadoPiezaTexto(monoblock->estado_diagnostico));
            }

            mvprintw(fila++, 4, "==============================================");
            mvprintw(fila++, 10, "Presiona cualquier tecla para continuar...");
            getch();
            return;
        }
    }
}


int exportarDetallesTickets(const char *nombreArchivo, FILE *archivo) {
    if (!archivo) {
        perror("No se pudo abrir el archivo");
        return -1;
    }

    fprintf(archivo, "EXPORTANDO DETALLES DE TODOS LOS TICKETS\n");
    fprintf(archivo, "Tamaño del array: %d\n\n", arrayTickets.tamanno);

    for (int i = 0; i < arrayTickets.tamanno; i++) {
        Usuario *usr = arrayTickets.datos[i].usuario;
        if (!usr) continue;

        Ticket *ticket = obtenerTicketByIdUsuario(usr->id_usuario);
        if (!ticket) {
            fprintf(stderr, "ERROR: Ticket no encontrado para el usuario ID %d\n", usr->id_usuario);
            continue;
        }

        Motor *motor = usr->motor;


        if (!motor) {
            fprintf(stderr, "ERROR: Motor no asignado para usuario ID %d. No se puede exportar.\n", usr->id_usuario);
            continue;
        }


        float precioFinalEstadoPieza = 0;
        if (motor->culata && motor->culata->operacionesMotor == 1) {
            precioFinalEstadoPieza = precioRectificadoCulata;
        } else if (motor->culata && motor->culata->operacionesMotor == 2) {
            precioFinalEstadoPieza = precioReconstruccionCulata;
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
        const char *estado = motor->culata ? estadoPiezaTexto(motor->culata->operacionesMotor) : "No definido";
        fprintf(archivo, "Trabajo requerido - %s: $ %.2f\n", estado, precioFinalEstadoPieza);
        fprintf(archivo, "Prueba de Presión:   $ %.2f\n", precioFinalPruebaPresion);
        fprintf(archivo, "Lavado de motor:     $ %.2f\n", precioFinalLavado);
        fprintf(archivo, "------------------------------------------------------\n");
        fprintf(archivo, "Subtotal:            $ %.2f\n", subtotal);
        fprintf(archivo, "IVA (16%%):           $ %.2f\n", impuesto);
        fprintf(archivo, "TOTAL:               $ %.2f\n", total);
        fprintf(archivo, "==================================================\n\n");
    }


    return 1;
}


const char *estadoPiezaTexto(int estadoPieza) {
    switch (estadoPieza) {
        case -2: return "Falta trabajo en la pieza, (Reconstruccion) ve al apartado de Servicio-Operaciones";
        case -1: return "Falta trabajo en la pieza, (Rectificacion) ve al apartado de Servicio-Operaciones";
        case 1: return "Rectificación";
        case 2: return "Reconstrucción";
        default: return "Verificación";
    }
}
