//RegistrarMotor
#include <curses.h>
#include <stdlib.h>
#include <tgmath.h>
#include <time.h>

#include "UsuarioDTO.h"
#include "LogicaNegocio.h"
#include "Testing.h"
#include "UserInterface.h"
#include "Util.h"

int registrarMotor() {
    int y = 2;

    int opcUsr = mostrarMenu(7, "¿Tienes el numero de serie del motor?");
    int id_usuario = 0;
    RETURN_IF_ESC(opcUsr);
    if (opcUsr == 1) {
        char *numeroDeSerieUsuario = leerStringSeguro(10, 10, 20, "Ingrese el numero de serie del motor");
        if (numeroDeSerieUsuario == NULL)return -1;
        Motor *motorUsr = obtenerMotorPorNumeroDeSerie(&arrayMotoresPrecargados, numeroDeSerieUsuario);
        if (motorUsr != NULL) {
            clear();
            mvprintw(2, 10, "¿Deseas cargar este motor al usuario?, Asi ya no tendras que registrar un nuevo motor");

            imprimirDetallesMotor(motorUsr);


            int opcUsr2 = mostrarMenu(7, " ");
            if (opcUsr2 == 1) {
                clear();
                id_usuario = obtenerIdSiExisteUsuario(10, 10);
                RETURN_IF_ESC(id_usuario);
                Usuario *usuario = obtenerUsuarioByIdUsuario(id_usuario);

                Motor *motorClonado = clonarMotor(motorUsr, id_usuario);

                usuario->motor = motorClonado;
                guardarMotorArray(motorClonado, id_usuario);

                clear();
                mvprintw(10, 10, "Motor asignado correctamente al usuario con id %d", id_usuario);
                getch();
                return -1;
            }
        }
    }


    clear();
    int id_pieza = getIdPiezaGlobal();
    id_usuario = obtenerIdSiExisteUsuario(10, 10);
    RETURN_IF_ESC(id_usuario);
    clear();
    mvprintw(2, 10, "Estas agregando un motor.");
    char *modelo = leerStringSeguro(y += 2, 10, 100, "Ingrese Modelo del Motor - String");
    if (modelo == NULL)return -1;
    char *fabricante = leerStringSeguro(y += 2, 10, 100, "Ingrese Fabricante del Motor - String");
    if (fabricante == NULL)return -1;
    char *carroAsociado = leerStringSeguro(y += 2, 10, 100, "Ingrese Carro Asociado - String");
    if (carroAsociado == NULL)return -1;
    char *material = leerStringSeguro(y += 2, 10, 30, "Ingrese Material de Motor - String");
    if (material == NULL) return -1;
    int anno = leerIntSeguro(y += 2, 10, 10, "Ingrese Año del Motor - Entero");
    float cilindrada = leerFloatSeguro(y += 2, 10, 10, "Ingrese Cilindrada (L) - Float");
    float compresionOriginal = leerFloatSeguro(y += 2, 10, 10, "Ingrese Compresión Original (psi) - Float");
    char *numeroSerie = leerStringSeguro(y += 2, 10, 50, "Ingrese Número de Serie - String");
    int tipoCombustible = mostrarMenu(6, "Seleccione Tipo de Combustible - Entero");

    float medidaOriginal = leerFloatSeguro(y += 2, 10, 10, "Ingrese Medida Original (mm) - Float");
    float medidaActual = leerFloatSeguro(y += 2, 10, 10, "Ingrese Medida Actual (mm) - Float");


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
        .medidaOriginal = medidaOriginal,
        .medidaActual = medidaActual,
    };
    Motor *motor = inicializarMotor(paramsmotor, id_usuario, getIdPiezaGlobal(), 0, 0);
    guardarMotorArray(motor, id_usuario);
    asignarMotorUsuario(obtenerUsuarioByIdUsuario(id_usuario), motor);

    if (mostrarMenu(7, "¿Deseas guardar este motor en la base de datos?") == 1
        && obtenerMotorPorNumeroDeSerie(&arrayMotoresUsuarios, numeroSerie) != NULL) {
        precargarMotoresDB(motor, 1);
        imprimirMensaje(10, 10, "El motor fue registrado al usuario y en la base de datos Correctamente");
        return 1;
    }
    imprimirMensaje(10, 10, "El motor fue registrado al usuario Correctamente");
    setIdPiezaGlobal(getIdPiezaGlobal() + 1);
    return 1;
};

