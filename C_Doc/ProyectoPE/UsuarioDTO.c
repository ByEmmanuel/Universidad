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
int id_Pieza = 0;
// Declaración global del array de usuarios
ArrayUsuarios arrayUsuarios;
ArryTickets arrayTickets;
ArrayList array_list;
ArrayPiezas arrayPiezas;

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

    usr.pieza = NULL;
    //Adiciona 1 al ID usuario desde aqui para que el usuario nunca tenga el mismo ID sin importar si es valido el usuario o no
    id_UsuarioLogico = id_UsuarioLogico + 1;
    return usr;
}
void asignarCulataUsuario(Usuario *usr, Culata* culata) {
    usr->pieza = (Pieza*) culata;
}
void asignarMonoblockUsuario(Usuario *usr, Monoblock* monoblock){
    usr->pieza = (Pieza*) monoblock;
}

Pieza inicializarPieza(const int id_Usuario, const int tipoPieza, const char* material, const float desgaste, float tolerancia,
                        const float medidaOriginal, const float medidaActual, const int necesitaRectificacion ){
    Pieza pz = {0};
    pz.id_Usuario = id_Usuario;
    pz.id_Pieza = id_Pieza;
    pz.tipo = tipoPieza;
    asignString(pz.material, material, sizeof(material));
    pz.desgaste = desgaste;
    pz.tolerancia = tolerancia;
    pz.medidaOriginal = medidaOriginal;
    pz.medidaActual = medidaActual;
    pz.necesitaRectificacion = necesitaRectificacion;

    return pz;
}

Culata inicializarCulata(const Pieza pieza, const int numValvulas ,const double presionPrueba,
                const int tipoCombustible, const int fisuras){
    Culata* culata = (Culata*)malloc(sizeof(Culata));
    culata->base = pieza;
    //culata.base.tipo = 1;
    //asignString(culata.base.material, material ,30);
    //culata.base.desgaste = desgaste;
    //culata.base.tolerancia = tolerancia;
    //culata.base.medidaOriginal = medidaOriginal;
    //culata.base.medidaActual = medidaActual;
    //culata.base.necesitaRectificacion = rectificacion;
    culata->numValvulas = numValvulas;
    culata->presionPrueba = presionPrueba;
    culata->tipoCombustible = tipoCombustible;
    culata->tieneFisuras = fisuras;
    // Agregar medidas manualmente
    return *culata;
}

// Función para agregar un usuario a la lista
int guardarUsuarioArray(Usuario usuario) {
    if (arrayUsuarios.total >= arrayUsuarios.capacidad) {
        int nuevaCapacidad = arrayUsuarios.capacidad == 0 ? 1 : arrayUsuarios.capacidad * 2;
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
        int nuevaCapacidad = arrayPiezas.capacidad == 0 ? 1 : arrayPiezas.capacidad * 2;
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
Usuario* obtenerUsuario(const int id) {
    cleanScreen();
    for (int i = 0; i < arrayUsuarios.total; i++) {
        if (arrayUsuarios.datos[i].id_usuario == id) {
            mostrarUsuario(arrayUsuarios.datos[i]);
            return &arrayUsuarios.datos[i];
        }
    }
    // Retorna NULL si el usuario no existe
    printf("Usuario no encontrado... Vuelve a intentar\n");
    return NULL;
}

void modificarCliente(){
    cleanScreen();
    printf("Ingrese ID, Folio o Numero de Cliente: ");
    int id_Cliente;
    scanf("%d", &id_Cliente);

    //Esta funcion puede ser contraproducente ya que si algun campo del objeto Usuario, esta vacio,
    //esta opcion nunca va a funcionar
    Usuario* usuarioNuevo = obtenerUsuario(id_Cliente);
    if (strIsEmpty(usuarioNuevo->nombreUsuario) || strIsEmpty(usuarioNuevo->email) || strIsEmpty(usuarioNuevo->nombreUsuario) || usuarioNuevo == NULL) {
        printf("Cliente no encontrado.\n");
        return;
    }

    //menuModificarCliente(0);
    int opcUsr;
    scanf("%d", &opcUsr);

    //char reemplazoUsuario[50]; // Buffer para almacenar entrada
    char* reemplazoUsuario;
    cleanBuffer();

    switch (opcUsr) {
        case 1:
            printf("Ingrese nuevo Nombre: ");
            reemplazoUsuario = cinString(50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")) {
                asignString(usuarioNuevo->nombreUsuario, reemplazoUsuario, sizeof(usuarioNuevo->nombreUsuario));
                printf("Modificación realizada con éxito.\n");
                break;
            }
            printf("Error al leer entrada.\n");
            break;
        case 2:
            printf("Ingrese nuevo Apellido: ");
            reemplazoUsuario = cinString(50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->apellido, reemplazoUsuario, sizeof(usuarioNuevo->apellido));
                printf("Modificación realizada con éxito.\n");
                break;
            }
            printf("Error al leer entrada.\n");
            break;
        case 3:
            printf("Ingrese nuevo Número Celular: ");
            long long numero;
            scanf("%9lld",&numero);
            if (numero != 0){
                usuarioNuevo->celular = numero;
                printf("Número guardado: %lld\n", usuarioNuevo->celular);
            }
            cleanBuffer();
            break;
        case 4:
            printf("Ingrese nuevo Email: ");
            reemplazoUsuario = cinString(50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->email, reemplazoUsuario, sizeof(usuarioNuevo->email));
                printf("Modificación realizada con éxito.\n");
                break;
            };
            printf("Error al leer entrada.\n");
            break;
        case 5:
            printf("Ingrese nuevo Contacto: ");
            reemplazoUsuario = cinString(50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->contacto, reemplazoUsuario, sizeof(usuarioNuevo->contacto));
                printf("Modificación realizada con éxito.\n");
                break;
            };
            printf("Error al leer entrada.\n");
            break;
        case 6:
            printf("Saliendo...\n");
            return;
        default:
            printf("Opción inválida.\n");
            return;
    }
}

