//
// Created by Jesus Emmanuel Garcia on 5/1/25.
//

#include "Testing.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "AlmacenYOtros.h"
#include "LogicaNegocio.h"
#include "UserInterface.h"
#include "UsuarioDTO.h"

void testing(int tipoDeTesting) {
    agregarSystemLog(1,"Login","Ninguno","-1",INFO, 1, "Login", "IDK", "0");
    if (tipoDeTesting){
        //usleep(200);
        int cantidadMotores = sizeof(motoresExistentesSINCulatasAsignadas) / sizeof(Motor);

        /**
        * *  0 = no testing mode
     *  1 = agregar usuarios
     *  2 = agregar motores y piezas -> Estos pertenecen a un usuario --> ¿Porque agregarias motores sin un usuario?
     *  3 = agregar usuarios y (motores y piezas) -> Estos pertenecen a un usuario
     *  4 = agregar usuarios con motoresDB precargados
     *  5 = agregar usuarios, (motores y piezas) y agregar MotoresPrecargados;
     *  6 = solo precargar motores (arrayMotoresPrecargados)
    precargarMotoresDB(motoresExistentesSINCulatasAsignadas, cantidadMotores);
         */

        printf("\n------TESTING MODE ON------ %d ", tipoDeTesting);
        switch (tipoDeTesting){
        case 1:
            agregarUsuarios();
            break;
        case 2:
            //Add
             //agregarUsuarios();
             // crashea porque no hay usuarios a los que se les añada la pieza
            //agregarPiezas();
            break;
        case 3:
            agregarUsuarios();
            agregarPiezas();
            break;
        case 4:
            agregarUsuarios();

            inicializarArrayMotoresPrecargados();
            precargarMotoresDB(motoresExistentesSINCulatasAsignadas, cantidadMotores);
            break;
        case 5:
            agregarUsuarios();
            agregarPiezas();

            inicializarArrayMotoresPrecargados();
            precargarMotoresDB(motoresExistentesSINCulatasAsignadas, cantidadMotores);
            break;
        case 6:
            inicializarArrayMotoresPrecargados();
            precargarMotoresDB(motoresExistentesSINCulatasAsignadas, cantidadMotores);
            break;
        default: break;
        }
    }
}

void agregarUsuarios() {
    const Usuario usuario1 = inicializarUsuario(0,"00001", "Usuario1", "Apellido 1", 1234567890, "EmailPrueba1@1", "Contacto1");
    guardarUsuarioArray(usuario1);
    agregarSystemLog(usuario1.id_usuario, "Usuario", "Registro", "00001", INFO, 1, "GuardarUsuario", "Usuario1 agregado", "0");

    const Usuario usuario2 = inicializarUsuario(1,"00002", "Usuario2", "Apellido 2", 1987654321, "EmailPrueba2@2", "Contacto2");
    guardarUsuarioArray(usuario2);
    agregarSystemLog(usuario1.id_usuario, "Usuario", "Registro", "00002", INFO, 1, "GuardarUsuario", "Usuario2 agregado", "0");

    const Usuario usuario3 = inicializarUsuario(2,"00003","Usuario3","Apellido 3",2746297201,"emailPrueba3@3","Contacto3");
    guardarUsuarioArray(usuario3);
    agregarSystemLog(usuario1.id_usuario, "Usuario", "Registro", "00003", INFO, 1, "GuardarUsuario", "Usuario3 agregado", "0");
}

void inicializarArrayMotoresPrecargados() {
    arrayMotoresPrecargados.tamanno = 0;
    arrayMotoresPrecargados.capacidad = 0;
    arrayMotoresPrecargados.datos = NULL;
}