int registrarCulata() {
    int y = 5;


    char *numeroDeSerieUsr = leerStringSeguro(10, 10, 25, "Ingrese numero de serie del motor asignado al cliente:");
    if (obtenerMotorPorNumeroDeSerie(&arrayMotoresUsuarios, numeroDeSerieUsr) != NULL) {
        const int id_usuario = obtenerIdSiExisteUsuario(13, 10);
        RETURN_IF_ESC(id_usuario);


        Usuario *usuario = obtenerUsuarioByIdUsuario(id_usuario);
        if (usuario == NULL) {
            imprimirMensaje(10, 10, "Ocurrió un problema al obtener los datos del usuario");
            return -1;
        }

        Motor *motor = usuario->motor;
        if (motor == NULL) {
            imprimirMensaje(10, 10, "El motor del usuario es NULL, por favor asigna un motor al usuario");
            return -1;
        }


        if (motor->culata == NULL) {
            clear();


            int numValvulas = leerIntSeguro(y += 2, 10, 50, "Ingrese numero Valvulas entero");

            double presionPrueba = leerFloatSeguro(y += 2, 10, 20, "Ingrese PresionPrueba float");


            int tieneFisuras = mostrarMenu(7, "¿Tiene Fisuras?");

            clear();

            float alturaOriginal = leerFloatSeguro(y += 2, 10, 20, "Ingrese medida original");
            float alturaActual = leerFloatSeguro(y += 2, 10, 20, "Ingrese la altura Actual");
            float alturaMinima = leerFloatSeguro(y += 2, 10, 20, "Ingrese altura minima");
            float tolerancia = leerFloatSeguro(y += 2, 10, 20, "Ingrese Tolerancia Maxima");


            int estadoPieza = evaluarEstadoCulata(alturaOriginal, alturaActual, alturaMinima, tolerancia);


            if (estadoPieza == -1) {
                imprimirMensaje(
                    10, 10, "La pieza necesita Rectificacion, porfavor ve al apartado de Servicio-Operaciones");
            } else if (estadoPieza == -2) {
                imprimirMensaje(
                    10, 10, "La pieza necesita Reeconstruccion, porfavor ve al apartado de Servicio-Operaciones");
            } else {
                imprimirMensaje(10, 10, "Se introdujeron datos erroneos, porfavor Introduce datos validos");
            }


            mvprintw(y += 2, 55, "Tiene Fisuras?: %d", tieneFisuras);

            getch();
            Culata *pzc = inicializarCulata(getIdPiezaGlobal(), numValvulas, presionPrueba, tieneFisuras,
                                            alturaOriginal, alturaActual, alturaMinima, id_usuario, estadoPieza);
            guardarPiezaArray(pzc, id_usuario, "culata");
            usuario->motor->culata = pzc;
            setIdPiezaGlobal(getIdPiezaGlobal() + 1);
            imprimirMensaje(10, 10, "Culata Creada correctamente :)");
            return 1;
        }
        imprimirMensaje(
            5, 5, "El usuario no es NULL, El motor no es NULL, La culata no es NULL. YA TIENE TODO AGREGADO ¿?¿?¿");
    }
    return -1;
}

