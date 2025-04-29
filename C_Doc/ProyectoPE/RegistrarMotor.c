//
// Created by Jesus Emmanuel Garcia on 4/28/25.
//
#include <ncurses.h>

#include "UsuarioDTO.h"
#include "LogicaNegocio.h"
#include "UserInterface.h"
#include "Util.h"

int registrarCulata(){
    //Si si tienes el nuemero de serie -> Agregar solo datos culata
    int y = 5;
    //Por corregir
    int id_pieza = id_piezaGlobal;
    // IDENTIFICADOR UNICO DE LA PIEZA -> TODAS LAS PIEZAS DE UN MOTOR DEBEN CONTENER EL MISMO ID
    int numValvulas; // Número de válvulas en la culata
    double presionPrueba; // Presión medida en prueba hidráulica (bar)
    int tieneFisuras; // 1 = Sí, 0 = No (fisuras detectadas)
    float alturaOriginal; // Altura original de la culata (mm)
    float alturaActual; // Altura actual de la culata tras desgaste (mm)
    float alturaMinima; // Altura mínima aceptable (según fabricante) (mm)

    //VARIABLES DE MOTOR
    char* material = 0;
    char* fabricante = 0;
    char* modeloMotor = 0;
    char* numeroDeSerie = 0;
    float desgaste = 0;
    float tolerancia = 0;
    float cilindrada = 0;
    float compresionOriginal = 0;
    int tipo_combustible = -1;
    int annoMotor = 0;

    //Esto debe ser el folio, pero esta agregado asi por temas de testeo
    const int id_Usuario = leerIntSeguro(y += 6, 10, 10000, "Ingrese Id Usuario: ");
    RETURN_IF_ESC(id_Usuario);
    //Esta linea impide que si el usuario no existe no se hara nada

    if (obtenerUsuarioByIdUsuario(id_Usuario) == NULL) return -1;
    if (mostrarMenu(7, "¿Tienes el numero de serie del motor?") == 1){
        clear();
        if (obtenerMotorPorNumeroDeSerie(leerStringSeguro(10,10,30,"Ingrese numero de serie del motor")) != NULL ){
            clear();
            //--------------------------- MEDIDAS CULATA ---------------------------
            // Ingresar numValvulas
            numValvulas = leerIntSeguro(y += 2, 10, 50, "Ingrese numero Valvulas entero");
            // Ingresar presionPrueba
            presionPrueba = leerFloatSeguro(y += 2, 10, 20, "Ingrese PresionPrueba float");
            // Ingresar tipoCombustible
            tipo_combustible = mostrarMenu(6, "Ingrese tipo de combustible");
            tieneFisuras = mostrarMenu(7, "¿Tiene Fisuras?");
            //rectificacion = mostrarMenu(7,"¿Necesita Rectificación?");
            clear();
            //mvprintw(y, 55, "Rectificacion?: %d", rectificacion);
            alturaOriginal = leerFloatSeguro(y += 2, 10, 20, "Ingrese medida original");
            alturaActual = leerFloatSeguro(y += 2, 10, 20, "Ingrese la altura Actual");
            alturaMinima = leerFloatSeguro(y += 2, 10, 20, "Ingrese altura minima");

            //Hacer operaciones aritmeticas para ver si necesita una rectificacion

            mvprintw(y++, 55, "Tiene Fisuras?: %d", tieneFisuras);
            mvprintw(y++, 55, "Tipo Combustible: %d", tipo_combustible);
            getch();
            Culata* pzc = inicializarCulata(id_piezaGlobal, numValvulas, presionPrueba, tieneFisuras, alturaOriginal,
                                    alturaActual, alturaMinima);
            guardarPiezaArray(pzc,id_Usuario);
        }
    }else{
        //GENERAR NUEVO REGISTRO PARA MOTOR Y CULATA
        // Ingresar material
        material = leerStringSeguro(y += 2, 10, 30, "Ingrese material del motor ");
        if (material == NULL)return -1;

        //Pendiente
        //annoMotor = leerIntSeguro(y+=2,10,20,"Ingrese año del modelo del motor -> D M A Sin Diagonal");
        annoMotor = 1;
        //-------------     Culata
        // Ingresar numValvulas
        numValvulas = leerIntSeguro(y += 2, 10, 50, "Ingrese numero Valvulas entero");
        // Ingresar presionPrueba
        presionPrueba = leerFloatSeguro(y += 2, 10, 20, "Ingrese PresionPrueba float");
        // Ingresar tipoCombustible
        tipo_combustible = mostrarMenu(6, "Ingrese tipo de combustible");
        tieneFisuras = mostrarMenu(7, "¿Tiene Fisuras?");
        //rectificacion = mostrarMenu(7,"¿Necesita Rectificación?");
        clear();
        //mvprintw(y, 55, "Rectificacion?: %d", rectificacion);
        alturaOriginal = leerFloatSeguro(y += 2, 10, 20, "Ingrese medida original");
        alturaActual = leerFloatSeguro(y += 2, 10, 20, "Ingrese la altura Actual");
        alturaMinima = leerFloatSeguro(y += 2, 10, 20, "Ingrese altura minima");

        //--------------    MOTOR
        fabricante = leerStringSeguro(y += 2, 10, 20, "Ingrese Fabricante del motor");
        modeloMotor = leerStringSeguro(y += 2, 10, 20, "Ingrese Modelo del motor");
        numeroDeSerie = leerStringSeguro(y += 2, 10, 20, "Ingrese Numero de serie del motor");
        // Ingresar desgaste
        desgaste = leerFloatSeguro(y += 2, 10, 30, "Ingresar desgaste float");
        // Este campo es automatico
        tolerancia = leerFloatSeguro(y += 2, 10, 100, "Ingrese tolerancia float");
        cilindrada = leerFloatSeguro(y += 2, 10, 100, "Ingrese Cilindrada en litros float");
        compresionOriginal = leerFloatSeguro(y += 2, 10, 100, "Ingrese Compresion Original float");
        // comprobar necesitaRectificacion
        //Funcion necesita rectificacion

        Paramsmotor registro_motor = {
            /*.modelo = modeloMotor,
            .fabricante = fabricante,
            .cilindrada = cilindrada,
            .compresionOriginal = compresionOriginal,
            .tipoCombustible = tipo_combustible,
            //Esta debe de ponerse en automatico en otra funcion
            .tipoPieza = CULATA,
            .culata = pzc,
            .material = material,
            .desgaste = desgaste,
            .tolerancia = tolerancia,
            .medidaOriginal = alturaOriginal,
            .medidaActual = alturaActual,
        .
            .necesitaRectificacion = //Funcion aritmetica*/
            .modelo = modeloMotor,
            .fabricante = fabricante,
            .anno = annoMotor,
            .cilindrada = cilindrada,
            .compresionOriginal = compresionOriginal,
            .numeroSerie = numeroDeSerie,
            .tipoCombustible = tipo_combustible,
            //Deprecated
            //.tipoPieza = CULATA,
            //.culata = pzc,
            //.monoblock = NULL,
            .material = material,
            .desgaste = desgaste,
            .tolerancia = tolerancia,
            .medidaOriginal = alturaOriginal,
            .medidaActual = alturaActual,
            .necesitaRectificacion = verificarSiNecesitaRectificacion(alturaOriginal, alturaActual, alturaMinima),
            .necesitaReconstruccion = verificarSiNecesitaReconstruccion(alturaOriginal, alturaActual, alturaMinima)
        };

        Culata* pzc = inicializarCulata(id_piezaGlobal, numValvulas, presionPrueba, tieneFisuras, alturaOriginal,
                                    alturaActual, alturaMinima);
        //Por agregar numero de serie
        Motor* motor = inicializarMotor(registro_motor, id_Usuario, id_pieza, numeroDeSerie, pzc, 1);
        guardarPiezaArray((void*)motor, id_Usuario); // Se guarda como puntero genérico
        Usuario* usuario = obtenerUsuarioByIdUsuario(id_Usuario);
        asignarPiezaUsuario(usuario, motor);
        mvprintw(8, 55, "Pieza Asignada y Guardada Correctamente");
        id_piezaGlobal++;
        getch();
    }

}

int verificarSiNecesitaRectificacion(float alturaOriginal, float alturaActual, float alturaMinima){

    return 0;
};

int verificarSiNecesitaReconstruccion(float alturaOriginal, float alturaActual, float alturaMinima){
    return 0;
}



                //IF YA TENEMOS REGISTRADO EL MOTOR, CARGAR SOLO LOS VALORES DE NUEVAS MEDIDAS
                // SI NO, COMPLETAR TODOS ESTOS CAMPOS

                /*// Si es NO -> LLenar todos los campos, SI Si tiene numero de serie del motor (manual) agregar solo culata
                    .culata = &culatasExistentes[3],
            .monoblock = &monoblocksExistentes[3],
                */