int precargarMotoresDB(Motor motores[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        if (arrayMotoresPrecargados.tamanno >= arrayMotoresPrecargados.capacidad) {
            int nuevaCapacidad = arrayMotoresPrecargados.capacidad == 0 ? 1 : arrayMotoresPrecargados.capacidad * 2;
            void** nuevoArray = realloc(arrayMotoresPrecargados.datos, nuevaCapacidad * sizeof(void*));
            if (!nuevoArray) {
                imprimirMensaje(10,10,"Error al redimensionar el array de motores precargados");
                return -1;
            }
            arrayMotoresPrecargados.datos = nuevoArray;
            arrayMotoresPrecargados.capacidad = nuevaCapacidad;
        }
        agregarSystemLog(motores[i].id_usuario, "Motor", "Precarga", motores[i].numeroSerie, INFO, 1, "PrecargarMotor", "Motor insertado en array de motores precargados", "0");
        arrayMotoresPrecargados.datos[arrayMotoresPrecargados.tamanno++] = &motores[i];
        id_piezaGlobal++;
    }
    return 1; // Éxito
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
            /*
            .desgaste = 0.125f,          // 12.5%
            .tolerancia = 0.05f,          // 0.05 mm
            */
            .medidaOriginal = 82.50f,     // mm
            .medidaActual = 82.40f,       // mm
            /*
            .necesitaRectificacion = 1,
            .necesitaReconstruccion = 0
            */
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
            /*
            .desgaste = 0.045f,
            .tolerancia = 0.04f,
            */
            .medidaOriginal = 86.0f,
            .medidaActual = 85.98f,
            /*
            .necesitaRectificacion = 0,
            .necesitaReconstruccion = 0
            */
        },
    };

    //id_pieza_global tiene problemas para actualizarse

    //Sospechozo, le asigno 2 veces el tipo de pieza, 1 aqui y otra en inicializarCulata
    //piezaUsuario.tipoPieza = CULATA;
    const int id_usuario = 0, id_usuario_2 = 1;
    Motor* motorUsuario_1 = inicializarMotor(motores_registrados[0],id_usuario,0,0,0);
    Culata* pzc = inicializarCulata(16, 10, 2,2,.124f,.123f,.120f, id_usuario,-1);
    //piezaUsuario.tipoPieza = CULATA;

    guardarMotorArray(motorUsuario_1,id_usuario);
    agregarSystemLog(id_usuario, "Motor", "Registro", motores_registrados[0].numeroSerie, INFO, 1, "GuardarMotor", "Motor registrado en pruebas", "0");

    guardarPiezaArray(pzc,id_usuario);
    agregarSystemLog(id_usuario, "Pieza", "Registro", "Culata", INFO, 1, "GuardarPieza", "Culata registrada en pruebas", "0");

    Usuario* usuario1 = obtenerUsuarioByIdUsuario(id_usuario);
    asignarMotorUsuario(usuario1, motorUsuario_1);
    asignarPiezaMotor(usuario1,pzc, 1);


    Motor* motorUsuario_2 = inicializarMotor(motores_registrados[1], id_usuario_2,1,0,0);
    Culata* pzc2 = inicializarCulata(18, 12, 1,14,.340f,.338f,.339f, id_usuario_2,-2);
    //piezaUsuario2.tipoPieza = CULATA;
    guardarMotorArray(motorUsuario_2, id_usuario_2);
    guardarPiezaArray(pzc2, id_usuario_2);
    Usuario* usuario2 = obtenerUsuarioByIdUsuario(id_usuario_2);
    asignarMotorUsuario(usuario2, motorUsuario_2);
    asignarPiezaMotor(usuario2,pzc2, 1);

    id_piezaGlobal+=2;

}

