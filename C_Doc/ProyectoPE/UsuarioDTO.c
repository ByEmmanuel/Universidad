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

int id_UsuarioLogico = 0;
//int id_Pieza = 0;
ArrayUsuarios arrayUsuarios;
ArryTickets arrayTickets;
ArrayList array_list;
ArrayPiezas arrayPiezas;
// Declaración global del array de usuarios


//Funciones Importantes para la ejecucion detodo el programa y evitar la reutilizacion de codigo
// strncpy,

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
    id_UsuarioLogico = id_UsuarioLogico + 1;
    return usr;
}

/**
 * Solo se pasaran commo variables estaticas
 * Las variables que no pertenecen unicamente del motor
 * @param id_usuario,
 * @param id_pieza,
 * @param numero_serie
 */
Motor inicializarMotor(Paramsmotor motor, const int id_usuario, const int id_pieza, const char* numero_serie){
    Motor pz = {0};

    pz.tipoCombustible = motor.tipoCombustible;
    pz.tipoPieza = motor.tipoPieza;
    asignString(pz.material, motor.material, sizeof(pz.material));
    pz.desgaste = motor.desgaste;
    pz.tolerancia = motor.tolerancia;
    pz.medidaOriginal = motor.medidaOriginal;
    pz.medidaActual = motor.medidaActual;
    pz.necesitaRectificacion = motor.necesitaRectificacion;
    pz.nombre = motor.nombre;
    pz.fabricante = motor.fabricante;
    pz.cilindrada = motor.cilindrada;
    pz.compresionOriginal = motor.compresionOriginal;

    pz.id_usuario = id_usuario;
    pz.id_pieza = id_pieza;
    pz.numeroSerie = numero_serie;

    return pz;
}

Culata* inicializarCulata(const Motor pieza, const int numValvulas ,const double presionPrueba
                /** const int tipoCombustible */, const int fisuras){
    Culata* culata = malloc(sizeof(Culata));
    if (culata == NULL) {
    perror("Error al asignar memoria para Culata");
    exit(EXIT_FAILURE);
    }
    culata->motor.tipoPieza = CULATA;  // ← ¡Necesario!
    culata->motor = pieza;
    culata->numValvulas = numValvulas;
    culata->presionPrueba = presionPrueba;
    //culata->base.tipoCombustible = tipoCombustible;
    culata->tieneFisuras = fisuras;
    return culata;
}

// Función para agregar un usuario a la lista
int guardarUsuarioArray(Usuario usuario) {
    if (arrayUsuarios.total >= arrayUsuarios.capacidad) {
        const int nuevaCapacidad = arrayUsuarios.capacidad == 0 ? 1 : arrayUsuarios.capacidad * 2;
        Usuario* nuevoArray = realloc(arrayUsuarios.datos, nuevaCapacidad * sizeof(Usuario));
        if (nuevoArray == NULL) {
            printf("Error al redimensionar el array de usuarios.\n");
            return -1;
        }
        arrayUsuarios.datos = nuevoArray;
        arrayUsuarios.capacidad = nuevaCapacidad;
    }
    arrayUsuarios.datos[arrayUsuarios.total] = usuario;
    arrayUsuarios.total++;
    return 1; // Retorna 1 si se guardó correctamente
}