void imprimirDetallesMotor(Motor *motor) {
    int fila = 5;

    if (motor == NULL) {
        mvprintw(5, 35, "Error: El motor es NULL.");
        getch();
        return;
    }

    mvprintw(fila++, 35, "==============================================");
    mvprintw(fila++, 35, "INFORMACION DE LA PIEZA / MOTOR");
    mvprintw(fila++, 35, "==============================================");

    mvprintw(fila++, 35, "ID Pieza: %d", motor->id_pieza);
    mvprintw(fila++, 35, "ID Usuario: %d", motor->id_usuario);

    mvprintw(fila++, 35, "Modelo Motor: %s", motor->modelo ? motor->modelo : "(No definido)");

    if (motor->anno > 0)
        mvprintw(fila++, 35, "Anno Motor: %d", motor->anno);
    else
        mvprintw(fila++, 35, "Anno Motor: (No definido)");

    mvprintw(fila++, 35, "Carro asociado: %s", motor->carroAsociado ? motor->carroAsociado : "(No definido)");
    mvprintw(fila++, 35, "Fabricante: %s", motor->fabricante ? motor->fabricante : "(No definido)");
    mvprintw(fila++, 35, "Numero Serie: %s", motor->numeroSerie ? motor->numeroSerie : "(No definido)");

    mvprintw(fila++, 35, "Cilindrada: %.2f L", motor->cilindrada);
    mvprintw(fila++, 35, "Compresion Original: %.2f psi", motor->compresionOriginal);
    mvprintw(fila++, 35, "Combustible: %s", tipoCombustibleToStr(motor->tipoCombustible));
    mvprintw(fila++, 35, "Material: %s", motor->material);

    mvprintw(fila++, 35, "Medida Original: %.4f mm", motor->medidaOriginal);
    mvprintw(fila++, 35, "Medida Actual: %.4f mm", motor->medidaActual);

    if (motor->culata == NULL) {
        mvprintw(fila++, 35, "(Culata no asignada)");
    }
    if (motor->monoblock == NULL) {
        mvprintw(fila++, 35, "(Monoblock no asignado)");
    }


    getch();
}

void rectificarCulata(Culata *culata, int id_usuario) {
    if (culata != NULL && culata->id_usuario == id_usuario) {
        culata->operacionesMotor = 1;
    }
}


