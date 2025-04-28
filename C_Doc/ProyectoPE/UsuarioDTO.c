//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//

#include "UsuarioDTO.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LogicaNegocio.h"
#include "UserInterface.h"
#include "Util.h"
//Variable encapsulada -> Private
int id_UsuarioLogico = 0;
//int id_Pieza = 0;
// Declaración global de array's
ArrayUsuarios arrayUsuarios = {0};
ArrayTickets arrayTickets = {0};  // ← variable global
ArrayList array_list;
ArrayPiezas arrayPiezas;


//Funciones Importantes para la ejecucion detodo el programa y evitar la reutilizacion de codigo

Usuario inicializarUsuario(const int id_usuario,const char* folio , const char* nombreUsuario, const char* apellido,
                           long long celular, const char* email, const char* contacto) {
    Usuario usr = {0}; // Inicializa la estructura en 0 para evitar datos basura
    usr.id_usuario = id_usuario;
    asignString(usr.folio, folio, sizeof(usr.folio));
    asignString(usr.nombreUsuario, nombreUsuario, sizeof(usr.nombreUsuario));
    asignString(usr.apellido, apellido, sizeof(usr.apellido));
    usr.celular = celular;
    asignString(usr.email, email, sizeof(usr.email));
    asignString(usr.contacto, contacto, sizeof(usr.contacto));

    usr.motor = NULL;
    usr.activo = 1;
    //Adiciona 1 al ID usuario desde aqui para que el usuario nunca tenga el mismo ID sin importar si es valido el usuario o no
    setIdUsuarioLogico(getIdUsuarioLogico() + 1);
    return usr;
}

/**
 * Solo se pasaran commo variables estaticas
 * Las variables que no pertenecen unicamente del motor
 * @param motor
 * @param id_usuario,
 * @param id_pieza,
 * @param numero_serie
 * @param tipoDePieza
 * @param numTipoDepieza
 */
Motor* inicializarMotor(Paramsmotor motor, const int id_usuario, const int id_pieza, const char* numero_serie, void* tipoDePieza, const int numTipoDepieza){
    Motor* pz = malloc(sizeof(Motor));

    // Culata 1, Monoblock 2
    //Si se quiere acceder a estos campos sin haberles asignado un valor, causara segfault
    if (numTipoDepieza == 1){
        pz->culata = (Culata*) tipoDePieza;
    }else{
        pz->culata = NULL;
    }

    if (numTipoDepieza == 2){
        pz->monoblock = (Monoblock*) tipoDePieza;
    }else{
        pz->monoblock = NULL;
    }

    pz->tipoCombustible = motor.tipoCombustible;
    asignString(pz->material, motor.material, sizeof(pz->material));
    pz->desgaste = motor.desgaste;
    pz->tolerancia = motor.tolerancia;
    pz->medidaOriginal = motor.medidaOriginal;
    pz->medidaActual = motor.medidaActual;
    pz->necesitaRectificacion = motor.necesitaRectificacion;
    pz->nombre = motor.nombre;
    pz->fabricante = motor.fabricante;
    pz->cilindrada = motor.cilindrada;
    pz->compresionOriginal = motor.compresionOriginal;

    pz->id_usuario = id_usuario;
    pz->id_pieza = id_pieza;
    pz->numeroSerie = numero_serie;

    return pz;
}

Culata* inicializarCulata(const int numValvulas ,const double presionPrueba
                /** const int tipoCombustible */, const int fisuras){
    Culata* culata = malloc(sizeof(Culata));
    if (culata == NULL) {
    perror("Error al asignar memoria para Culata");
    exit(EXIT_FAILURE);
    }

    /*
    culata->motor.tipoPieza = CULATA;  // ← ¡Necesario!
    culata->motor = pieza;
    */

    culata->numValvulas = numValvulas;
    culata->presionPrueba = presionPrueba;
    //culata->base.tipoCombustible = tipoCombustible;
    culata->tieneFisuras = fisuras;
    return culata;
}

