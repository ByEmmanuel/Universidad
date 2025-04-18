//
// Created by Jesus Emmanuel Garcia on 4/18/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include "LogicaNegocio.h"
#include "Escape.h"
#include "Util.h"
#include "LogicaNegocio.h"
#include "UsuarioDTO.h"

int servicio(){
    //Varibales locales
    // Material de la pieza (Hierro, Aluminio, etc.)
    // Nivel de desgaste en porcentaje (0-100%)
    // Tolerancia máxima de desgaste permitida antes de rectificar
    // Medida original de la pieza en mm
    // Medida actual después del desgaste
    TipoCombustible tipo_combustible = {};

    const int opc = mostrarMenu(4,".") + 1;
    RETURN_IF_ESC(opc);
    int opcusr;
    switch (opc){
        case 1:
            //Ingreso culata o monoblock
            //mvprintw(10,10,"Ingrese una opcion 1: Culata. 2: Monoblock");
            opcusr = mostrarMenu(5,".") + 1;
            RETURN_IF_ESC(opcusr);
            listarFoliosUsuarios();
            if (opcusr == 1){
                //Esto debe ser el folio, pero esta agregado asi por temas de testeo
                const int id_Usuario = leerIntSeguro(10,10,10000,"Ingrese Id Usuario: ");
                RETURN_IF_ESC(id_Usuario);
                // o para mayor control:
                mvprintw(12, 10, "                                                 ");
                //Generar numero de servicio
                // Ingresar material
                const char* material = leerStringSeguro(12,10,30,"Ingrese material del motor");
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
                tipo_combustible = mostrarMenu(6,"Ingrese tipo de combustible");

                const int tieneFisuras = mostrarMenu(7,"¿Tiene Fisuras?");

                const int rectificacion = mostrarMenu(7,"¿Necesita Rectificación?");
                // Ahora puedes usar buffer como un char*
                mvprintw(3, 55, "Rectificacion?: %d", rectificacion);
                mvprintw(4, 55, "Tiene Fisuras?: %d", tieneFisuras);
                mvprintw(5, 55, "Tipo Combustible: %d", tipo_combustible);
                const Pieza piezaUsuario = inicializarPieza(id_Usuario, 1, material, desgaste, tolerancia, medidaOriginal, medidaActual, rectificacion);
                //Polimorfismo
                    Culata* pzc = inicializarCulata(piezaUsuario, numValvulas, presionPrueba, tipo_combustible, tieneFisuras);
                    guardarPiezaArray((void*)pzc);  // Se guarda como puntero genérico
                mvprintw(8, 55, "Pieza Guardada Correctamente");
                getch();
            }else if (opcusr == 2){
                mvprintw(10,10,"Opcion Monoblock");
            }else if (opcusr == 3){
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