int registrarMonoblock() {
    int y = 5, y_2 = 5;

    char *numeroDeSerieUsr = leerStringSeguro(10, 10, 25, "Ingrese numero de serie del motor asignado al cliente:");
    if (obtenerMotorPorNumeroDeSerie(&arrayMotoresUsuarios, numeroDeSerieUsr) != NULL) {
        const int id_usuario = obtenerIdSiExisteUsuario(13, 10);
        RETURN_IF_ESC(id_usuario);

        Usuario *usuario = obtenerUsuarioByIdUsuario(id_usuario);
        if (usuario == NULL) {
            imprimirMensaje(10, 10, "Ocurrió un problema al obtener los datos del usuario");
            return -1;
        }

        Motor *motor = usuario->motor;
        if (motor == NULL) {
            imprimirMensaje(10, 10, "El motor del usuario es NULL, por favor asigna un motor al usuario");
            return -1;
        }

        clear();
        int numCilindros = leerIntSeguro(y++, 5, 10, "Ingrese numero de cilindros");
        int num_bancadas = leerIntSeguro(y++, 5, 10, "Ingrese numero de bancadas");

        float *diametros = malloc(numCilindros * sizeof(float));
        float *conicidades = malloc(numCilindros * sizeof(float));
        float *desalineaciones = malloc(numCilindros * sizeof(float));
        float *bancadas = malloc(num_bancadas * sizeof(float));

        for (int i = 0; i < numCilindros; i++) {
            char mensajeUno[50];
            sprintf(mensajeUno, "Diametro del cilindro %d", i + 1);
            diametros[i] = leerFloatSeguro(y++, 5, 10, mensajeUno);
        }
        for (int i = 0; i < numCilindros; i++) {
            char mensajeDos[50];
            sprintf(mensajeDos, "Conicidad del cilindro %d", i + 1);
            conicidades[i] = leerFloatSeguro(y++, 5, 10, mensajeDos);
        }
        for (int i = 0; i < numCilindros; i++) {
            char mensajeTres[50];
            sprintf(mensajeTres, "Desalineacion del cilindro %d", i + 1);
            desalineaciones[i] = leerFloatSeguro(y++, 5, 10, mensajeTres);
        }

        for (int i = 0; i < num_bancadas; i++) {
            char mensajeCuatro[35];
            sprintf(mensajeCuatro, "Diametro de bancada %d", i + 1);
            bancadas[i] = leerFloatSeguro(y++, 5, 10, mensajeCuatro);
        }

        int flags = leerIntSeguro(y++, 5, 10, "Ingrese flag");
        int estado = leerIntSeguro(y++, 5, 10, "Ingrese estado");

        float oval = leerFloatSeguro(y++, 5, 10, "Ingrese oval");
        float planitud = leerFloatSeguro(y++, 5, 10, "Ingrese planitud");

        char *observaciones;
        if (mostrarMenu(7, "¿Desea agregar observaciones?")) {
            observaciones = leerStringSeguro(y++, 5, 100, "Ingrese Observaciones");
        } else {
            observaciones = " ";
        }


        int necesitaRectificacion = 0;
        int necesitaReconstruccion = 0;
        float grosorLaina = 0.0f;

        necesitaRectificacion |= evaluarDiametrosCilindros(diametros, numCilindros, y_2, &necesitaReconstruccion);
        y_2 += 3;
        necesitaRectificacion |= evaluarConicidadCilindros(conicidades, numCilindros, y_2);
        y_2++;
        necesitaRectificacion |= evaluarDesalineacionCilindros(desalineaciones, numCilindros, y_2);
        y_2++;
        necesitaRectificacion |= evaluarDiametrosBancadas(bancadas, num_bancadas, y_2);
        y_2++;
        necesitaRectificacion |= evaluarOvalidad(oval, y_2);
        y_2++;
        necesitaRectificacion |= evaluarPlanitud(planitud, y_2);
        y_2++;
        int necesitaLaina = evaluarJuegoAxial(y_2, &grosorLaina);
        y_2++;


        Monoblock *mono = inicializarMonoblock(
            0, id_usuario, numCilindros, diametros,
            conicidades, num_bancadas, bancadas,
            bancadas, oval, planitud, flags, numeroDeSerieUsr, observaciones, estado
        );

        clear();

        if (flags == -2 || necesitaReconstruccion) {
            mvprintw(y_2++, 5, "Monoblock requiere reconstruccion");
            mono->operacionesMonoblock = -2;
            if (necesitaLaina) {
                actualizarStockLaina(grosorLaina, -1);
                registrarUsoHerramienta("Micrometro", "Reconstrucción");
            }

            actualizarStockLaina(0.0f, -1);
        } else if (necesitaRectificacion) {
            mvprintw(y_2++, 5, "Monoblock requiere rectificacion");
            mono->operacionesMonoblock = -1;
            mvprintw(y_2++, 5, "Regresar");
        } else if (necesitaLaina) {
            mvprintw(y_2++, 5, "Monoblock solo requiere ajuste con laina");
            mono->operacionesMonoblock = -3;
        } else {
            mvprintw(y_2++, 5, "Monoblock dentro de tolerancias, no requiere accion");
            mono->operacionesMonoblock = 0;
        }

        guardarPiezaArray(mono, id_usuario, "monoblock");
        imprimirMensaje(10, 10, "Monoblock creado correctamente :)");
        usuario->motor->monoblock = mono;
        setIdPiezaGlobal(getIdPiezaGlobal() + 1);
        imprimirMensaje(10, 10, mono->numero_serie);

        free(desalineaciones);

        return 0;
    }
    return 1;
}

