//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include "UsuarioDTO.h"
#include "Util.h"
#include "UserInterface.h"
#include "LogicaNegocio.h"
#include "Motores.h"

#define MAX_USUARIOS 6
#define MAX_LONGITUD 50

char usuariosRegistrados[MAX_USUARIOS][MAX_LONGITUD] =  {"David","Jose","Admin","Pepe","Luis",""};
char contraseñasUsuarios[MAX_USUARIOS][MAX_LONGITUD] = {"123456789","987654321","01","24680",""};
char* empleado;
int id_pieza_global = 0;

char* enterString(int length) {
    char* buffer = (char*)malloc(length + 1); // Reservar espacio para la cadena
    if (buffer == NULL) {
        perror("Error al asignar memoria");
        exit(1);
    }
    if (fgets(buffer, length + 1, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar el salto de línea al final
    }
    return buffer;
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
//Aqui iría va la funcion cliente pero esta puesta en DTO USUARIO

int servicio(){
    //Varibales locales
    // Material de la pieza (Hierro, Aluminio, etc.)
    // Nivel de desgaste en porcentaje (0-100%)
    // Tolerancia máxima de desgaste permitida antes de rectificar
    // Medida original de la pieza en mm
    // Medida actual después del desgaste
    //TipoCombustible tipo_combustible = {};

    const int opc = mostrarMenu(4,".") + 1;
    RETURN_IF_ESC(opc);
    int opcusrParteMotor;
    switch (opc){
        case 1:
            //Ingreso culata o monoblock
            //mvprintw(10,10,"Ingrese una opcion 1: Culata. 2: Monoblock");
            opcusrParteMotor = mostrarMenu(5,".") + 1;
            RETURN_IF_ESC(opcusrParteMotor);
            listarFoliosUsuarios();
            if (opcusrParteMotor == 1){
                //Esto debe ser el folio, pero esta agregado asi por temas de testeo
                const int id_Usuario = leerIntSeguro(10,10,10000,"Ingrese Id Usuario: ");
                RETURN_IF_ESC(id_Usuario);
                //Esta linea impide que si el usuario no existe no se hara nada
                if(obtenerUsuarioById(id_Usuario) == NULL)return -1;
                mvprintw(12, 10, "                                                 ");
                //Generar numero de servicio
                // Ingresar material
                char* material = leerStringSeguro(12,10,30,"Ingrese material del motor");
                if (material == NULL) {
                    return -1;
                }
                mvprintw(14, 10, "                                                 ");
                // Ingresar desgaste
                const float desgaste = leerFloatSeguro(14, 10, 30,"Ingresar desgaste");
                mvprintw(16, 10, "                                                 ");
                // Ingresar tolerancia
                const float tolerancia = leerFloatSeguro(16, 10, 100, "Ingrese tolerancia");
                mvprintw(18, 10, "                                                 ");
                // Ingresar medidaOriginal
                const float medidaOriginal = leerFloatSeguro(18, 10, 100,"Ingrese medida Original");
                mvprintw(20, 10, "                                                 ");
                // Ingresar medidaActual
                const float medidaActual = leerFloatSeguro(20, 10, 100,"Ingrese Medida Actual");
                mvprintw(22, 10, "                                                 ");
                // comprobar necesitaRectificacion
                //Funcion necesita rectificacion
                // Ingresar numValvulas
                const int numValvulas = leerIntSeguro(22, 10, 50,"Ingrese numero Valvulas");
                mvprintw(24, 10, "                                                 ");
                // Ingresar presionPrueba
                const float presionPrueba = leerFloatSeguro(24, 10, 20,"Ingrese PresionPrueba");
                mvprintw(26, 10, "                                                 ");
                // Ingresar tipoCombustible
                int tipo_combustible = mostrarMenu(6,"Ingrese tipo de combustible");

                const int tieneFisuras = mostrarMenu(7,"¿Tiene Fisuras?");

                const int rectificacion = mostrarMenu(7,"¿Necesita Rectificación?");
                // Ahora puedes usar buffer como un char*
                mvprintw(3, 55, "Rectificacion?: %d", rectificacion);
                mvprintw(4, 55, "Tiene Fisuras?: %d", tieneFisuras);
                mvprintw(5, 55, "Tipo Combustible: %d", tipo_combustible);

                Paramsmotor registro_motor = {

                        /**
        .nombre = "1.8L i-VTEC",
        .fabricante = "Honda",
        .cilindrada = 1.8f,
        .compresionOriginal = 190.0f,
        .tipoCombustible = 0,             // 0 = Gasolina
        .tipoPieza = CULATA,              // Definido en enum TipoPieza
        .material = "Aluminio",
        .desgaste = 0.09f,                // 9% de desgaste
        .tolerancia = 0.10f,
        .medidaOriginal = 81.0f,
        .medidaActual = 80.93f,
        .necesitaRectificacion = 0       // No necesita rectificación

                         */
                        //Campos por agregar;
                        .nombre = "POR AGREGAR",
                        .fabricante = "POR AGREGAR",
                        .cilindrada = 0.0,
                        .compresionOriginal = 0.0,
                        .tipoCombustible = tipo_combustible,
                        //.numeroSerie = "POR AGREGAR",
                        //Esta debe de ponerse en automatico en otra funcion
                        .tipoPieza = CULATA,
                        .material = material,
                        .desgaste = desgaste,
                        .tolerancia = tolerancia ,
                        .medidaOriginal = medidaActual,
                        .medidaActual = medidaActual,
                        .necesitaRectificacion = rectificacion
                };
                //const Motor piezaUsuario = inicializarMotor(registro_motor, );
                //Por agregar numero de serie
                    Motor motor = inicializarMotor(registro_motor, id_Usuario, id_pieza_global, "JKOXS1234");
                //Polimorfismo
                    Culata* pzc = inicializarCulata(motor, numValvulas, presionPrueba, tieneFisuras);
                    guardarPiezaArray((void*)pzc);  // Se guarda como puntero genérico

                    Usuario* usuario = obtenerUsuarioById(id_Usuario);
                    asignarPiezaUsuario(usuario, pzc);
                mvprintw(8, 55, "Pieza Asignada y Guardada Correctamente");
                id_pieza_global ++;
                getch();
            }else if (opcusrParteMotor == 2){
                mvprintw(10,10,"Opcion Monoblock");
            }else if (opcusrParteMotor == 3){
                listarPiezas();
            }
            printf("Opcion no valida");

            break;
        case 2:
        //Lavado

            break;
        case 3:
        //Medidas

            break;
        case 4:
        //Rectificar

            break;
        case 5:
            //Ensamble

            break;
        case 6:
            //Menu Anterior
            return 1;
    default:
        break;
    }
    //Ingresar manualmente que es lo que se quiere reconstruir
    // Cabeza o culata

    return 0;
}

int pago(){
    printf("Opcion pago ");
    return 0;
}

int almacen(){
    const int opcUsr = mostrarMenu(8, ".") + 1;
    RETURN_IF_ESC(opcUsr);
    switch (opcUsr){
    case 1:
        //const int opcUsrInventario = mostrarMenu(9,".");
            clear();
            mvprintw(10,10,"Atiende: %s",empleado);
            getch();
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

void mostrarLogo(){
    printf("\nBienvenido al sistema\n");
    //usleep(300000);
    printf("    ____           __ \n");
    //usleep(300000);
    printf("   / __/__    ____/ /___  _________ \n");
    //usleep(300000);
    printf("  / /_/ _ \\ / __  / __ / ___/ __ /\n");
    //usleep(300000);
    printf(" / __/  __/ /_/ / /_/ / /  / /_/ / \n");
    //usleep(300000);
    printf("/_/  \\___/\\__,_/\\____/_/   \\__,_/  \n");
    //usleep(800000);
    printf("      /\\     \n");
    printf("     /  \\    \n");
    printf("    /    \\    \n");
    //sleep(1);
    // Ingresar delay y cambiar la pantalla de color

}

int asignarPiezaUsuario(Usuario* usuario, void* pieza){
    if (usuario == NULL || usuario->activo != 1){
        mvprintw(10,10,"Usuario invalido o no encontrado");
        getch();
        return 0;
    }
    usuario->motor = pieza;
    return 1;
};


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
    //Motor piezaUsuario = inicializarMotor(0, 1, "Metal", .1123f, .1125f, .1300f, .1180f, 0,1);

    const Paramsmotor motores_registrados[2] = {
            {
                .nombre = "1.8L i-VTEC",
                .fabricante = "Honda",
                .cilindrada = 1.8f,
                .compresionOriginal = 190.0f,
                .tipoCombustible = 0,             // 0 = Gasolina
                .tipoPieza = CULATA,              // Definido en enum TipoPieza
                .material = "Aluminio",
                .desgaste = 0.09f,                // 9% de desgaste
                .tolerancia = 0.10f,
                .medidaOriginal = 81.0f,
                .medidaActual = 80.93f,
                .necesitaRectificacion = 0       // No necesita rectificación
            },
            {
                .nombre = "3.2L Duratorq",
                .fabricante = "Ford",
                .cilindrada = 3.2f,
                .compresionOriginal = 410.0f,
                .tipoCombustible = 1,             // 1 = Diesel
                .tipoPieza = MONOBLOCK,           // Definido en enum TipoPieza
                .material = "Hierro fundido",
                .desgaste = 0.14f,                // 14% de desgaste
                .tolerancia = 0.12f,
                .medidaOriginal = 89.9f,
                .medidaActual = 89.76f,
                .necesitaRectificacion = 1       // Sí necesita rectificación
            }
    };

    //id_pieza_global tiene problemas para actualizarse 

    //Sospechozo, le asigno 2 veces el tipo de pieza, 1 aqui y otra en inicializarCulata
    //piezaUsuario.tipoPieza = CULATA;

    Motor piezaUsuario = inicializarMotor(motores_registrados[0],0,0,"NUMSERIE");
    piezaUsuario.tipoPieza = CULATA;
    Culata* pzc = inicializarCulata(piezaUsuario, 16, .10, 2);
    guardarPiezaArray((void*)pzc);  // Se guarda como puntero genérico
    Usuario* usuario1 = obtenerUsuarioById(0);
    asignarPiezaUsuario(usuario1, (void*)pzc);


    Motor piezaUsuario2 = inicializarMotor(motores_registrados[1], 1,1,"NUMSERIE");
    piezaUsuario2.tipoPieza = CULATA;
    Culata* pzc2 = inicializarCulata(piezaUsuario2, 18, 0.12, 1);
    guardarPiezaArray((void*)pzc2);
    Usuario* usuario2 = obtenerUsuarioById(1);
    asignarPiezaUsuario(usuario2, pzc2);

    //Motor pieza1 = inicializarMotor(0, 0, "Aluminio", 0.05f, 0.12f, 79.0f, 78.95f, 0, 180.0f);

    /**

    Culata* culata1 = inicializarCulata(pieza1, 16, 0.10, 0);
    guardarPiezaArray((void*)culata1);

    //Motor pieza2 = inicializarMotor(1, 0, "Hierro", 0.08f, 0.15f, 79.5f, 79.35f, 1, 400.0f);

    Culata* culata2 = inicializarCulata(pieza2, 16, 0.15, 1);
    guardarPiezaArray((void*)culata2);

    //Motor pieza3 = inicializarMotor(2, 0, "Hierro Fundido", 0.10f, 0.20f, 99.5f, 99.3f, 0, 195.0f);

    Culata* culata3 = inicializarCulata(pieza3, 16, 0.18, 0);
    guardarPiezaArray((void*)culata3);

    //Motor pieza4 = inicializarMotor(3, 0, "Acero", 0.06f, 0.14f, 87.5f, 87.4f, 0, 210.0f);

    Culata* culata4 = inicializarCulata(pieza4, 16, 0.12, 0);
    guardarPiezaArray((void*)culata4);

    //Motor pieza5 = inicializarMotor(4, 0, "Hierro", 0.09f, 0.18f, 93.0f, 92.8f, 1, 410.0f);

    Culata* culata5 = inicializarCulata(pieza5, 16, 0.16, 1);
    guardarPiezaArray((void*)culata5);

    //Motor pieza6 = inicializarMotor(5, 0, "Aluminio", 0.07f, 0.13f, 89.0f, 88.85f, 0, 185.0f);

    Culata* culata6 = inicializarCulata(pieza6, 16, 0.14, 0);
    guardarPiezaArray((void*)culata6);

    */

}
