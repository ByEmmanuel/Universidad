//
// Created by Jesus Emmanuel Garcia on 4/24/25.
//


#include <ncurses.h>
#include <string.h>

#include "LogicaNegocio.h"
#include "UserInterface.h"
#include "Util.h"

#define MAX_USUARIOS 6
#define MAX_LONGITUD 50

char usuariosRegistrados[MAX_USUARIOS][MAX_LONGITUD] =  {"David","Jose","Admin","Pepe","Luis",""};
char contraseñasUsuarios[MAX_USUARIOS][MAX_LONGITUD] = {"123456789","987654321","01","24680",""};

char* empleado = 0;

int cliente(){
    //Funcion que crea a los clientes
    //Agregar valores (Todo en un String A una lista)

    // MENU CLIENTE
    int opcCliente = mostrarMenu(2," ") + 1;
    char* emailUsr;
    clear();
    refresh();

    int y = 3;
    if (opcCliente == 4) {
        return 1;  // Volver al menú principal
    }
    if (opcCliente == 1) {
        cleanScreen();
        clear();
        mvprintw(1,10,"Agregar Cliente");
        const char* nombreUsr = leerStringSeguro(y, 5, 19,"Ingrese Nombre: ");
        if (nombreUsr == NULL) {
            return -1;
        }
        char* folio = generarFolio(nombreUsr);
        const char* apellidoUsr = leerStringSeguro(y+=2, 5, 19,"Ingrese Apellido: ");
        if (apellidoUsr == NULL) {
            return -1;
        }
        const int celularUsr = leerIntSeguro(y+=2, 5, 15,"Ingrese Celular: ");
        emailUsr = leerStringSeguro(y+=2, 5, 49, "Ingrese Email: ");
        if (emailUsr == NULL) {
            return -1;
        }
        const char* contactoUsr = leerStringSeguro(y+=2,5, 29,"Ingrese Contacto: ");
        if (contactoUsr == NULL) {
            return -1;
        }
        while (!strContains(emailUsr, "@")) {
            if (mostrarMenu(7,"Tu Email no es valido, ¿Deseas volver a ingresarlo?") == 1){
                clear();
                emailUsr = leerStringSeguro(y,5,49,"Ingrese Email");
                if (emailUsr == NULL) {
                    return -1;
                }
            } else {
                mvprintw(y+2,10,"Registro INVÁLIDO: Email Inválido");
                getch();
                return -1;
            }
        }
        const Usuario usuario = inicializarUsuario(getIdUsuarioLogico(), folio, nombreUsr, apellidoUsr, celularUsr, emailUsr, contactoUsr);
        mostrarUsuario(usuario);
        guardarUsuarioArray(usuario);
        imprimirMensaje(10,13,"Registro Correcto, Presione Enter");

    } else if (opcCliente == 2){
        modificarCliente();
    }else if (opcCliente == 3) {  // Listar Clientes
        cleanScreen();
        if (arrayUsuarios.capacidad == 0) {
            printf("No hay clientes registrados.\n");
        } else {
            int p = 2;
            for (int i = 0; i < arrayUsuarios.tamanno; i++) {
                mvprintw(p++, 1, "ID: %d", arrayUsuarios.datos[i].id_usuario);
                if (arrayUsuarios.datos[i].motor != NULL) {
                    mvprintw(p++, 1, "Pieza: %s", arrayUsuarios.datos[i].motor->material);
                    //mvprintw(y++, 1, "Pieza: %s", arrayUsuarios.datos[i].motor->nombre);
                } else {
                    mvprintw(p++, 1, "Motor: (no asignada)");
                }
                mvprintw(p++, 1, "Folio: %s", arrayUsuarios.datos[i].folio);
                mvprintw(p++, 1, "Activo?: %d", arrayUsuarios.datos[i].activo);
                mvprintw(p++, 1, "Nombre: %s", arrayUsuarios.datos[i].nombreUsuario);
                mvprintw(p++, 1, "Apellido: %s", arrayUsuarios.datos[i].apellido);
                mvprintw(p++, 1, "Celular: %lld", arrayUsuarios.datos[i].celular);
                mvprintw(p++, 1, "Email: %s", arrayUsuarios.datos[i].email);
                mvprintw(p++, 1, "Contacto: %s", arrayUsuarios.datos[i].contacto);
                p++; // Dejar una línea en blanco entre registros
            }
            getch();
            return 1;
        }
        mvprintw(10, 10, "Capacidad En El arrayUsuarios: %d", arrayUsuarios.capacidad);
        mvprintw(10, 10, "Presiona ENTER para continuar...");
        getchar();  // Pausa antes de limpiar la pantalla
    }
    cleanScreen();
    return 1;
}