int cliente(){
    //Funcion que crea a los clientes
    //Agregar valores (Todo en un String A una lista)

    // MENU CLIENTE
    int opcCliente = menuCliente();
    clear();
    refresh();


    if (opcCliente == 4) {
        return 1;  // Volver al menú principal
    }

    if (opcCliente == 1) {
        cleanScreen();
        clear();
        mvprintw(2, 10, "Agregar Cliente");
        mvprintw(4, 10, "Ingrese Nombre: ");
        char* nombreUsr = leerEntrada(4, 26, 19);
        char* folio = generarFolio(nombreUsr);
        mvprintw(5, 10, "Ingrese Apellido: ");
        char* apellidoUsr = leerEntrada(5, 28, 19);
        mvprintw(6, 10, "Ingrese Celular: ");
        char* celularStr = leerEntrada(6, 27, 15);
        long long celularUsr = atoll(celularStr);
        mvprintw(7, 10, "Ingrese Email: ");
        char* emailUsr = leerEntrada(7, 25, 49);
        mvprintw(8, 10, "Ingrese Contacto: ");
        char* contactoUsr = leerEntrada(8, 28, 29);


        while (!strContains(emailUsr, "@")) {
            free(emailUsr);
            mvprintw(10,10,"Tu Email no es valido, ¿Deseas volver a ingresarlo? 1: SI 2: NO");
            const char* opcUsr = leerEntrada(12,10,25);
            if (strContains(opcUsr, "1")) {
                mvprintw(10,10,"\033[2A\033[2K\033[1B\033[2K");
                clear();
                //fflush(stdout);
                mvprintw(10,12,"Ingrese Email\n");
                emailUsr = leerEntrada(11,12,49);
            } else {
                mvprintw(10,13,"Registro INVÁLIDO: Email Inválido\n");
                free(nombreUsr);
                free(folio);
                free(apellidoUsr);
                free(contactoUsr);
                return 1;
            }
        }

        Usuario usuario = inicializarUsuario(id_UsuarioLogico, folio, nombreUsr, apellidoUsr, celularUsr, emailUsr, contactoUsr);
        mostrarUsuario(usuario);
        guardarUsuarioArray(usuario);

        free(nombreUsr);
        free(folio);
        free(apellidoUsr);
        free(emailUsr);
        free(contactoUsr);

    } else if (opcCliente == 2){
        modificarCliente();
    }else if (opcCliente == 3) {  // Listar Clientes
        cleanScreen();
        if (arrayUsuarios.capacidad == 0) {
            printf("No hay clientes registrados.\n");
        } else {
            int y = 2;
            for (int i = 0; i < arrayUsuarios.capacidad; i++) {
                mvprintw(y++, 1, "ID: %d", arrayUsuarios.datos[i].id_usuario);
                mvprintw(y++, 1, "Folio: %s", arrayUsuarios.datos[i].folio);
                mvprintw(y++, 1, "Nombre: %s", arrayUsuarios.datos[i].nombreUsuario);
                mvprintw(y++, 1, "Apellido: %s", arrayUsuarios.datos[i].apellido);
                mvprintw(y++, 1, "Celular: %lld", arrayUsuarios.datos[i].celular);
                mvprintw(y++, 1, "Email: %s", arrayUsuarios.datos[i].email);
                mvprintw(y++, 1, "Contacto: %s", arrayUsuarios.datos[i].contacto);
                y++; // Dejar una línea en blanco entre registros
            }
        }
        mvprintw(10, 10, "Capacidad En El arrayUsuarios: %d", arrayUsuarios.capacidad);
        printf("\nPresiona ENTER para continuar...");
        getchar();  // Pausa antes de limpiar la pantalla
    }
    cleanScreen();
    return 1;
}

