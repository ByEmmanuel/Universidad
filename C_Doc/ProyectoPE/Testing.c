//Testin
#include "Testing.h"

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#include "LogicaNegocio.h"
#include "SystemLogs.h"
#include "UserInterface.h"
#include "UsuarioDTO.h"

void testing(int tipoDeTesting) {
    generarSystemLog(1, "Login", "Ninguno", "-1", INFO, 1, "Login", "testing", HTTP_OK);
    if (tipoDeTesting) {
        int cantidadMotores = sizeof(motoresExistentesSINCulatasAsignadas) / sizeof(Motor);


        printf("\n------TESTING MODE ON------ %d ", tipoDeTesting);
        switch (tipoDeTesting) {
            case 1:
                agregarUsuarios();
                break;
            case 2:


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
    const Usuario usuario1 = inicializarUsuario(0, "00001", "Usuario1", "Apellido 1", 1234567890, "EmailPrueba1@1",
                                                "Contacto1");
    guardarUsuarioArray(usuario1);

    const Usuario usuario2 = inicializarUsuario(1, "00002", "Usuario2", "Apellido 2", 1987654321, "EmailPrueba2@2",
                                                "Contacto2");
    guardarUsuarioArray(usuario2);

    const Usuario usuario3 = inicializarUsuario(2, "00003", "Usuario3", "Apellido 3", 2746297201, "emailPrueba3@3",
                                                "Contacto3");
    guardarUsuarioArray(usuario3);
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
            void **nuevoArray = realloc(arrayMotoresPrecargados.datos, nuevaCapacidad * sizeof(void *));
            if (!nuevoArray) {
                imprimirMensaje(10, 10, "Error al redimensionar el array de motores precargados");
                generarSystemLog(motores[i].id_usuario, "Add Motor arrayMotores", "Precarga", motores[i].numeroSerie,
                                 WARN, 0, "PrecargarMotor", "precargarMotoresDB", HTTP_BAD_REQUEST);
                return -1;
            }
            arrayMotoresPrecargados.datos = nuevoArray;
            arrayMotoresPrecargados.capacidad = nuevaCapacidad;
        }
        generarSystemLog(motores[i].id_usuario, "Add Motor arrayMotores", "Precarga", motores[i].numeroSerie, INFO, 1,
                         "PrecargarMotor", "precargarMotoresDB", HTTP_OK);
        arrayMotoresPrecargados.datos[arrayMotoresPrecargados.tamanno++] = &motores[i];
        setIdPiezaGlobal(getIdPiezaGlobal() + 1);
    }
    return 1;
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

            .medidaOriginal = 82.50f,
            .medidaActual = 82.40f,

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

            .medidaOriginal = 86.0f,
            .medidaActual = 85.98f,

        },
    };


    const int id_usuario = 0, id_usuario_2 = 1;
    Motor *motorUsuario_1 = inicializarMotor(motores_registrados[0], id_usuario, 0, 0, 0);
    Culata *pzc = inicializarCulata(16, 10, 2, 2, .124f, .123f, .120f, id_usuario, -1);
    float diametros_cilindro[] = {79.0f, 79.0f, 79.0f, 79.0f};
    float conicidades[] = {0.01f, 0.015f, 0.012f, 0.014f};
    float diametros_bancadas[] = {55.0f, 55.0f, 55.0f, 55.0f, 55.0f};
    float desalineacion_bancadas[] = {0.01f, 0.008f, 0.009f, 0.007f, 0.01f};

    Monoblock *mono = inicializarMonoblock(
        -1,
        1,
        4,
        diametros_cilindro,
        conicidades,
        5,
        diametros_bancadas,
        desalineacion_bancadas,
        0.02f,
        0.03f,
        0b00000110,
        "1ZZFE-TRD-987654",
        "Se observó desgaste uniforme, requiere rectificado",
        1
    );


    guardarMotorArray(motorUsuario_1, id_usuario);


    guardarPiezaArray(mono, id_usuario, "monoblock");

    Usuario *usuario1 = obtenerUsuarioByIdUsuario(id_usuario);
    asignarMotorUsuario(usuario1, motorUsuario_1);


    asignarPiezaMotor(usuario1, mono, 2);


    Motor *motorUsuario_2 = inicializarMotor(motores_registrados[1], id_usuario_2, 1, 0, 0);
    Culata *pzc2 = inicializarCulata(18, 12, 1, 14, .340f, .338f, .339f, id_usuario_2, -2);
    float diametros_cilindroDos[] = {137.0f, 137.1f, 137.0f, 137.2f, 137.1f, 137.0f};
    float conicidadesDos[] = {0.025f, 0.027f, 0.022f, 0.021f, 0.024f, 0.025f};
    float diametros_bancadasDos[] = {78.0f, 78.0f, 78.0f, 78.0f, 78.0f, 78.0f, 78.0f};
    float desalineacion_bancadasDos[] = {0.015f, 0.012f, 0.014f, 0.016f, 0.013f, 0.014f, 0.015f};

    Monoblock *mono2 = inicializarMonoblock(
        -1,
        2,
        6,
        diametros_cilindroDos,
        conicidadesDos,
        7,
        diametros_bancadasDos,
        desalineacion_bancadasDos,
        0.035f,
        0.04f,
        0b00001101,
        "ISX15-456789-CUMMINS",
        "Ovalización fuera de norma, bancadas desalineadas",
        2
    );
    guardarMotorArray(motorUsuario_2, id_usuario_2);


    guardarPiezaArray(mono2, id_usuario_2, "monoblock");
    Usuario *usuario2 = obtenerUsuarioByIdUsuario(id_usuario_2);
    asignarMotorUsuario(usuario2, motorUsuario_2);

    asignarPiezaMotor(usuario2, mono2, 2);

    setIdPiezaGlobal(getIdPiezaGlobal() + 2);
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
        Motor *motor = (Motor *) arrayMotoresPrecargados.datos[i];
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

