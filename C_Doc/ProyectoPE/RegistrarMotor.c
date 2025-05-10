//
// Created by Jesus Emmanuel Garcia on 4/28/25.
//
#include <ncurses.h>

#include "UsuarioDTO.h"
#include "LogicaNegocio.h"
#include "Testing.h"
#include "UserInterface.h"
#include "Util.h"
int registrarMotor(){
    int y = 2;
    /** Preguntar si tiene numero de seria del motor,
    * si el numero de serie coincide con alguno de los precargados,
    *  Decirle que solamente ingrese los datos de la culata
    *  si no tiene numero serie o no coincide, llenar desde 0 el nuevo motor
    *
    *  este fokin funcionamiento necesitò mas tiempo del esperado -> por reglas de negocio
    */
    int opcUsr = mostrarMenu(7, "¿Tienes el numero de serie del motor?");
    int id_usuario = 0;
    RETURN_IF_ESC(opcUsr);
    if (opcUsr == 1){
        char* numeroDeSerieUsuario = leerStringSeguro(10, 10, 20, "Ingrese el numero de serie del motor");
        if (numeroDeSerieUsuario == NULL)return -1;
        Motor* motorUsr = obtenerMotorPorNumeroDeSerie(&arrayMotoresPrecargados, numeroDeSerieUsuario);
        if (motorUsr != NULL){

            clear();
            mvprintw(2,10,"¿Deseas cargar este motor al usuario?, Asi ya no tendras que registrar un nuevo motor");
            //AQUI
            imprimirDetallesMotor(motorUsr);
            //getch();

            int opcUsr2 = mostrarMenu(7," ");
            if (opcUsr2 == 1){
                clear();
                id_usuario =  obtenerIdSiExisteUsuario(10,10);
                RETURN_IF_ESC(id_usuario);
                Usuario* usuario = obtenerUsuarioByIdUsuario(id_usuario);

                Motor* motorClonado = clonarMotor(motorUsr, id_usuario);

                usuario->motor = motorClonado;
                guardarMotorArray(motorClonado, id_usuario);

                clear();
                mvprintw(10,10,"Motor asignado correctamente al usuario con id %d", id_usuario);
                getch();
                return -1;
            }
            /*
            clear();
            mvprintw(10, 10, "El motor ya esta registrado en el sistema");
            mvprintw(11, 10, "Por favor ve a la seccion de Medidas ");
            getch();
            mvprintw(12, 10, "-> Selecciona Pieza, e introduce este mismo numero de serie del motor");
            return -1; //Si existe el numero de serie
            */
        }
    }

    //Ingreso datos motor
    // Variables auxiliares
    clear();
    int id_pieza = id_piezaGlobal;
    id_usuario =  obtenerIdSiExisteUsuario(10,10);
    RETURN_IF_ESC(id_usuario);
    clear();
    mvprintw(2,10,"Estas agregando un motor.");
    char* modelo = leerStringSeguro(y += 2, 10, 100, "Ingrese Modelo del Motor - String");
    if (modelo == NULL)return -1;
    char* fabricante = leerStringSeguro(y += 2, 10, 100, "Ingrese Fabricante del Motor - String");
    if (fabricante == NULL)return -1;
    char* carroAsociado = leerStringSeguro(y += 2, 10, 100, "Ingrese Carro Asociado - String");
    if (carroAsociado == NULL)return -1;
    char* material = leerStringSeguro(y += 2, 10, 30, "Ingrese Material de Motor - String");
    if (material == NULL) return -1;
    int anno = leerIntSeguro(y += 2, 10, 10, "Ingrese Año del Motor - Entero");
    float cilindrada = leerFloatSeguro(y += 2, 10, 10, "Ingrese Cilindrada (L) - Float");
    float compresionOriginal = leerFloatSeguro(y += 2, 10, 10, "Ingrese Compresión Original (psi) - Float");
    char* numeroSerie = leerStringSeguro(y += 2, 10, 50, "Ingrese Número de Serie - String");
    int tipoCombustible = mostrarMenu(6, "Seleccione Tipo de Combustible - Entero");

    //float desgaste = leerFloatSeguro(y += 2, 10, 10, "Ingrese Desgaste (%) - Float") / 100.0f;
    //float tolerancia = leerFloatSeguro(y += 2, 10, 10, "Ingrese Tolerancia (mm) - Float");
    float medidaOriginal = leerFloatSeguro(y += 2, 10, 10, "Ingrese Medida Original (mm) - Float");
    float medidaActual = leerFloatSeguro(y += 2, 10, 10, "Ingrese Medida Actual (mm) - Float");

    // Variables que dependen de cálculo y tienen que ir aparte

    // Ahora sí: inicializas la estructura
    imprimirMensaje(5,5,"Depuracion 0");
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
    imprimirMensaje(5,5,"Depuracion 1");
    Motor* motor = inicializarMotor(paramsmotor, id_usuario, id_piezaGlobal, 0, 0);
    imprimirMensaje(5,5,"Depuracion 2");
    guardarMotorArray(motor, id_usuario);
    imprimirMensaje(5,5,"Depuracion 3");
    asignarMotorUsuario(obtenerUsuarioByIdUsuario(id_usuario), motor);
    imprimirMensaje(5,5,"Depuracion 4");
    //liberarMotor(motor);

    if (mostrarMenu(7, "¿Deseas guardar este motor en la base de datos?") == 1
        && obtenerMotorPorNumeroDeSerie(&arrayMotoresUsuarios, numeroSerie) != NULL){
        precargarMotoresDB(motor, 1);
        imprimirMensaje(10, 10, "El motor fue registrado al usuario y en la base de datos Correctamente");
        return 1;
    }
    //Mensaje de exito
    imprimirMensaje(10, 10, "El motor fue registrado al usuario Correctamente");
    id_piezaGlobal++;
    return 1;
};
//Le vas a registrar la culata al motor del usuario
int registrarCulata(){
    //Si si tienes el nuemero de serie -> Agregar solo datos culata
    int y = 5;
    //Por corregir
    // IDENTIFICADOR UNICO DE LA PIEZA -> TODAS LAS PIEZAS DE UN MOTOR DEBEN CONTENER EL MISMO ID
    // Número de válvulas en la culata
    // Presión medida en prueba hidráulica (bar)
    // 1 = Sí, 0 = No (fisuras detectadas)
    // Altura original de la culata (mm)
    // Altura actual de la culata tras desgaste (mm)
    // Altura mínima aceptable (según fabricante) (mm)

    //Esto debe ser el folio, pero esta agregado asi por temas de testeo
    //if (mostrarMenu(7, "¿Tienes el numero de serie del motor?") == 1){
    char* numeroDeSerieUsr = leerStringSeguro(10,10,25,"Ingrese numero de serie del motor asignado al cliente:");
    if (obtenerMotorPorNumeroDeSerie(&arrayMotoresUsuarios, numeroDeSerieUsr)  != NULL){
    //clear();
    const int id_usuario = obtenerIdSiExisteUsuario(13,10);
    RETURN_IF_ESC(id_usuario);
    //Esta linea impide que si el usuario no existe no se hara nada

        Usuario* usuario = obtenerUsuarioByIdUsuario(id_usuario);
        if (usuario == NULL) {
            imprimirMensaje(10, 10, "Ocurrió un problema al obtener los datos del usuario");
            return -1;
        }

        Motor* motor = usuario->motor;
        if (motor == NULL) {
            imprimirMensaje(10, 10, "El motor del usuario es NULL, por favor asigna un motor al usuario");
            return -1;
        }
        //Motor* motorUsuario = obtenerMotorPorNumeroDeSerie(&arrayMotoresUsuarios,numeroDeSerieUsr);
        //Motor* motorUsuario = obtenerMotorPorNumeroDeSerie(leerStringSeguro(10,10,30,"Ingrese numero de serie del motor"));
        if (motor->culata == NULL){
            clear();
            //--------------------------- MEDIDAS CULATA ---------------------------
            // Ingresar numValvulas
            int numValvulas = leerIntSeguro(y += 2, 10, 50, "Ingrese numero Valvulas entero");
            // Ingresar presionPrueba
            double presionPrueba = leerFloatSeguro(y += 2, 10, 20, "Ingrese PresionPrueba float");
            // Ingresar tipoCombustible
            //tipo_combustible = mostrarMenu(6, "Ingrese tipo de combustible");
            int tieneFisuras = mostrarMenu(7, "¿Tiene Fisuras?");
            //rectificacion = mostrarMenu(7,"¿Necesita Rectificación?");
            clear();
            //mvprintw(y, 55, "Rectificacion?: %d", rectificacion);
            float alturaOriginal = leerFloatSeguro(y += 2, 10, 20, "Ingrese medida original");
            float alturaActual = leerFloatSeguro(y += 2, 10, 20, "Ingrese la altura Actual");
            float alturaMinima = leerFloatSeguro(y += 2, 10, 20, "Ingrese altura minima");
            float tolerancia = leerFloatSeguro(y += 2, 10, 20, "Ingrese Tolerancia Maxima");

            //EstadoPieza evaluarEstadoPieza(float medidaOriginal, float medidaActual, float toleranciaMax) {
            int estadoPieza = evaluarEstadoCulata(alturaOriginal, alturaActual, alturaMinima,  tolerancia);

            /**
             *RECTIFICACION
            alturaOriginal = 130.0;
            alturaActual   = 128.9;
            alturaMinima   = 128.5;
            tolerancia     = 1.5;
            // desgaste = 1.1 → válido

            alturaOriginal = 130.0;
            alturaActual   = 127.0;
            alturaMinima   = 127.5;
            tolerancia     = 2.0;
            alturaActual < alturaMinima → reconstrucción
             */
            if (estadoPieza == -1){
                imprimirMensaje(10,10,"La pieza necesita Rectificacion, porfavor ve al apartado de Servicio-Operaciones");
            }else if (estadoPieza == -2){
                imprimirMensaje(10,10,"La pieza necesita Reeconstruccion, porfavor ve al apartado de Servicio-Operaciones");
            }else {
                imprimirMensaje(10,10,"Se introdujeron datos erroneos, porfavor Introduce datos validos");
            }
            //Hacer operaciones aritmeticas para ver si necesita una rectificacion

            mvprintw(y +=2, 55, "Tiene Fisuras?: %d", tieneFisuras);
            //mvprintw(y++, 55, "Tipo Combustible: %d", tipo_combustible);
            getch();
            Culata* pzc = inicializarCulata(id_piezaGlobal, numValvulas, presionPrueba, tieneFisuras, alturaOriginal,alturaActual, alturaMinima,id_usuario, estadoPieza);
            guardarPiezaArray(pzc,id_usuario);
            usuario->motor->culata = pzc;
            id_piezaGlobal++;
            imprimirMensaje(10,10,"Culata Creada correctamente :)");
            return 1;
        }
        //clear();
        //mvprintw(10,5,"el usuario NO tiene un motor asignado");
        //mvprintw(11,5,"porfavor modifica los datos o intenta registrando un motor desde 0");
        imprimirMensaje(5,5,"El usuario no es NULL, El motor no es NULL, La culata no es NULL. ¿?¿?¿");
        //getch();
    }
    /*
     *else{
        imprimirMensaje(10,10,"-> No tienes un motor registrado, no puedes ingresar una culata sin tener el numero de serie <-");
    }
    */
    return -1;
}


                //IF YA TENEMOS REGISTRADO EL MOTOR, CARGAR SOLO LOS VALORES DE NUEVAS MEDIDAS
                // SI NO, COMPLETAR TODOS ESTOS CAMPOS

                /*// Si es NO -> LLenar todos los campos, SI Si tiene numero de serie del motor (manual) agregar solo culata
                    .culata = &culatasExistentes[3],
            .monoblock = &monoblocksExistentes[3],
                */
int registrarMonoblock(){


    return 0;
};

void imprimirDetallesMotor(Motor* motor){
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
    //Si alguien nuevo que esta agregando un nuevo motor, seria malo que ya tuviera una de estas piezas asignadas
    if (motor->culata == NULL){
        mvprintw(fila++, 35, "(Culata no asignada)");
    }
    if (motor->monoblock == NULL){
        mvprintw(fila++, 35, "(Monoblock no asignado)");
    }


    getch();
}

void rectificarCulata(Culata* culata, int id_usuario){
    if (culata != NULL && culata->id_usuario == id_usuario){
        culata->operacionesMotor = 1;
    }
}