void listarMotoresPrecargados() {
    clear();
    int fila = 1;

    if (arrayMotoresPrecargados.tamanno == 0) {
        mvprintw(fila++, 5, "No hay motores precargados para mostrar.");
        getch();
        return;
    }

    mvprintw(fila++, 5, "====== LISTADO DE MOTORES PRECARGADOS ======");

    for (int i = 0; i < arrayMotoresPrecargados.tamanno; i++) {
        Motor* motor = (Motor*) arrayMotoresPrecargados.datos[i];
        if (!motor) continue;

        mvprintw(fila++, 5, "---------------------------------------------");
        mvprintw(fila++, 5, "ID Motor (Pieza): %d", motor->id_pieza);
        mvprintw(fila++, 5, "ID Usuario:       %d", motor->id_usuario);
        mvprintw(fila++, 5, "Modelo:           %s", motor->modelo);
        mvprintw(fila++, 5, "Fabricante:       %s", motor->fabricante);
        mvprintw(fila++, 5, "Año:              %d", motor->anno);
        mvprintw(fila++, 5, "Carro Asociado:   %s", motor->carroAsociado);
        mvprintw(fila++, 5, "Cilindrada:       %.2f L", motor->cilindrada);
        mvprintw(fila++, 5, "Compresión:       %.2f psi", motor->compresionOriginal);
        mvprintw(fila++, 5, "N° Serie:         %s", motor->numeroSerie);
        mvprintw(fila++, 5, "Combustible:      %s", tipoCombustibleToStr(motor->tipoCombustible));
        mvprintw(fila++, 5, "Material:         %s", motor->material);
        mvprintw(fila++, 5, "Medida Original:  %.2f mm", motor->medidaOriginal);
        mvprintw(fila++, 5, "Medida Actual:    %.2f mm", motor->medidaActual);

        if (motor->culata != NULL) {
            mvprintw(fila++, 7, "--- CULATA ---");
            mvprintw(fila++, 7, "N° Válvulas:      %d", motor->culata->numValvulas);
            mvprintw(fila++, 7, "Presión Prueba:   %.2f bar", motor->culata->presionPrueba);
            mvprintw(fila++, 7, "Fisuras:          %s", motor->culata->tieneFisuras ? "Sí" : "No");
            mvprintw(fila++, 7, "Altura Original:  %.2f mm", motor->culata->alturaOriginal);
            mvprintw(fila++, 7, "Altura Actual:    %.2f mm", motor->culata->alturaActual);
            mvprintw(fila++, 7, "Altura Mínima:    %.2f mm", motor->culata->alturaMinima);
        }

        if (motor->monoblock != NULL) {
            mvprintw(fila++, 7, "--- MONOBLOCK ---");
            mvprintw(fila++, 7, "N° Cilindros:     %d", motor->monoblock->numCilindros);
            mvprintw(fila++, 7, "Diámetro Cilindro:%.2f mm", motor->monoblock->diametroCilindro);
            mvprintw(fila++, 7, "Ovalización:      %.2f mm", motor->monoblock->ovalizacion);
            mvprintw(fila++, 7, "Alineación:       %.2f mm", motor->monoblock->alineacionCiguenal);
        }

        if (fila >= LINES - 8) {
            mvprintw(fila++, 5, "[Continuar con Enter...]");
            getch();
            clear();
            fila = 1;
        }
    }

    mvprintw(fila++, 5, "======= FIN DEL LISTADO =======");
    getch();
}

Culata culatasExistentes[10] = {
    {0, 0, 16, 1.0, 0, 0.12f, 0.05f, 140.0f, 139.88f, 139.80f, 1},
    {1, 0, 8, 1.2, 0, 0.04f, 0.03f, 125.0f, 124.96f, 124.90f, 0},
    {2, 0, 24, 0.9, 1, 0.25f, 0.06f, 148.0f, 147.70f, 147.50f, 2},
    {3, 0, 12, 1.1, 0, 0.10f, 0.04f, 135.0f, 134.90f, 134.85f, 1},
    {4, 0, 16, 1.0, 0, 0.03f, 0.05f, 142.0f, 141.97f, 141.80f, 0},
    {5, 0, 16, 0.95, 0, 0.14f, 0.05f, 139.0f, 138.86f, 138.80f, 1},
    {6, 0, 20, 0.9, 1, 0.30f, 0.07f, 150.0f, 149.50f, 149.40f, 2},
    {7, 0, 12, 1.1, 0, 0.08f, 0.04f, 137.0f, 136.92f, 136.80f, 1},
    {8, 0, 8, 1.2, 0, 0.05f, 0.05f, 128.0f, 127.95f, 127.90f, 0},
    {9, 0, 24, 0.8, 1, 0.28f, 0.06f, 146.0f, 145.65f, 145.50f, 2}
};