int guardarPiezaArray(void* pieza) {
    if (arrayPiezas.tamaño >= arrayPiezas.capacidad) {
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
    arrayPiezas.datos[arrayPiezas.tamaño] = pieza;  // Guardar puntero a la pieza
    arrayPiezas.tamaño++;  // Incrementar el número de elementos
    return 0;  // Éxito
}

// Función para obtener un usuario por ID
Usuario* obtenerUsuarioById(const int id) {
    for (int i = 0; i < arrayUsuarios.total; i++) {
        if (arrayUsuarios.datos[i].id_usuario == id) {
            //mostrarUsuario(arrayUsuarios.datos[i]);
            return &arrayUsuarios.datos[i];
        }
    }
    // Retorna NULL si el usuario no existe
    mvprintw(12, 10, "Usuario no encontrado O no corresponde a un numero de ID");
    getch();
    return NULL;
}

void modificarCliente(){
    cleanScreen();
    clear();
    int id_Cliente = leerIntSeguro(11, 15, 2,"Ingrese ID, Folio o Numero de Cliente: ");

    //Esta funcion puede ser contraproducente ya que si algun campo del objeto Usuario, esta vacio,
    //esta opcion nunca va a funcionar
    cleanScreen();
    Usuario* usuarioNuevo = obtenerUsuarioById(id_Cliente);
    if (usuarioNuevo == NULL) {
        mvprintw(12,15,"Cliente no encontrado.\n");
        getch();
        return;
    }

    if (strIsEmpty(usuarioNuevo->nombreUsuario) || strIsEmpty(usuarioNuevo->email) || strIsEmpty(usuarioNuevo->nombreUsuario)) {
        mvprintw(12,15,"Cliente con datos incompletos.\n");
        getch();
        return;
    }

    mvprintw(0,0,"Debug: usuarioNuevo = %p", usuarioNuevo);
    refresh();
    mvprintw(1, 0, "usuarioNuevo: %p", usuarioNuevo);
    mvprintw(2, 1, "ID: %d", usuarioNuevo->id_usuario);
    mvprintw(3, 1, "Folio: %s", usuarioNuevo->folio);
    mvprintw(4, 1, "Nombre: %s", usuarioNuevo->nombreUsuario);
    mvprintw(5, 1, "Apellido: %s", usuarioNuevo->apellido);
    mvprintw(6, 1, "Celular: %lld", usuarioNuevo->celular);
    mvprintw(7, 1, "Email: %s", usuarioNuevo->email);
    mvprintw(8, 1, "Contacto: %s", usuarioNuevo->contacto);
    refresh();

    const int opcUsr = mostrarMenu(3,".") + 1;

    //char reemplazoUsuario[50]; // Buffer para almacenar entrada
    char* reemplazoUsuario;
    //<cleanBuffer();

    switch (opcUsr) {
        case 1:
            clear();
            refresh();
            reemplazoUsuario = leerStringSeguro(10,15,50,"Ingrese nuevo Nombre: ");
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")) {
                asignString(usuarioNuevo->nombreUsuario, reemplazoUsuario, sizeof(usuarioNuevo->nombreUsuario));
                mvprintw(12,15,"Modificación realizada con éxito.\n");
                getch();
                break;
            }
            mvprintw(12,15,"Error al leer entrada.\n");
            break;
        case 2:
            clear();
            refresh();
            reemplazoUsuario = leerStringSeguro(10,15,50,"Ingrese nuevo Apellido: ");
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->apellido, reemplazoUsuario, sizeof(usuarioNuevo->apellido));
                mvprintw(12,15,"Modificación realizada con éxito.\n");
                getch();
                break;
            }
            printf("Error al leer entrada.\n");
            break;
        case 3:
            clear();
            refresh();
        usuarioNuevo->celular = leerIntSeguro(10,15,10,"Ingrese nuevo Número Celular: ");
            if (usuarioNuevo->celular != 0) mvprintw(12,15,"Modificación realizada con éxito.\n");
            getch();
            break;
        case 4:
            clear();
            refresh();
            reemplazoUsuario = leerStringSeguro(10,15,50,"Ingrese nuevo Email: ");
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->email, reemplazoUsuario, sizeof(usuarioNuevo->email));
                mvprintw(12,15,"Modificación realizada con éxito.\n");
                getch();
                break;
            };
            mvprintw(12,15,"Error al leer entrada.\n");
            getch();
            break;
        case 5:
            clear();
            refresh();
            reemplazoUsuario = leerStringSeguro(10,15,50,"Ingrese nuevo Contacto: ");
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->contacto, reemplazoUsuario, sizeof(usuarioNuevo->contacto));
                mvprintw(12,15,"Modificación realizada con éxito.\n");
                getch();
                break;
            };
            mvprintw(12,15,"Error al leer entrada.\n");
            getch();
            break;
        case 6:
            if (mostrarMenu(7, "¿Deseas eliminar a este usuario?") == 1) usuarioNuevo->activo = 0;
            asignString(usuarioNuevo->apellido, "0", sizeof(usuarioNuevo->apellido));
            usuarioNuevo->celular = 0;
            asignString(usuarioNuevo->contacto, "0", sizeof(usuarioNuevo->contacto));
            break;
        case 7:
            mvprintw(2, 10, "Saliendo del menú...");  // Muestra mensaje de depuración
            refresh();  // Asegúrate de que el mensaje se actualice
            return;
        default:
            mvprintw(12,15,"Opción inválida.\n");
            getch();
            return;
    }
    clear();
    refresh();
}

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
                if (arrayUsuarios.datos[i].motor != NULL) {
                    mvprintw(y++, 1, "Pieza: %s", arrayUsuarios.datos[i].motor->material);
                    //mvprintw(y++, 1, "Pieza: %s", arrayUsuarios.datos[i].motor->nombre);
                } else {
                    mvprintw(y++, 1, "Motor: (no asignada)");
                }
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