// Función para agregar un usuario a la lista
int guardarUsuarioArray(Usuario usuario) {
    if (arrayUsuarios.tamanno >= arrayUsuarios.capacidad) {
        const int nuevaCapacidad = arrayUsuarios.capacidad == 0 ? 1 : arrayUsuarios.capacidad * 2;
        Usuario* nuevoArray = realloc(arrayUsuarios.datos, nuevaCapacidad * sizeof(Usuario));
        if (nuevoArray == NULL) {
            printf("Error al redimensionar el array de usuarios.\n");
            return -1;
        }
        arrayUsuarios.datos = nuevoArray;
        arrayUsuarios.capacidad = nuevaCapacidad;
    }
    arrayUsuarios.datos[arrayUsuarios.tamanno] = usuario;
    arrayUsuarios.tamanno++;
    return 1; // Retorna 1 si se guardó correctamente
}

int guardarPiezaArray(void* motor, const int id_usuario) {
    if (arrayPiezas.tamanno >= arrayPiezas.capacidad) {
        // Si la capacidad está llena, redimensionamos el arreglo
        const int nuevaCapacidad = arrayPiezas.capacidad == 0 ? 1 : arrayPiezas.capacidad * 2;
        void** nuevoArray = realloc(arrayPiezas.datos, nuevaCapacidad * sizeof(void*));
        if (nuevoArray == NULL) {
            printf("Error al redimensionar el array de Piezas.\n");
            return -1;  // Si realloc falla, retornar error
        }
        arrayPiezas.datos = nuevoArray;  // Asignar el nuevo arreglo redimensionado
        arrayPiezas.capacidad = nuevaCapacidad; // Actualizar la capacidad
    }
    arrayPiezas.datos[arrayPiezas.tamanno] = motor;  // Guardar puntero al motor
    arrayPiezas.tamanno++;  // Incrementar el número de elementos
    //Agregar Id Usuario generico por cada motor
    arrayPiezas.id_usuario = id_usuario;
    return 1;  // Éxito
}

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
            //mostrarUsuario(arrayUsuarios.datos[i]);
            return &arrayUsuarios.datos[i];
        }
    }
    // Retorna NULL si el usuario no existe
    mvprintw(12, 10, "Usuario no encontrado o no corresponde a un numero de ID");
    getch();
    return NULL;
}

void* obtenerPiezaByIdUsuario(const int id) {
    for (int i = 0; i < arrayPiezas.tamanno; i++) {
        Motor* pieza = (Motor*) arrayPiezas.datos[i];  // cast seguro
        if (pieza->id_usuario == id) {
            return pieza;  // Retorna el puntero a la pieza
        }
    }

    // Retorna NULL si el usuario no existe
    mvprintw(12, 10, "X Pieza no encontrada o ID de usuario inválido");
    getch();
    return NULL;
}

