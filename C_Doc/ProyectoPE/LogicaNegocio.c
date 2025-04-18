//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include "LogicaNegocio.h"
#include "Escape.h"
#include "Util.h"
#include "UsuarioDTO.h"

//Aqui iría va la funcion cliente pero esta puesta en DTO USUARIO



int pago(){
    printf("Opcion pago ");
    return 0;
}

int almacen(){
    const int opcUsr = mostrarMenu(8, ".");
    RETURN_IF_ESC(opcUsr);
    switch (opcUsr){
    case 1:
        //const int opcUsrInventario = mostrarMenu(9,".");
        break;
    case 2:
        //const int opcUsrControl = mostrarMenu(10,".");
        break;
    case 3:
        //const int opcUsrHerramientas = mostrarMenu(11,".");
        break;
    case 4:
        //const int opcUsrProveedores = mostrarMenu(12,".");
        break;
    case 5:
        //const int opcUsrReportes = mostrarMenu(13,".");
        break;
    default:

        break;
    }
    return 0;
}

int otro(){
    printf("Opcion otro");
    return 0;
}

int dudas(){
    printf("Opcion Dudas");
    return 0;
}
// AQUI VAN LAS FUNCIONES QUE QUIERES QUE SE EJECUTEN ANTES DE QUE TERMINE EL PROGRAMA
int salir() {
    listarPiezas();
    exit(0);  // Finaliza el programa pero la terminal permanecerá abierta
}



void testing(int encendido) {
    if (encendido) {
        //usleep(200);
        printf("\n------TESTING MODE ON------");
        agregarUsuarios();
        agregarPiezas();
    }
}

void agregarUsuarios() {
    const Usuario usuario1 = inicializarUsuario(0,"00001", "Usuario1", "Apellido 1", 1234567890, "EmailPrueba1@1", "Contacto1");
    guardarUsuarioArray(usuario1);
    const Usuario usuario2 = inicializarUsuario(1,"00002", "Usuario2", "Apellido 2", 1987654321, "EmailPrueba2@2", "Contacto2");
    guardarUsuarioArray(usuario2);
}

void agregarPiezas() {
    Pieza piezaUsuario = inicializarPieza(0, 1, "Metal", .1123f, .1125f, .1300f, .1180f, 0);
    piezaUsuario.tipo = CULATA;
    Culata* pzc = inicializarCulata(piezaUsuario, 16, .10, 2,1);
    guardarPiezaArray((void*)pzc);  // Se guarda como puntero genérico

    Pieza piezaUsuario2 = inicializarPieza(1, 2, "Aluminio", 0.1000f, 0.1050f, 0.1250f, 0.1150f, 1);
    piezaUsuario2.tipo = CULATA;
    Culata* pzc2 = inicializarCulata(piezaUsuario2, 18, 0.12, 1, 0);
    guardarPiezaArray((void*)pzc2);
}