Monoblock monoblocksExistentes[10] = {
    {0, 0, 4, 84.0f, 0.02f, 0.05f, 0.08f, 0.04f, 1},
    {1, 0, 6, 92.0f, 0.03f, 0.04f, 0.02f, 0.03f, 0},
    {2, 0, 8, 96.0f, 0.06f, 0.07f, 0.14f, 0.05f, 2},
    {3, 0, 4, 81.0f, 0.01f, 0.03f, 0.03f, 0.03f, 0},
    {4, 0, 6, 89.0f, 0.02f, 0.04f, 0.05f, 0.04f, 1},
    {5, 0, 4, 86.0f, 0.015f, 0.035f, 0.09f, 0.04f, 1},
    {6, 0, 6, 90.0f, 0.04f, 0.06f, 0.12f, 0.06f, 2},
    {7, 0, 8, 102.0f, 0.05f, 0.07f, 0.03f, 0.03f, 0},
    {8, 0, 4, 78.0f, 0.01f, 0.02f, 0.02f, 0.02f, 0},
    {9, 0, 6, 91.0f, 0.025f, 0.03f, 0.13f, 0.05f, 2}
};
//Creo que no voy a necesitar esto
Motor motoresExistentesCONCulatasAsignadas[10] = {
    {
        0, 0,
        "Duratec 2.0",
        "Ford",
        2012,
        "Focus",
        2.0f,
        130.0f,
        "FD123456",
        GASOLINA,
        &culatasExistentes[0],
        &monoblocksExistentes[0],
        "Aluminio",
        84.0f,
        83.9f
    },
    {
        1, 1,
        "Vortec 4800",
        "Chevrolet",
        2010,
        "Silverado",
        4.8f,
        150.0f,
        "CHV09876",
        GASOLINA,
        &culatasExistentes[1],
        &monoblocksExistentes[1],
        "Hierro",
        92.0f,
        91.98f
    },
    {
        2, 2,
        "EcoBoost 1.5",
        "Ford",
        2018,
        "Escape",
        1.5f,
        140.0f,
        "FRD45678",
        GASOLINA,
        &culatasExistentes[2],
        &monoblocksExistentes[2],
        "Aluminio",
        79.0f,
        78.8f
    },
    {
        3, 3,
        "Cummins 6.7",
        "Cummins",
        2016,
        "RAM 2500",
        6.7f,
        195.0f,
        "CMS23456",
        DIESEL,
        &culatasExistentes[3],
        &monoblocksExistentes[3],
        "Hierro fundido",
        107.0f,
        106.97f
    },
    {
        4, 4,
        "SkyActiv-G 2.5",
        "Mazda",
        2020,
        "Mazda6",
        2.5f,
        160.0f,
        "MZD67890",
        GASOLINA,
        &culatasExistentes[4],
        &monoblocksExistentes[4],
        "Aluminio",
        89.0f,
        88.95f
    },
    {
        5, 5,
        "1KD-FTV",
        "Toyota",
        2013,
        "Hilux",
        3.0f,
        175.0f,
        "TYT56473",
        DIESEL,
        &culatasExistentes[5],
        &monoblocksExistentes[5],
        "Hierro",
        95.0f,
        94.85f
    },
    {
        6, 6,
        "PowerStroke 6.4",
        "Ford",
        2009,
        "F-250",
        6.4f,
        200.0f,
        "PWS98765",
        DIESEL,
        &culatasExistentes[6],
        &monoblocksExistentes[6],
        "Hierro fundido",
        104.0f,
        103.87f
    },
    {
        7, 7,
        "K20A",
        "Honda",
        2007,
        "Civic Type-R",
        2.0f,
        210.0f,
        "HND13579",
        GASOLINA,
        &culatasExistentes[7],
        &monoblocksExistentes[7],
        "Aluminio",
        86.0f,
        85.98f
    },
    {
        8, 8,
        "N57D30",
        "BMW",
        2015,
        "Serie 5",
        3.0f,
        175.0f,
        "BMW24681",
        DIESEL,
        &culatasExistentes[8],
        &monoblocksExistentes[8],
        "Aluminio reforzado",
        84.0f,
        83.95f
    },
    {
        9, 9,
        "F20C",
        "Honda",
        2005,
        "S2000",
        2.0f,
        220.0f,
        "HND12345",
        GASOLINA,
        &culatasExistentes[9],
        &monoblocksExistentes[9],
        "Aluminio",
        87.0f,
        86.94f
    }
};

