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
#include "ConstantesMotores.h"
#include "Util.h"
//Variable encapsulada -> Private
int id_UsuarioGlobal = 0;
int id_piezaGlobal = 0;
//int id_Pieza = 0;
// Declaración global de array's
ArrayUsuarios arrayUsuarios = {0};
ArrayTickets arrayTickets = {0};  // ← variable global
ArrayList array_list;
ArrayPiezas arrayMotoresPrecargados = {0};
ArrayPiezas arrayMotoresUsuarios = {0};
ArrayPiezas arrayPiezas = {0};


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
 * @param params
 * @param paramsmotor
 * @param id_usuario,
 * @param id_pieza,
 * @param numero_serie
 * @param tipoDePieza
 * @param tipoPieza -> MONOBLOCK = 0, CULATA = 1.
 *
 */
Motor* inicializarMotor(Paramsmotor params, const int id_usuario, const int id_pieza, void* tipoDePieza, const int tipoPieza) {
    Motor* pz = (Motor*)malloc(sizeof(Motor));
    if (pz == NULL) {
        perror("Error al asignar memoria para Motor");
        exit(EXIT_FAILURE);
    }

    // Inicialización básica
    pz->id_usuario = id_usuario;
    pz->id_pieza = id_pieza;
    pz->tipoCombustible = params.tipoCombustible;
    //Deprecated
    //pz->tipoPieza = params.tipoPieza;

    // Copiar cadenas de texto
    asignString(pz->material, params.material, sizeof(pz->material));
    pz->modelo = params.modelo;
    pz->fabricante = params.fabricante;
    pz->carroAsociado = params.carroAsociado;
    pz->numeroSerie = params.numeroSerie;
    // Datos técnicos
    pz->anno = params.anno;
    pz->cilindrada = params.cilindrada;
    pz->compresionOriginal = params.compresionOriginal;
    /*
    pz->desgaste = params.desgaste;
    pz->tolerancia = params.tolerancia;
    */
    pz->medidaOriginal = params.medidaOriginal;
    pz->medidaActual = params.medidaActual;


    pz->culata = NULL;
    pz->monoblock = NULL;


    return pz;
}