#include <stdlib.h>
#include <string.h>


Monoblock monoblocksExistentes[10];


void inicializarMonoblocksExistentes() { {
        static float cilindros0[] = {83.02f, 83.01f, 83.03f, 83.02f};
        static float bancadas0[] = {60.01f, 60.00f, 60.02f, 60.01f, 60.00f};
        static char serie0[] = "FD123456";
        monoblocksExistentes[0] = (Monoblock){
            .id_pieza = 100,
            .id_usuario = 1,
            .numCilindros = 4,
            .diametroCilindro = cilindros0,
            .num_bancadas = 5,
            .diametro_bancadas = bancadas0,
            .ovalizacion_max = 0.01f,


            .planitud_superficie = 0.02f,
            .flags = FLAG_CILINDROS_OK | FLAG_BANCADAS_OK | FLAG_SUPERFICIE_PLANA,
            .numero_serie = serie0,
            .observaciones = "Monoblock en buen estado, apto para uso",
            .estado_diagnostico = 0
        };
    } {
        static float cilindros1[] = {92.05f, 92.07f, 92.06f, 92.08f, 92.05f, 92.06f};
        static float bancadas1[] = {65.03f, 65.04f, 65.02f, 65.05f, 65.03f, 65.04f, 65.02f};
        static char serie1[] = "AB654321";
        monoblocksExistentes[1] = (Monoblock){
            .id_pieza = 101,
            .id_usuario = 2,
            .numCilindros = 6,
            .diametroCilindro = cilindros1,
            .num_bancadas = 7,
            .diametro_bancadas = bancadas1,
            .ovalizacion_max = 0.03f,


            .planitud_superficie = 0.03f,
            .flags = FLAG_BANCADAS_OK | FLAG_SUPERFICIE_PLANA,
            .numero_serie = serie1,
            .observaciones = "Cilindros con desgaste, requiere rectificación",
            .estado_diagnostico = 1
        };
    } {
        static float cilindros2[] = {96.10f, 96.12f, 96.09f, 96.11f, 96.08f, 96.10f, 96.13f, 96.09f};
        static float bancadas2[] = {70.05f, 70.07f, 70.06f, 70.08f, 70.05f, 70.06f, 70.04f, 70.07f, 70.05f};
        static char serie2[] = "XY789012";
        monoblocksExistentes[2] = (Monoblock){
            .id_pieza = 102,
            .id_usuario = 3,
            .numCilindros = 8,
            .diametroCilindro = cilindros2,
            .num_bancadas = 9,
            .diametro_bancadas = bancadas2,
            .ovalizacion_max = 0.06f,


            .planitud_superficie = 0.06f,
            .flags = FLAG_FISURAS_DETECTADAS,
            .numero_serie = serie2,
            .observaciones = "Fisuras detectadas, requiere reconstruccion",
            .estado_diagnostico = 2
        };
    } {
        static float cilindros3[] = {81.01f, 81.00f, 81.02f, 81.01f};
        static float bancadas3[] = {58.00f, 58.01f, 58.00f, 58.02f, 58.01f};
        static char serie3[] = "LM456789";
        monoblocksExistentes[3] = (Monoblock){
            .id_pieza = 103,
            .id_usuario = 4,
            .numCilindros = 4,
            .diametroCilindro = cilindros3,
            .num_bancadas = 5,
            .diametro_bancadas = bancadas3,
            .ovalizacion_max = 0.01f,


            .planitud_superficie = 0.01f,
            .flags = FLAG_CILINDROS_OK | FLAG_BANCADAS_OK | FLAG_SUPERFICIE_PLANA,
            .numero_serie = serie3,
            .observaciones = "Monoblock en excelente estado",
            .estado_diagnostico = 0
        };
    } {
        static float cilindros4[] = {89.04f, 89.05f, 89.06f, 89.04f, 89.05f, 89.03f};
        static float bancadas4[] = {62.02f, 62.03f, 62.01f, 62.04f, 62.02f, 62.03f, 62.01f};
        static char serie4[] = "PQ987654";
        monoblocksExistentes[4] = (Monoblock){
            .id_pieza = 104,
            .id_usuario = 5,
            .numCilindros = 6,
            .diametroCilindro = cilindros4,
            .num_bancadas = 7,
            .diametro_bancadas = bancadas4,
            .ovalizacion_max = 0.02f,


            .planitud_superficie = 0.04f,
            .flags = FLAG_BANCADAS_OK,
            .numero_serie = serie4,
            .observaciones = "Superficie no plana, requiere rectificación",
            .estado_diagnostico = 1
        };
    } {
        static float cilindros5[] = {86.03f, 86.04f, 86.02f, 86.03f};
        static float bancadas5[] = {59.01f, 59.02f, 59.00f, 59.01f, 59.02f};
        static char serie5[] = "JK321098";
        monoblocksExistentes[5] = (Monoblock){
            .id_pieza = 105,
            .id_usuario = 6,
            .numCilindros = 4,
            .diametroCilindro = cilindros5,
            .num_bancadas = 5,
            .diametro_bancadas = bancadas5,
            .ovalizacion_max = 0.015f,


            .planitud_superficie = 0.03f,
            .flags = FLAG_CILINDROS_OK | FLAG_SUPERFICIE_PLANA,
            .numero_serie = serie5,
            .observaciones = "Bancadas desalineadas, rectificar",
            .estado_diagnostico = 1
        };
    } {
        static float cilindros6[] = {90.08f, 90.09f, 90.07f, 90.10f, 90.08f, 90.09f};
        static float bancadas6[] = {64.04f, 64.05f, 64.03f, 64.06f, 64.04f, 64.05f, 64.03f};
        static char serie6[] = "UV123987";
        monoblocksExistentes[6] = (Monoblock){
            .id_pieza = 106,
            .id_usuario = 7,
            .numCilindros = 6,
            .diametroCilindro = cilindros6,
            .num_bancadas = 7,
            .diametro_bancadas = bancadas6,
            .ovalizacion_max = 0.04f,


            .planitud_superficie = 0.05f,
            .flags = FLAG_FISURAS_DETECTADAS,
            .numero_serie = serie6,
            .observaciones = "Fisuras menores, reconstruir",
            .estado_diagnostico = 2
        };
    } {
        static float cilindros7[] = {102.01f, 102.00f, 102.02f, 102.01f, 102.00f, 102.01f, 102.02f, 102.00f};
        static float bancadas7[] = {72.00f, 72.01f, 72.00f, 72.02f, 72.01f, 72.00f, 72.01f, 72.02f, 72.00f};
        static char serie7[] = "WX456321";
        monoblocksExistentes[7] = (Monoblock){
            .id_pieza = 107,
            .id_usuario = 8,
            .numCilindros = 8,
            .diametroCilindro = cilindros7,
            .num_bancadas = 9,
            .diametro_bancadas = bancadas7,
            .ovalizacion_max = 0.01f,


            .planitud_superficie = 0.02f,
            .flags = FLAG_CILINDROS_OK | FLAG_BANCADAS_OK | FLAG_SUPERFICIE_PLANA,
            .numero_serie = serie7,
            .observaciones = "Monoblock en buen estado, sin intervención",
            .estado_diagnostico = 0
        };
    } {
        static float cilindros8[] = {78.00f, 78.01f, 78.00f, 78.02f};
        static float bancadas8[] = {57.01f, 57.00f, 57.01f, 57.02f, 57.00f};
        static char serie8[] = "YZ789654";
        monoblocksExistentes[8] = (Monoblock){
            .id_pieza = 108,
            .id_usuario = 9,
            .numCilindros = 4,
            .diametroCilindro = cilindros8,
            .num_bancadas = 5,
            .diametro_bancadas = bancadas8,
            .ovalizacion_max = 0.01f,


            .planitud_superficie = 0.01f,
            .flags = FLAG_CILINDROS_OK | FLAG_BANCADAS_OK | FLAG_SUPERFICIE_PLANA,
            .numero_serie = serie8,
            .observaciones = "Monoblock en excelente estado",
            .estado_diagnostico = 0
        };
    } {
        static float cilindros9[] = {91.07f, 91.08f, 91.06f, 91.09f, 91.07f, 91.08f};
        static float bancadas9[] = {63.05f, 63.06f, 63.04f, 63.07f, 63.05f, 63.06f, 63.04f};
        static char serie9[] = "KL012345";
        monoblocksExistentes[9] = (Monoblock){
            .id_pieza = 109,
            .id_usuario = 10,
            .numCilindros = 6,
            .diametroCilindro = cilindros9,
            .num_bancadas = 7,
            .diametro_bancadas = bancadas9,
            .ovalizacion_max = 0.035f,


            .planitud_superficie = 0.05f,
            .flags = FLAG_FISURAS_DETECTADAS,
            .numero_serie = serie9,
            .observaciones = "Fisuras detectadas, reconstrucción necesaria",
            .estado_diagnostico = 2
        };
    }
}

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
