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

#define MAX_USUARIOS 6
#define MAX_LONGITUD 50

char usuariosRegistrados[MAX_USUARIOS][MAX_LONGITUD] =  {"David","Jose","Admin","Pepe","Luis",""};
char contraseñasUsuarios[MAX_USUARIOS][MAX_LONGITUD] = {"123456789","987654321","01","24680",""};
char* empleado;


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
    int y = 2;
    int opc = mostrarMenu(4,".");
    RETURN_IF_ESC(opc);
    int opcusrParteMotor;
    switch (opc){
        case 0:{
               //Ingreso datos motor

                // Variables auxiliares
            int id_pieza = id_piezaGlobal;
            clear();
            int id_usuario = obtenerIdSiExisteUsuario();
            RETURN_IF_ESC(id_usuario);
            clear();
            char* modelo = leerStringSeguro(y+=2, 10, 100, "Ingrese Modelo del Motor - String");
                if (modelo == NULL)return -1;
            char* fabricante = leerStringSeguro(y+=2, 10, 100, "Ingrese Fabricante del Motor - String");
                if (fabricante == NULL)return -1;
            char* carroAsociado = leerStringSeguro(y+=2, 10, 100, "Ingrese Carro Asociado - String");
                if (carroAsociado == NULL)return -1;
            char* material = leerStringSeguro(y+=2, 10, 30, "Ingrese Material de Motor - String");
                if (material == NULL) return -1;
            int anno = leerIntSeguro(y+=2, 10, 10, "Ingrese Año del Motor - Entero");
            float cilindrada = leerFloatSeguro(y+=2, 10, 10, "Ingrese Cilindrada (L) - Float");
            float compresionOriginal = leerFloatSeguro(y+=2, 10, 10, "Ingrese Compresión Original (psi) - Float");
            char* numeroSerie = leerStringSeguro(y+=2, 10, 50, "Ingrese Número de Serie - String");
            int tipoCombustible = mostrarMenu(6, "Seleccione Tipo de Combustible - Entero");

            float desgaste = leerFloatSeguro(y+=2, 10, 10, "Ingrese Desgaste (%) - Float") / 100.0f;
            float tolerancia = leerFloatSeguro(y+=2, 10, 10, "Ingrese Tolerancia (mm) - Float");
            float medidaOriginal = leerFloatSeguro(y+=2, 10, 10, "Ingrese Medida Original (mm) - Float");
            float medidaActual = leerFloatSeguro(y+=2, 10, 10, "Ingrese Medida Actual (mm) - Float");

            // Variables que dependen de cálculo y tienen que ir aparte
            int necesitaRectificacion = 0;
            int necesitaReconstruccion = 0;
            float diferencia = medidaOriginal - medidaActual;
            if (diferencia <= tolerancia) {
                necesitaRectificacion = 1;
                necesitaReconstruccion = 0;
            } else {
                necesitaRectificacion = 0;
                necesitaReconstruccion = 1;
            }

            // Ahora sí: inicializas la estructura
            Paramsmotor paramsmotor = {
                .id_pieza = id_pieza,
                .id_usuario = id_usuario,
                .modelo = modelo,
                .fabricante = fabricante,
                .carroAsociado = carroAsociado,
                .anno = anno,
                .cilindrada = cilindrada,
                .compresionOriginal = compresionOriginal,
                .numeroSerie = numeroSerie,
                .tipoCombustible = tipoCombustible,
                .material = material,
                .desgaste = desgaste,
                .tolerancia = tolerancia,
                .medidaOriginal = medidaOriginal,
                .medidaActual = medidaActual,
                .necesitaRectificacion = necesitaRectificacion,
                .necesitaReconstruccion = necesitaReconstruccion
            };
                Motor* motor = inicializarMotor(paramsmotor,id_usuario,id_piezaGlobal,0,0);
                guardarMotorArray(motor,id_usuario);
                asignarMotorUsuario(obtenerUsuarioByIdUsuario(id_usuario),motor);
                //Mensaje de exito
                imprimirMensaje(10,10,"El motor fue registrado Correctamente");
                id_piezaGlobal++;
                return 1;
            }
        /**
char* menuCuatro[SIZE_SEIS] = {"Ingreso datos motor", "Medidas", "Lavado",  "Rectificar", "Ensamble", "Salir"};
char* menuCinco[SIZE_TRES] = {"CULATA", "MONOBLOCK", "Listar Piezas"};
         */
        case 1:
            //Ingreso culata o monoblock
            clear();
            opcusrParteMotor = mostrarMenu(5,".");
            RETURN_IF_ESC(opcusrParteMotor);
            listarFoliosUsuarios();
            if (opcusrParteMotor == 0){
                if (registrarCulata() != 1){
                    imprimirMensaje(10,10,"¡Hubo un error al crear las piezas -> Culata o No existe un motor previo!");
                }
                return -1;
            }
            if (opcusrParteMotor == 1){
                //registrarMonoblock();
                mvprintw(10,10,"Opcion Monoblock");
            }else if (opcusrParteMotor == 2){
                listarPiezas();
            }
            //printf("Opcion no valida");

            break;
        case 2:{
                //Lavado
                clear();
                if (mostrarMenu(7, "¿Desea agregar el lavado a su servicio?") == 0) return -1;
                clear();
                int id_usuario = obtenerIdSiExisteUsuario();
                RETURN_IF_ESC(id_usuario);
                Ticket* ticket = obtenerTicketByIdUsuario(id_usuario);
                ticket->lavado = 1;
                clear();
                //barraDeCarga(/*Tiempo en ms*/ 8000)
                mvprintw(10,10,"El motor y el carro fueron lavados!     Presione Enter");
                getch();
            }
            break;
        case 3:
            //Rectificar

            break;
        case 4:
            //Ensamble

            break;
        case 5:
            //Menu Anterior
            return 1;
    default:
        break;
    }
    //Ingresar manualmente que es lo que se quiere reconstruir
    // Cabeza o culata

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

