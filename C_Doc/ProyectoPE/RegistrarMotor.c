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
    // IDENTIFICADOR UNICO DE LA PIEZA -> TODAS LAS PIEZAS DE UN MOTOR DEBEN CONTENER EL MISMO ID
    // Número de válvulas en la culata
    // Presión medida en prueba hidráulica (bar)
    // 1 = Sí, 0 = No (fisuras detectadas)
    // Altura original de la culata (mm)
    // Altura actual de la culata tras desgaste (mm)
    // Altura mínima aceptable (según fabricante) (mm)

    //Esto debe ser el folio, pero esta agregado asi por temas de testeo
    clear();
    const int id_usuario = obtenerIdSiExisteUsuario();
    RETURN_IF_ESC(id_usuario);
    //Esta linea impide que si el usuario no existe no se hara nada

    if (obtenerUsuarioByIdUsuario(id_usuario) == NULL) return -1;
    if (mostrarMenu(7, "¿Tienes el numero de serie del motor?") == 1){
        clear();
        //Motor* motorUsuario = obtenerMotorPorNumeroDeSerie(leerStringSeguro(10,10,30,"Ingrese numero de serie del motor"));
        Motor* motorUsuario = obtenerMotorByIdUsuario(id_usuario);
        if (motorUsuario != NULL && motorUsuario->culata == NULL){
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

            //Hacer operaciones aritmeticas para ver si necesita una rectificacion

            mvprintw(y +=2, 55, "Tiene Fisuras?: %d", tieneFisuras);
            //mvprintw(y++, 55, "Tipo Combustible: %d", tipo_combustible);
            getch();
            Culata* pzc = inicializarCulata(id_piezaGlobal, numValvulas, presionPrueba, tieneFisuras, alturaOriginal,alturaActual, alturaMinima,id_usuario);
            guardarPiezaArray(pzc,id_usuario);
            motorUsuario->culata = pzc;
            id_piezaGlobal++;
            imprimirMensaje(10,10,"Culata Creada correctamente :)");
            return 1;
        }
        //Imprimir que no existe el motor o que el motor ya tiene asignado una culata
    }else{
        imprimirMensaje(10,10,"-> No tienes un motor registrado, no puedes ingresar una culata sin tener el numero de serie <-");
    }
    return -1;
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