int evaluarDiametrosCilindros(const float *diametros, int numCilindros, int y, int *necesitaReconstruccion) {
    float toleranciaDiametro = 0.05f;
    float diametroNominal = 80.00f;
    int necesitaRectificacion = 0;

    for (int i = 0; i < numCilindros; i++) {
        float deltaD = fabs(diametros[i] - diametroNominal);
        if (deltaD > toleranciaDiametro) {
            necesitaRectificacion = 1;
            mvprintw(y++, 5, "Cilindro %d: Desgaste %.3f mm, requiere rectificación", i + 1, deltaD);
            if (deltaD > 0.5) {
                *necesitaReconstruccion = 1;
                mvprintw(y++, 5, "Cilindro %d: Desgaste severo, considerar reconstrucción", i + 1);
            }
        }
    }
    return necesitaRectificacion;
}


int evaluarConicidadCilindros(const float *conicidades, int numCilindros, int y) {
    float conicidadMax = 0.02f;
    int necesitaRectificacion = 0;

    for (int i = 0; i < numCilindros; i++) {
        if (conicidades[i] > conicidadMax) {
            necesitaRectificacion = 1;
            mvprintw(y++, 5, "Cilindro %d: Conicidad %.3f mm, requiere rectificación", i + 1, conicidades[i]);
        }
    }
    return necesitaRectificacion;
}


int evaluarDesalineacionCilindros(float *desalineaciones, int numCilindros, int y) {
    float desalineacionMax = 0.01f;
    int necesitaRectificacion = 0;

    for (int i = 0; i < numCilindros; i++) {
        if (desalineaciones[i] > desalineacionMax) {
            necesitaRectificacion = 1;
            mvprintw(y++, 5, "Cilindro %d: Desalineación %.3f mm, requiere rectificación", i + 1, desalineaciones[i]);
        }
    }
    return necesitaRectificacion;
}

int evaluarDiametrosBancadas(float *bancadas, int num_bancadas, int y) {
    float toleranciaBancada = 0.03f;
    float bancadaNominal = 50.00f;
    int necesitaRectificacion = 0;

    for (int i = 0; i < num_bancadas; i++) {
        float deltaB = fabs(bancadas[i] - bancadaNominal);
        if (deltaB > toleranciaBancada) {
            necesitaRectificacion = 1;
            mvprintw(y++, 5, "Bancada %d: Desgaste %.3f mm, requiere rectificación", i + 1, deltaB);
        }
    }
    return necesitaRectificacion;
}

int evaluarOvalidad(float oval, int y) {
    float ovalidadMax = 0.02f;
    int necesitaRectificacion = 0;

    if (oval > ovalidadMax) {
        necesitaRectificacion = 1;
        mvprintw(y++, 5, "Ovalidad %.3f mm, requiere rectificación", oval);
    }
    return necesitaRectificacion;
}

int evaluarPlanitud(float planitud, int y) {
    float planitudMax = 0.05f;
    int necesitaRectificacion = 0;

    if (planitud > planitudMax) {
        necesitaRectificacion = 1;
        mvprintw(y++, 5, "Planitud %.3f mm, requiere rectificación", planitud);
    }
    return necesitaRectificacion;
}

int evaluarJuegoAxial(int y, float *grosorLaina) {
    float juegoNominal = 0.15f;
    float juegoMedido = leerFloatSeguro(y++, 5, 10, "Ingrese juego axial de bancada (mm)");
    *grosorLaina = juegoMedido - juegoNominal;
    int necesitaLaina = 0;

    if (*grosorLaina > 0) {
        necesitaLaina = 1;
        mvprintw(y++, 5, "Instalar laina de %.3f mm para bancada", *grosorLaina);
    }
    return necesitaLaina;
}


void actualizarStockLaina(float grosor, int cantidad) {
    FILE *archivo = fopen("inventario.txt", "a");
    fprintf(archivo, "Laina,%.3f,%d\n", grosor, cantidad);
    fclose(archivo);
}

void registrarUsoHerramienta(char *idHerramienta, char *etapa) {
    FILE *archivo = fopen("herramientas.txt", "a");
    fprintf(archivo, "%s,%s,%ld\n", idHerramienta, etapa, time(NULL));
    fclose(archivo);
}