int asignarMotorUsuario(Usuario* usuario, Motor* motor ){
    if (usuario == NULL || usuario->activo != 1){
        clear();
        mvprintw(10,10,"Usuario invalido o no encontrado");
        getch();
        return 0;
    }
    if (usuario->motor != NULL){
        clear();
        mvprintw(10,10,"La pieza ya fue asignada anteriormente");
        getch();
        return 0;
    }
    if (motor != NULL) usuario->motor = motor;
    return 1;
};
// 1 CULATA , 2  MONOBLOCK
int asignarPiezaMotor(Usuario* usuario, void* pieza, int tipoDePieza){
    if (tipoDePieza == 1){
        usuario->motor->culata = (Culata*)pieza;
        return 1;
    }
    if (tipoDePieza == 2){
        usuario->motor->monoblock = (Monoblock*)pieza;
        return 1;
    }
    return 0;
};

void testing(int tipoDeTesting) {
    //usleep(200);
    printf("\n------TESTING MODE ON------");
    switch (tipoDeTesting){
    case 1:
        agregarUsuarios();
        break;
    case 2:
        agregarPiezas();
        break;
    case 3:
        agregarUsuarios();
        agregarPiezas();
        break;
    default: break;
    }
}

void agregarUsuarios() {
    const Usuario usuario1 = inicializarUsuario(0,"00001", "Usuario1", "Apellido 1", 1234567890, "EmailPrueba1@1", "Contacto1");
    guardarUsuarioArray(usuario1);
    const Usuario usuario2 = inicializarUsuario(1,"00002", "Usuario2", "Apellido 2", 1987654321, "EmailPrueba2@2", "Contacto2");
    guardarUsuarioArray(usuario2);
}

void agregarPiezas() {

    const Paramsmotor motores_registrados[2] = {
        {
            .id_pieza = 0,
            .id_usuario = 0,
            .modelo = "Duratec 2.0",
            .fabricante = "Ford",
            .carroAsociado = "Ford Focus 2012",
            .anno = 2012,
            .cilindrada = 2.0f,
            .compresionOriginal = 130.0f,
            .numeroSerie = "FD2K-123456",
            .tipoCombustible = GASOLINA,
            .material = "Aluminio",
            .desgaste = 0.125f,          // 12.5%
            .tolerancia = 0.05f,          // 0.05 mm
            .medidaOriginal = 82.50f,     // mm
            .medidaActual = 82.40f,       // mm
            .necesitaRectificacion = 1,
            .necesitaReconstruccion = 0
        },
        {
            .id_pieza = 1,
            .id_usuario = 1,
            .modelo = "K20A",
            .fabricante = "Honda",
            .carroAsociado = "Honda Civic Type R 2004",
            .anno = 2004,
            .cilindrada = 2.0f,
            .compresionOriginal = 210.0f,
            .numeroSerie = "HND-K20A1234",
            .tipoCombustible = GASOLINA,
            .material = "Aluminio",
            .desgaste = 0.045f,
            .tolerancia = 0.04f,
            .medidaOriginal = 86.0f,
            .medidaActual = 85.98f,
            .necesitaRectificacion = 0,
            .necesitaReconstruccion = 0
        },
    };

    //id_pieza_global tiene problemas para actualizarse 

    //Sospechozo, le asigno 2 veces el tipo de pieza, 1 aqui y otra en inicializarCulata
    //piezaUsuario.tipoPieza = CULATA;
    const int id_usuario = 0, id_usuario_2 = 1;
    Motor* motorUsuario_1 = inicializarMotor(motores_registrados[0],id_usuario,0,0,0);
    Culata* pzc = inicializarCulata(16, 10, 2,2,.124f,.123f,.120f, id_usuario);
    //piezaUsuario.tipoPieza = CULATA;
    guardarMotorArray(motorUsuario_1,id_usuario);  // Se guarda como puntero genérico
    guardarPiezaArray(pzc,id_usuario);
    Usuario* usuario1 = obtenerUsuarioByIdUsuario(id_usuario);
    asignarMotorUsuario(usuario1, motorUsuario_1);
    asignarPiezaMotor(usuario1,pzc, 1);


    Motor* motorUsuario_2 = inicializarMotor(motores_registrados[1], id_usuario_2,1,0,0);
    Culata* pzc2 = inicializarCulata(18, 12, 1,14,.340f,.338f,.339f, id_usuario_2);
    //piezaUsuario2.tipoPieza = CULATA;
    guardarMotorArray(motorUsuario_2, id_usuario_2);
    guardarPiezaArray(pzc2, id_usuario_2);
    Usuario* usuario2 = obtenerUsuarioByIdUsuario(id_usuario_2);
    asignarMotorUsuario(usuario2, motorUsuario_2);
    asignarPiezaMotor(usuario2,pzc2, 1);

    id_piezaGlobal+=2;

}
