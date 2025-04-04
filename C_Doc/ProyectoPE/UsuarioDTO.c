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
            //mostrarUsuario(arrayUsuarios.datos[i]);
            return &arrayUsuarios.datos[i];
        }
    }
    // Retorna NULL si el usuario no existe
    mvprintw(15,15,"Usuario no encontrado... Vuelve a intentar\n");
    return NULL;
}

void modificarCliente(){
    cleanScreen();
    clear();
    mvprintw(10,15,"Ingrese ID, Folio o Numero de Cliente: ");

    int* ptr_id_Cliente = leerInt(11, 15, 2);
    if (ptr_id_Cliente == NULL) {
        mvprintw(12,15,"Error al leer ID.\n");
        return;
    }
    int id_Cliente = *ptr_id_Cliente;
    free(ptr_id_Cliente);  // Liberamos la memoria

    //scanf("%d", &id_Cliente);

    //Esta funcion puede ser contraproducente ya que si algun campo del objeto Usuario, esta vacio,
    //esta opcion nunca va a funcionar
    Usuario* usuarioNuevo = obtenerUsuario(id_Cliente);
    if (usuarioNuevo == NULL) {
        mvprintw(12,15,"Cliente no encontrado.\n");
        return;
    }

    if (strIsEmpty(usuarioNuevo->nombreUsuario) || strIsEmpty(usuarioNuevo->email) || strIsEmpty(usuarioNuevo->nombreUsuario)) {
        mvprintw(12,15,"Cliente con datos incompletos.\n");
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

    const int opcUsr = menuModificarCliente();
    clear();
    refresh();

    //char reemplazoUsuario[50]; // Buffer para almacenar entrada
    char* reemplazoUsuario;
    //<cleanBuffer();

    switch (opcUsr) {
        case 1:
            mvprintw(9,15,"Ingrese nuevo Nombre: ");
            reemplazoUsuario = leerString(10,15,50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")) {
                asignString(usuarioNuevo->nombreUsuario, reemplazoUsuario, sizeof(usuarioNuevo->nombreUsuario));
                mvprintw(12,15,"Modificación realizada con éxito.\n");
                clear();
                refresh();
                break;
            }
            mvprintw(12,15,"Error al leer entrada.\n");
            break;
        case 2:
            mvprintw(9,15,"Ingrese nuevo Apellido: ");
            reemplazoUsuario = leerString(10,15,50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->apellido, reemplazoUsuario, sizeof(usuarioNuevo->apellido));
                mvprintw(12,15,"Modificación realizada con éxito.\n");
                break;
            }
            printf("Error al leer entrada.\n");
            break;
        case 3:
            mvprintw(9,15,"Ingrese nuevo Número Celular: ");
            int* ptr_numero = leerInt(10,15,10);
            if (ptr_numero == NULL) {
                mvprintw(12,15,"Error al leer número de celular.\n");
                return;
            }
            usuarioNuevo->celular = *ptr_numero;
            free(ptr_numero);
            cleanBuffer();
            break;
        case 4:
            mvprintw(9,15,"Ingrese nuevo Email: ");
            reemplazoUsuario = leerString(10,15,50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->email, reemplazoUsuario, sizeof(usuarioNuevo->email));
                mvprintw(12,15,"Modificación realizada con éxito.\n");
                break;
            };
            mvprintw(12,15,"Error al leer entrada.\n");
            break;
        case 5:
            mvprintw(9,15,"Ingrese nuevo Contacto: ");
            reemplazoUsuario = leerString(10,15,50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->contacto, reemplazoUsuario, sizeof(usuarioNuevo->contacto));
                mvprintw(12,15,"Modificación realizada con éxito.\n");
                break;
            };
            mvprintw(12,15,"Error al leer entrada.\n");
            break;
        case 6:
            mvprintw(2, 10, "Saliendo del menú...");  // Muestra mensaje de depuración
            refresh();  // Asegúrate de que el mensaje se actualice
            //@Deprecated
            //endwin();   // Finaliza ncurses, si lo necesitas
            return;
        default:
            mvprintw(12,15,"Opción inválida.\n");
            return;
    }
    //cleanBuffer();
    clear();
    refresh();
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
        char* nombreUsr = leerString(4, 26, 19);
        char* folio = generarFolio(nombreUsr);
        mvprintw(5, 10, "Ingrese Apellido: ");
        char* apellidoUsr = leerString(5, 28, 19);
        mvprintw(6, 10, "Ingrese Celular: ");
        char* celularStr = leerString(6, 27, 15);
        long long celularUsr = atoll(celularStr);
        mvprintw(7, 10, "Ingrese Email: ");
        char* emailUsr = leerString(7, 25, 49);
        mvprintw(8, 10, "Ingrese Contacto: ");
        char* contactoUsr = leerString(8, 28, 29);


        while (!strContains(emailUsr, "@")) {
            free(emailUsr);
            mvprintw(10,10,"Tu Email no es valido, ¿Deseas volver a ingresarlo? 1: SI 2: NO");
            const char* opcUsr = leerString(12,10,25);
            if (strContains(opcUsr, "1")) {
                mvprintw(10,10,"\033[2A\033[2K\033[1B\033[2K");
                clear();
                //fflush(stdout);
                mvprintw(10,12,"Ingrese Email\n");
                emailUsr = leerString(11,12,49);
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
        mvprintw(10, 10, "\nPresiona ENTER para continuar...");
        getchar();  // Pausa antes de limpiar la pantalla
    }
    cleanScreen();
    //mvprintw(10, 10, "Saliendo opcCliente");
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
    noecho();              // No muestra lo que escribe el usuario
    cbreak();              // Lectura sin necesidad de ENTER
    keypad(stdscr, TRUE);  // Permite teclas especiales
    int fila = 1;
    mvprintw(fila++, 10, "==============================================");
    mvprintw(fila++, 15, "LISTADO DE TODAS LAS PIEZAS");
    mvprintw(fila++, 10, "==============================================");
    for (size_t i = 0; i < arrayPiezas.tamaño; i++) {
        Pieza* pieza = (Pieza*)arrayPiezas.datos[i];
        fila++;
        mvprintw(fila++, 2, "ID Pieza: %d", pieza->id_Pieza);
        mvprintw(fila++, 2, "ID Usuario: %d", pieza->id_Usuario);
        mvprintw(fila++, 2, "Material: %s", pieza->material);
        mvprintw(fila++, 2, "Desgaste: %.2f%%", pieza->desgaste);
        mvprintw(fila++, 2, "Tolerancia: %.2f mm", pieza->tolerancia);
        mvprintw(fila++, 2, "Medida Original: %.2f mm", pieza->medidaOriginal);
        mvprintw(fila++, 2, "Medida Actual: %.2f mm", pieza->medidaActual);
        mvprintw(fila++, 2, "Necesita Rectificación: %s", pieza->necesitaRectificacion ? "Sí" : "No");
        if (pieza->tipo == CULATA) {
            Culata* culata = (Culata*)pieza;
            mvprintw(fila++, 4, "Numero de Válvulas: %d", culata->numValvulas);
            mvprintw(fila++, 4, "Presión de Prueba: %.2f", culata->presionPrueba);
            mvprintw(fila++, 4, "Tipo de Combustible: %s", culata->tipoCombustible == 0 ? "Gasolina" : "Diésel");
            mvprintw(fila++, 4, "Tiene Fisuras: %s", culata->tieneFisuras ? "Sí" : "No");
        } else if (pieza->tipo == MONOBLOCK) {
            Monoblock* monoblock = (Monoblock*)pieza;
            mvprintw(fila++, 4, "Número de Cilindros: %d", monoblock->numCilindros);
            mvprintw(fila++, 4, "Diámetro de Cilindros: %.2f mm", monoblock->diametroCilindro);
            mvprintw(fila++, 4, "Altura del Bloque: %.2f mm", monoblock->alineacionCiguenal);
        }
        mvprintw(fila++, 10, "----------------------------------------------");
        // Manejo de overflow vertical
        if (fila >= LINES - 5) {
            mvprintw(fila++, 10, "Presiona cualquier tecla para continuar...");
            getch();
            clear();
            fila = 1;
        }
    }
    mvprintw(fila++, 10, "Fin del listado. Presiona cualquier tecla...");
    getch();
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