Motor motoresExistentesSINCulatasAsignadas[10] = {
    {
        0, 0,
        "Duratec 2.0",
        "Ford",
        2012,
        "Focus",
        2.0f,
        130.0f,
        "FD123456",
        GASOLINA,
        NULL,
        NULL,
        "Aluminio",
        84.0f,
        83.9f
    },
    {
        1, 0,
        "Vortec 4800",
        "Chevrolet",
        2010,
        "Silverado",
        4.8f,
        150.0f,
        "CHV09876",
        GASOLINA,
        NULL,
        NULL,
        "Hierro",
        92.0f,
        91.98f
    },
    {
        2, 0,
        "EcoBoost 1.5",
        "Ford",
        2018,
        "Escape",
        1.5f,
        140.0f,
        "FRD45678",
        GASOLINA,
        NULL,
        NULL,
        "Aluminio",
        79.0f,
        78.8f
    },
    {
        3, 0,
        "Cummins 6.7",
        "Cummins",
        2016,
        "RAM 2500",
        6.7f,
        195.0f,
        "CMS23456",
        DIESEL,
        NULL,
        NULL,
        "Hierro fundido",
        107.0f,
        106.97f
    },
    {
        4, 0,
        "SkyActiv-G 2.5",
        "Mazda",
        2020,
        "Mazda6",
        2.5f,
        160.0f,
        "MZD67890",
        GASOLINA,
        NULL,
        NULL,
        "Aluminio",
        89.0f,
        88.95f
    },
    {
        5, 0,
        "1KD-FTV",
        "Toyota",
        2013,
        "Hilux",
        3.0f,
        175.0f,
        "TYT56473",
        DIESEL,
        NULL,
        NULL,
        "Hierro",
        95.0f,
        94.85f
    },
    {
        6, 0,
        "PowerStroke 6.4",
        "Ford",
        2009,
        "F-250",
        6.4f,
        200.0f,
        "PWS98765",
        DIESEL,
        NULL,
        NULL,
        "Hierro fundido",
        104.0f,
        103.87f
    },
    {
        7, 0,
        "K20A",
        "Honda",
        2007,
        "Civic Type-R",
        2.0f,
        210.0f,
        "HND13579",
        GASOLINA,
        NULL,
        NULL,
        "Aluminio",
        86.0f,
        85.98f
    },
    {
        8, 0,
        "N57D30",
        "BMW",
        2015,
        "Serie 5",
        3.0f,
        175.0f,
        "BMW24681",
        DIESEL,
        NULL,
        NULL,
        "Aluminio reforzado",
        84.0f,
        83.95f
    },
    {
        9, 0,
        "F20C",
        "Honda",
        2005,
        "S2000",
        2.0f,
        220.0f,
        "HND12345",
        GASOLINA,
        NULL,
        NULL,
        "Aluminio",
        87.0f,
        86.94f
    }
};