void imprimirPiezasPorUsuario(int idUsuario) {
    printf("Piezas para el Usuario ID: %d\n", idUsuario);
    // Recorrer todas las piezas almacenadas
    for (int i = 0; i < arrayPiezas.tamaño; i++) {
        Pieza* pieza = arrayPiezas.datos[i];  // Obtener puntero a la pieza

        // Verificar si el id_Usuario coincide
        if (pieza->id_Usuario == idUsuario) {
            // Imprimir datos comunes de la pieza
            printf("ID Pieza: %d, Tipo: %d, Material: %s, Desgaste: %.2f%%\n",
                   pieza->id_Pieza, pieza->tipo, pieza->material, pieza->desgaste);

            // Si la pieza es una Culata
            if (pieza->tipo == CULATA) {
                Culata* culata = (Culata*)pieza;  // Hacer cast a Culata

                printf("Tolerancia: %.2f,\n Medida Original: %.2f,\n Medida Actual: %.2f,\n Necesita Rectificacion: %d,\n"
                       "Número de válvulas: %d,\n Presión de prueba: %.2f,\n Combustible: %d,\n Tiene fisuras: %d,\n",
                       pieza->tolerancia, pieza->medidaOriginal, pieza->medidaActual, culata->numValvulas,
                       pieza->necesitaRectificacion, culata->presionPrueba, culata->tipoCombustible,
                       culata->tieneFisuras);
            }
            // Si la pieza es un Monoblock
            else if (pieza->tipo == MONOBLOCK) {
                Monoblock* monoblock = (Monoblock*)pieza;  // Hacer cast a Monoblock
                printf("Monoblock: Número de cilindros: %d, Diámetro del cilindro: %.2f, Ovalización: %.2f, Alineación cigüeñal: %.2f\n",
                       monoblock->numCilindros, monoblock->diametroCilindro, monoblock->ovalizacion, monoblock->alineacionCiguenal);
            }
            printf("\n");  // Línea en blanco entre piezas
        }
    }
}

void listarPiezas(){
    printf("==============================================\n");
    printf("          LISTADO DE TODAS LAS PIEZAS         \n");
    printf("==============================================\n");

    for (size_t i = 0; i < arrayPiezas.tamaño; i++) {
        Pieza* pieza = (Pieza*)arrayPiezas.datos[i];  // Convertimos a Pieza*

        printf("\nID Pieza: %d\n", pieza->id_Pieza);
        printf("ID Usuario: %d\n", pieza->id_Usuario);
        printf("Material: %s\n", pieza->material);
        printf("Desgaste: %.2f%%\n", pieza->desgaste);
        printf("Tolerancia: %.2f mm\n", pieza->tolerancia);
        printf("Medida Original: %.2f mm\n", pieza->medidaOriginal);
        printf("Medida Actual: %.2f mm\n", pieza->medidaActual);
        printf("Necesita Rectificación: %s\n", pieza->necesitaRectificacion ? "Si" : "No");

        if (pieza->tipo == CULATA) {
            Culata* culata = (Culata*)pieza;
            printf("Numero de Valvulas: %d\n", culata->numValvulas);
            printf("Presion de Prueba: %.2f\n", culata->presionPrueba);
            printf("Tipo de Combustible: %s\n", culata->tipoCombustible == 0 ? "Gasolina" : "Diesel");
            printf("Tiene Fisuras: %s\n", culata->tieneFisuras ? "Si" : "No");
        } else if (pieza->tipo == MONOBLOCK) {
            Monoblock* monoblock = (Monoblock*)pieza;
            printf("Numero de Cilindros: %d\n", monoblock->numCilindros);
            printf("Diametro Cilindros: %.2f mm\n", monoblock->diametroCilindro);
            printf("Altura Bloque: %.2f mm\n", monoblock->alineacionCiguenal);
        }

        printf("----------------------------------------------\n");
    }
}

void mostrarUsuario(Usuario usr) {
    mvprintw(10,10,"ID Usuario: %d\n", usr.id_usuario);
    mvprintw(10,11,"Folio Usuario: %s\n", usr.folio);
    mvprintw(10,12,"Nombre: %s\n", usr.nombreUsuario);
    mvprintw(10,13,"Apellido: %s\n", usr.apellido);
    mvprintw(10,14,"Celular: %lld\n", usr.celular);
    mvprintw(10,15,"Email: %s\n", usr.email);
    mvprintw(10,16,"Contacto: %s\n", usr.contacto);
}