int guardarTicket(Ticket ticket){
    if (arrayTickets.tamanno >= arrayTickets.capacidad){
        const int nuevaCapacidad = arrayTickets.capacidad == 0 ? 1 : arrayTickets.capacidad * 2;
        Ticket* nuevoArray = realloc(arrayTickets.datos, nuevaCapacidad * sizeof(Ticket));
        if (nuevoArray == NULL) {
            printf("Error al redimensionar el array de tickets.\n");
            return -1;
        }
        arrayTickets.datos = nuevoArray;
        arrayTickets.capacidad = nuevaCapacidad;
    }
    arrayTickets.datos[arrayTickets.tamanno] = ticket;
    arrayTickets.tamanno++;
    return 1;
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

int obtenerIdSiExisteUsuario(){
    const int id_usuario = leerIntSeguro(6,10,10000,"Ingrese Id Usuario: ");
    RETURN_IF_ESC(id_usuario);

    Usuario* usuario = obtenerUsuarioByIdUsuario(id_usuario);
    if (usuario == NULL) {
        mvprintw(15,10,"️ Usuario no encontrado.");
        getch();
        return -1;
    }
    return id_usuario;
}

const char* tipoCombustibleToStr(TipoCombustible tipo) {
    switch (tipo) {
    case GASOLINA: return "Gasolina";
    case DIESEL:   return "Diesel";
    case HIBRIDO:  return "Híbrido";
    default:       return "Desconocido";
    }
}

void listarPiezas(){
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int fila = 1;
    mvprintw(fila++, 10, "==============================================");
    mvprintw(fila++, 15, "LISTADO DE TODAS LAS PIEZAS");
    mvprintw(fila++, 10, "==============================================");

    for (size_t i = 0; i < arrayPiezas.tamanno; i++) {
        Motor* pieza = (Motor*)arrayPiezas.datos[i];
        fila++;
        mvprintw(fila++, 2, "ID Pieza: %d", pieza->id_pieza);
        mvprintw(fila++, 2, "ID Usuario: %d", pieza->id_usuario);
        mvprintw(fila++, 2, "Nombre del Motor: %s", pieza->nombre);
        mvprintw(fila++, 2, "Fabricante: %s", pieza->fabricante);
        mvprintw(fila++, 2, "Cilindrada: %.2f L", pieza->cilindrada);
        mvprintw(fila++, 2, "Compresión Original: %.2f psi", pieza->compresionOriginal);
        mvprintw(fila++, 2, "Número de Serie: %s", pieza->numeroSerie);
        mvprintw(fila++, 2, "Tipo de Combustible: %s", tipoCombustibleToStr(pieza->tipoCombustible));
        mvprintw(fila++, 2, "Material: %s", pieza->material);
        mvprintw(fila++, 2, "Desgaste: %.2f%%", pieza->desgaste * 100.0f);
        mvprintw(fila++, 2, "Tolerancia: %.4f mm", pieza->tolerancia);
        mvprintw(fila++, 2, "Medida Original: %.4f mm", pieza->medidaOriginal);
        mvprintw(fila++, 2, "Medida Actual: %.4f mm", pieza->medidaActual);
        mvprintw(fila++, 2, "¿Rectificar?: %s", pieza->necesitaRectificacion ? "Sí" : "No");

        if (pieza->culata != NULL) {
            Culata* culata = (Culata*)pieza;
            mvprintw(fila++, 4, "Tipo de Pieza: Culata");
            mvprintw(fila++, 4, "N° Válvulas: %d", culata->numValvulas);
            mvprintw(fila++, 4, "Presión Prueba: %.2f bar", culata->presionPrueba);
            mvprintw(fila++, 4, "Tiene Fisuras: %s", culata->tieneFisuras ? "Sí" : "No");
        } else if (pieza->monoblock != NULL) {
            Monoblock* monoblock = (Monoblock*)pieza;
            mvprintw(fila++, 4, "Tipo de Pieza: Monoblock");
            mvprintw(fila++, 4, "N° Cilindros: %d", monoblock->numCilindros);
            mvprintw(fila++, 4, "Diámetro Cilindros: %.2f mm", monoblock->diametroCilindro);
            mvprintw(fila++, 4, "Alineación Cigüeñal: %.2f mm", monoblock->alineacionCiguenal);
        }

        mvprintw(fila++, 10, "----------------------------------------------");

        if (fila >= LINES - 5) {
            mvprintw(fila++, 10, "Presiona cualquier tecla para continuar...");
            getch();
            clear();
            fila = 1;
        }
    }

    mvprintw(fila++, 10, "Fin del listado...");
    getch();
}

void listarFoliosUsuarios(){
    int y = 3;
    for (int i = 0; i < arrayUsuarios.tamanno; i++) {
        mvprintw(y, 40, "Activo?: %s", arrayUsuarios.datos[i].activo ? "True" : "False");
        mvprintw(y, 60, "ID: %d", arrayUsuarios.datos[i].id_usuario);
        mvprintw(y, 70, "Nombre: %s", arrayUsuarios.datos[i].nombreUsuario);
        mvprintw(y, 90, "Folio: %s", arrayUsuarios.datos[i].folio);

        y++; // Dejar una línea en blanco entre registros
    }
}

void mostrarUsuario(Usuario usr) {
    mvprintw(10,10,"ID Usuario: %d\n", usr.id_usuario);
    mvprintw(10,11,"Folio Usuario: %s\n", usr.folio);
    mvprintw(10,12, "Activo?: %d", usr.activo);
    mvprintw(10,13,"Nombre: %s\n", usr.nombreUsuario);
    mvprintw(10,14,"Apellido: %s\n", usr.apellido);
    mvprintw(10,15,"Celular: %lld\n", usr.celular);
    mvprintw(10,16,"Email: %s\n", usr.email);
    mvprintw(10,17,"Contacto: %s\n", usr.contacto);
}

//Getters y setters
void setIdUsuarioLogico(const int nuevoId){
    id_UsuarioLogico = nuevoId;
};
int getIdUsuarioLogico(){
    return id_UsuarioLogico;
};