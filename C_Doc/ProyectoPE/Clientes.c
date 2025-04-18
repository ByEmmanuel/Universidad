//
// Created by Jesus Emmanuel Garcia on 4/18/25.
//

#include "UsuarioDTO.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LogicaNegocio.h"
#include "Escape.h"
#include "Util.h"
#include "LogicaNegocio.h"
#include "UsuarioDTO.h"



int cliente(){
    //Funcion que crea a los clientes
    //Agregar valores (Todo en un String A una lista)

    // MENU CLIENTE
    int opcCliente = mostrarMenu(2,".") + 1;
    char* emailUsr;
    clear();
    refresh();


    if (opcCliente == 4) {
        return 1;  // Volver al menú principal
    }
    if (opcCliente == 1) {
        cleanScreen();
        clear();
        mvprintw(1,10,"Agregar Cliente");
        const char* nombreUsr = leerStringSeguro(3, 0, 19,"Ingrese Nombre: ");
        if (nombreUsr == NULL) {
            return -1;
        }
        mvprintw(6, 10, "                                                 ");
        const char* folio = generarFolio(nombreUsr);
        const char* apellidoUsr = leerStringSeguro(6, 0, 19,"Ingrese Apellido: ");
        if (apellidoUsr == NULL) {
            return -1;
        }
        mvprintw(9, 10, "                                                 ");
        const int celularUsr = leerIntSeguro(10, 0, 15,"Ingrese Celular: ");
        mvprintw(12, 10, "                                                 ");
        emailUsr = leerStringSeguro(12, 0, 49, "Ingrese Email: ");
        if (emailUsr == NULL) {
            return -1;
        }
        mvprintw(15, 10, "                                                 ");
        const char* contactoUsr = leerStringSeguro(15, 0, 29,"Ingrese Contacto: ");
        if (contactoUsr == NULL) {
            return -1;
        }
        mvprintw(18, 10, "                                                 ");

        while (!strContains(emailUsr, "@")) {
            if (mostrarMenu(7,"Tu Email no es valido, ¿Deseas volver a ingresarlo?") == 1){
                clear();
                emailUsr = leerStringSeguro(11,12,49,"Ingrese Email");
                if (emailUsr == NULL) {
                    return -1;
                }
            } else {
                mvprintw(10,13,"Registro INVÁLIDO: Email Inválido");
                getch();
                return 1;
            }
        }

        const Usuario usuario = inicializarUsuario(id_UsuarioLogico, folio, nombreUsr, apellidoUsr, celularUsr, emailUsr, contactoUsr);
        mostrarUsuario(usuario);
        guardarUsuarioArray(usuario);
        clear();
        mvprintw(10,13,"Registro Correcto, Presione Enter");
        getch();

    } else if (opcCliente == 2){
        modificarCliente();
    }else if (opcCliente == 3) {  // Listar Clientes
        cleanScreen();
        if (arrayUsuarios.capacidad == 0) {
            printf("No hay clientes registrados.\n");
        } else {
            int y = 2;
            for (int i = 0; i < arrayUsuarios.total; i++) {
                mvprintw(y++, 1, "ID: %d", arrayUsuarios.datos[i].id_usuario);
                mvprintw(y++, 1, "Folio: %s", arrayUsuarios.datos[i].folio);
                mvprintw(y++, 1, "Activo?: %d", arrayUsuarios.datos[i].activo);
                mvprintw(y++, 1, "Nombre: %s", arrayUsuarios.datos[i].nombreUsuario);
                mvprintw(y++, 1, "Apellido: %s", arrayUsuarios.datos[i].apellido);
                mvprintw(y++, 1, "Celular: %lld", arrayUsuarios.datos[i].celular);
                mvprintw(y++, 1, "Email: %s", arrayUsuarios.datos[i].email);
                mvprintw(y++, 1, "Contacto: %s", arrayUsuarios.datos[i].contacto);
                y++; // Dejar una línea en blanco entre registros
            }
            getch();
            return 1;
        }
        mvprintw(10, 10, "Capacidad En El arrayUsuarios: %d", arrayUsuarios.capacidad);
        mvprintw(10, 10, "\nPresiona ENTER para continuar...");
        getchar();  // Pausa antes de limpiar la pantalla
    }
    cleanScreen();
    //mvprintw(10, 10, "Saliendo opcCliente");
    return 1;
}