/**
 *
 * @deprecated
 */
void imprimirPiezasPorUsuario(int idUsuario) {
    printf("Piezas para el Usuario ID: %d\n", idUsuario);
    // Recorrer todas las piezas almacenadas
    for (int i = 0; i < arrayPiezas.tamaño; i++) {
        Motor* pieza = arrayPiezas.datos[i];  // Obtener puntero a la pieza

        // Verificar si el id_Usuario coincide
        if (pieza->id_usuario == idUsuario) {
            // Imprimir datos comunes de la pieza
            printf("ID Pieza: %d, Tipo: %d, Material: %s, Desgaste: %.2f%%\n",
                   pieza->id_pieza, pieza->tipoPieza, pieza->material, pieza->desgaste);

            // Si la pieza es una Culata
            if (pieza->tipoPieza == CULATA) {
                Culata* culata = (Culata*)pieza;  // Hacer cast a Culata

                printf("Tolerancia: %.2f,\n Medida Original: %.2f,\n Medida Actual: %.2f,\n Necesita Rectificacion: %d,\n"
                       "Número de válvulas: %d,\n Presión de prueba: %.2f,\n Combustible: %d,\n Tiene fisuras: %d,\n",
                       pieza->tolerancia, pieza->medidaOriginal, pieza->medidaActual, culata->numValvulas,
                       pieza->necesitaRectificacion, culata->presionPrueba, culata->motor.tipoCombustible,
                       culata->tieneFisuras);
            }
            // Si la pieza es un Monoblock
            else if (pieza->tipoPieza == MONOBLOCK) {
                Monoblock* monoblock = (Monoblock*)pieza;  // Hacer cast a Monoblock
                printf("Monoblock: Número de cilindros: %d, Diámetro del cilindro: %.2f, Ovalización: %.2f, Alineación cigüeñal: %.2f\n",
                       monoblock->numCilindros, monoblock->diametroCilindro, monoblock->ovalizacion, monoblock->alineacionCiguenal);
            }
            printf("\n");  // Línea en blanco entre piezas
        }
    }
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

    for (size_t i = 0; i < arrayPiezas.tamaño; i++) {
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

        if (pieza->tipoPieza == CULATA) {
            Culata* culata = (Culata*)pieza;
            mvprintw(fila++, 4, "Tipo de Pieza: Culata");
            mvprintw(fila++, 4, "N° Válvulas: %d", culata->numValvulas);
            mvprintw(fila++, 4, "Presión Prueba: %.2f bar", culata->presionPrueba);
            mvprintw(fila++, 4, "Tiene Fisuras: %s", culata->tieneFisuras ? "Sí" : "No");
        } else if (pieza->tipoPieza == MONOBLOCK) {
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
    for (int i = 0; i < arrayUsuarios.total; i++) {
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