Culata* inicializarCulata(int id_pieza , int numValvulas, double presionPrueba,int fisuras,
    float alturaOriginal, float alturaActual, float alturaMinima, int id_usuario, int estadoPieza){

    //Variables que estan en Culata
    Culata* culata = malloc(sizeof(Culata));
    if (culata == NULL) {
    perror("Error al asignar memoria para Culata");
    exit(EXIT_FAILURE);
    }
    culata->id_usuario = id_usuario;
    culata->id_pieza = id_pieza;
    culata->numValvulas = numValvulas;
    culata->presionPrueba = presionPrueba;
    culata->tieneFisuras = fisuras;
    culata->alturaOriginal = alturaOriginal;
    culata->alturaActual = alturaActual;
    culata->alturaMinima = alturaMinima;
    culata->estadoPieza = estadoPieza;
    //Sumar 1 al contador de piezas globales
    id_piezaGlobal++;
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

int guardarMotorArray(void* motor, const int id_usuario) {
    if (arrayMotoresUsuarios.tamanno >= arrayMotoresUsuarios.capacidad) {
        // Si la capacidad está llena, redimensionamos el arreglo
        const int nuevaCapacidad = arrayMotoresUsuarios.capacidad == 0 ? 1 : arrayMotoresUsuarios.capacidad * 2;
        //void* nuevoArray = (Motor*) realloc(arrayMotores.datos, nuevaCapacidad * sizeof(void*));
        void* nuevoArray = realloc(arrayMotoresUsuarios.datos, nuevaCapacidad * sizeof(void*));
        if (nuevoArray == NULL) {
            printf("Error al redimensionar el array de Piezas.\n");
            return -1;  // Si realloc falla, retornar error
        }
        arrayMotoresUsuarios.datos = nuevoArray;  // Asignar el nuevo arreglo redimensionado
        arrayMotoresUsuarios.capacidad = nuevaCapacidad; // Actualizar la capacidad
    }
    arrayMotoresUsuarios.datos[arrayMotoresUsuarios.tamanno] = motor;  // Guardar puntero al motor
    arrayMotoresUsuarios.tamanno++;  // Incrementar el número de elementos
    //Agregar Id Usuario generico por cada motor
    arrayMotoresUsuarios.id_usuario = id_usuario;
    return 1;  // Éxito
}

int guardarPiezaArray(void* pieza, int id_usuario) {
    if (arrayPiezas.tamanno >= arrayPiezas.capacidad) {
        const int nuevaCapacidad = arrayPiezas.capacidad == 0 ? 1 : arrayPiezas.capacidad * 2;
        void** nuevoArray = realloc(arrayPiezas.datos, nuevaCapacidad * sizeof(void*));
        if (nuevoArray == NULL) {
            printf("Error al redimensionar el array de Piezas.\n");
            return -1;
        }
        arrayPiezas.datos = nuevoArray;
        arrayPiezas.capacidad = nuevaCapacidad;
    }
    arrayPiezas.datos[arrayPiezas.tamanno] = pieza;
    arrayPiezas.tamanno++;
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

Motor* obtenerMotorByIdUsuario(const int id) {
    for (int i = 0; i < arrayMotoresUsuarios.tamanno; i++) {
        Motor* motor = (Motor*)arrayMotoresUsuarios.datos[i]; // <-- Convertir el void* a Motor* CORRECTAMENTE
        if (motor->id_usuario == id) {
            return motor;  // Ya es un puntero, no necesitas &
        }
    }
    // Retorna NULL si no encuentra
    clear();
    mvprintw(12, 10, "X Motor no encontrado o ID de usuario inválido");
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
    mvprintw(12, 10, "El número de serie ingresado no coincide con ningún registro.");
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

int obtenerIdSiExisteUsuario(const int POS_Y, const int POS_X){
    const int id_usuario = leerIntSeguro(POS_Y,POS_X,10000,"Ingrese Id Usuario: ");
    RETURN_IF_ESC(id_usuario);
    const Usuario* usuario = obtenerUsuarioByIdUsuario(id_usuario);
    if (usuario == NULL) {
        /*
         *mvprintw(15,10,"Usuario no encontrado con el ID %d", id_usuario);
        getch();
        */
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

    for (size_t i = 0; i < arrayMotoresUsuarios.tamanno; i++) {
        Motor* pieza = (Motor*) arrayMotoresUsuarios.datos[i];
        fila++;
        mvprintw(fila++, 2, "ID Pieza: %d", pieza->id_pieza);
        mvprintw(fila++, 2, "ID Usuario: %d", pieza->id_usuario);
        mvprintw(fila++, 2, "Nombre del Motor: %s", pieza->modelo);
        mvprintw(fila++, 2, "Fabricante: %s", pieza->fabricante);
        mvprintw(fila++, 2, "Cilindrada: %.2f L", pieza->cilindrada);
        mvprintw(fila++, 2, "Compresión Original: %.2f psi", pieza->compresionOriginal);
        mvprintw(fila++, 2, "Número de Serie: %s", pieza->numeroSerie);
        mvprintw(fila++, 2, "Tipo de Combustible: %s", tipoCombustibleToStr(pieza->tipoCombustible));
        mvprintw(fila++, 2, "Material: %s", pieza->material);
        /*
        mvprintw(fila++, 2, "Desgaste: %.2f%%", pieza->desgaste * 100.0f);
        mvprintw(fila++, 2, "Tolerancia: %.4f mm", pieza->tolerancia);
        */
        mvprintw(fila++, 2, "Medida Original: %.4f mm", pieza->medidaOriginal);
        mvprintw(fila++, 2, "Medida Actual: %.4f mm", pieza->medidaActual);


        if (pieza->culata != NULL) {
            mvprintw(fila++, 4, "Tipo de Pieza: Culata");
            mvprintw(fila++, 4, "N° Válvulas: %d", pieza->culata->numValvulas);
            mvprintw(fila++, 4, "Presión Prueba: %.2f bar", pieza->culata->presionPrueba);
            mvprintw(fila++, 4, "Tiene Fisuras: %s", pieza->culata->tieneFisuras ? "Sí" : "No");
            mvprintw(fila++, 4, "Estado de la Pieza: %s", estadoPiezaTexto(pieza->culata->estadoPieza));
        } else if (pieza->monoblock != NULL) {
            Monoblock* monoblock = (Monoblock*)pieza;
            mvprintw(fila++, 4, "Tipo de Pieza: Monoblock");
            mvprintw(fila++, 4, "N° Cilindros: %d", monoblock->numCilindros);
            mvprintw(fila++, 4, "Diámetro Cilindros: %.2f mm", monoblock->diametroCilindro);
            mvprintw(fila++, 4, "Alineación Cigüeñal: %.2f mm", monoblock->alineacionCiguenal);
            mvprintw(fila++, 4, "Estado de la Pieza: %s", estadoPiezaTexto(monoblock->estadoPieza));
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
    id_UsuarioGlobal = nuevoId;
};
int getIdUsuarioLogico(){
    return id_UsuarioGlobal;
};