int modificarCliente(){
    cleanScreen();
    clear();
    int id_Cliente = leerIntSeguro(11, 15, 2,"Ingrese ID, Folio o Numero de Cliente: ");
    RETURN_IF_ESC(id_Cliente);

    //Esta funcion puede ser contraproducente ya que si algun campo del objeto Usuario, esta vacio,
    //esta opcion nunca va a funcionar
    cleanScreen();
    Usuario* usuarioNuevo = obtenerUsuarioByIdUsuario(id_Cliente);
    if (usuarioNuevo == NULL) {
        imprimirMensaje(13,15,"Cliente no encontrado");
        return -1;
    }

    if (strIsEmpty(usuarioNuevo->nombreUsuario) || strIsEmpty(usuarioNuevo->email) || strIsEmpty(usuarioNuevo->nombreUsuario)) {
        imprimirMensaje(12,15,"Cliente con datos incompletos");
        return -1;
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

    const int opcUsr = mostrarMenu(3," ") + 1;

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
            imprimirMensaje(12,15,"Modificación realizada con éxito");
            break;
        }
        printf("Error al leer entrada.\n");
        break;
    case 3:
        clear();
        refresh();
        usuarioNuevo->celular = leerIntSeguro(10,15,10,"Ingrese nuevo Número Celular: ");
        if (usuarioNuevo->celular != 0) imprimirMensaje(12,15,"Modificación realizada con éxito");
        getch();
        break;
    case 4:
        clear();
        refresh();
        reemplazoUsuario = leerStringSeguro(10,15,50,"Ingrese nuevo Email: ");

        while (!strContains(reemplazoUsuario, "@")){
            if (mostrarMenu(7,"Tu Email no es valido, ¿Deseas volver a ingresarlo?") == 1){
                clear();
                reemplazoUsuario = leerStringSeguro(10,5,49,"Ingrese Email");
                if (reemplazoUsuario == NULL) {
                    return 0;
                }
            } else {
                mvprintw(122,10,"Registro INVÁLIDO: Email Inválido");
                getch();
                return 0;
            }
        }

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
        return 0;
    default:
        mvprintw(12,15,"Opción inválida.\n");
        getch();
        return -1;
    }
    clear();
    refresh();
    return 0;
}

int loginUsuario(){
    int intentosUsuario = 0;

    do {
        printf("Ingrese Usuario: ");
        // Función para leer cadenas de manera segura
        char* usuarioID = enterString(MAX_LONGITUD);
        // Buscar el usuario en la lista
        int usuarioIndex = -1;
        for (int i = 0; i < MAX_USUARIOS; i++) {
            if (strcmp(usuarioID, usuariosRegistrados[i]) == 0) {
                usuarioIndex = i;
                break;
            }
        }

        if (usuarioIndex != -1) {
            //char passwUsuario[MAX_LONGITUD];
            printf("Ingrese Contraseña: ");
            char* passwUsuario = enterString(MAX_LONGITUD);
            // Si se encontró el usuario
            //scanf("%s", passwUsuario);

            // Verificar contraseña
            if (strEquals(passwUsuario, contraseñasUsuarios[usuarioIndex])) {
                empleado = usuarioID;
                printf("Inicio de sesión exitoso.\n");
                return 1;
            }
            printf("Contraseña incorrecta.\n");
        } else {
            printf("Usuario no encontrado.\n");
        }
        intentosUsuario++;
    } while (intentosUsuario < 3);  // Permitir 3 intentos

    printf("Se agotaron los intentos.\n");
    return 0;
}

/**
 * En las opciones de servicio
 * Rectificar -> Si la pieza necesita rectificacion se imprimira por pantalla una barra que simulara que se estara rectificanto
 * Ensamble -> Despues de rectificar la pieza hay que reensamblarla
 */
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
            mvprintw(fila++, 4, "Estado de la Pieza: %s", estadoPiezaTexto(pieza->culata->operacionesMotor));
        }else{
            mvprintw(fila++, 4, "Culata : (NO Asignada)");
        }
        if (pieza->monoblock != NULL) {
            Monoblock* monoblock = (Monoblock*)pieza;
            mvprintw(fila++, 4, "Tipo de Pieza: Monoblock");
            mvprintw(fila++, 4, "N° Cilindros: %d", monoblock->numCilindros);
            mvprintw(fila++, 4, "Diámetro Cilindros: %.2f mm", monoblock->diametroCilindro);
            mvprintw(fila++, 4, "Alineación Cigüeñal: %.2f mm", monoblock->alineacionCiguenal);
            mvprintw(fila++, 4, "Estado de la Pieza: %s", estadoPiezaTexto(monoblock->estadoPieza));
        }else{
            mvprintw(fila++, 4, "Monoblock : (NO Asignada)");
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
        Usuario usuario = arrayUsuarios.datos[i];

        mvprintw(y, 40, "Activo?: %s", usuario.activo ? "True" : "False");
        mvprintw(y, 60, "ID: %d", usuario.id_usuario);
        mvprintw(y, 70, "Nombre: %s", usuario.nombreUsuario);
        mvprintw(y, 90, "Folio: %s", usuario.folio);

        if (usuario.motor != NULL) {
            mvprintw(y, 110, "Numero de serie del motor: %s", usuario.motor->numeroSerie);

            if (usuario.motor->culata != NULL) {
                mvprintw(y, 180, "(Culata asignada)");
            } else {
                mvprintw(y, 180, "(Culata no asignada)");
            }
        } else {
            mvprintw(y, 105, "Motor no asignado");
        }

        y++; // Dejar una línea en blanco entre registros
    }
}