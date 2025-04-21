//
// Created by pollofeliz on 20/04/25.
//

#ifndef MOTORES_H
#define MOTORES_H

#define TOTAL_MOTORES 10
#include "UsuarioDTO.h"
//#include "LogicaNegocio.h"

/**
typedef struct {
    const char* nombre;
    const char* fabricante;
    float cilindrada;              // Litros
    int numCilindros;
    float medidaOriginal;          // mm
    float toleranciaMaxima;        // mm
    float desgasteMaximoPermitido;// mm
    float compresionOriginal;      // psi
    int tipoCombustible;           // 0: Gasolina, 1: Diesel
    const char* numeroSerie;       // Número de serie único del motor
    Culata* culata;
    Monoblock* monoblock;
} Motor;
*/



/**
 *  "Motores de la pagina web"
 *  Se cortara el numero de serie a un formato mas "Amigable" para el usuario,
 *  Cada usuario podra tener la capacidad de tener un motor en verificacion
 *  Y una pieza
 *  -> Esto es un array de motores
 */

// Voy a tener 2 Arrays, uno de Culata y otro de Monoblock, para despues asignar esas piezas a un motor
// Y el motor meterlo en un array -> Array de motores



/**
const Motor MOTORES_REGISTRADOS[TOTAL_MOTORES] = {
    {

        .nombre = "1.6L VVT-i",
        .fabricante = "Toyota",
        .cilindrada = 1.6f,
        .numCilindros = 4,
        .medidaOriginal = 79.0f,
        .toleranciaMaxima = 0.05f,
        .desgasteMaximoPermitido = 0.12f,
        .compresionOriginal = 180.0f,
        .tipoCombustible = 0,
        //NUMS - TOY-VVTI-1600-ABX0912
        .numeroSerie = "ABX0912"
    },
    {
        .nombre = "1.9L TDI",
        .fabricante = "Volkswagen",
        .cilindrada = 1.9f,
        .numCilindros = 4,
        .medidaOriginal = 79.5f,
        .toleranciaMaxima = 0.08f,
        .desgasteMaximoPermitido = 0.15f,
        .compresionOriginal = 400.0f,
        .tipoCombustible = 1,
        //NUMS - VW-TDI-1900-XKZ3920
        .numeroSerie = "XKZ3920"
    },
    {
        .nombre = "5.7L HEMI",
        .fabricante = "Chrysler",
        .cilindrada = 5.7f,
        .numCilindros = 8,
        .medidaOriginal = 99.5f,
        .toleranciaMaxima = 0.10f,
        .desgasteMaximoPermitido = 0.20f,
        .compresionOriginal = 195.0f,
        .tipoCombustible = 0,
        //NUMS - CHY-HEMI-5700-RFJ7435
        .numeroSerie = "RFJ7435"
    },
    {
        .nombre = "2.0L EcoBoost",
        .fabricante = "Ford",
        .cilindrada = 2.0f,
        .numCilindros = 4,
        .medidaOriginal = 87.5f,
        .toleranciaMaxima = 0.06f,
        .desgasteMaximoPermitido = 0.14f,
        .compresionOriginal = 210.0f,
        .tipoCombustible = 0,
        //NUMS - FRD-EBST-2000-MTS8821
        .numeroSerie = "FRD-EBST-2000-MTS8821"
    },
    {
        .nombre = "3.0L PowerStroke",
        .fabricante = "Ford",
        .cilindrada = 3.0f,
        .numCilindros = 6,
        .medidaOriginal = 93.0f,
        .toleranciaMaxima = 0.09f,
        .desgasteMaximoPermitido = 0.18f,
        .compresionOriginal = 410.0f,
        .tipoCombustible = 1,
        //NUMS - FRD-PWST-3000-KDL2214
        .numeroSerie = "KDL2214"
    },
    {
        .nombre = "2.5L SKYACTIV-G",
        .fabricante = "Mazda",
        .cilindrada = 2.5f,
        .numCilindros = 4,
        .medidaOriginal = 89.0f,
        .toleranciaMaxima = 0.07f,
        .desgasteMaximoPermitido = 0.13f,
        .compresionOriginal = 185.0f,
        .tipoCombustible = 0,
        // NUMS - MZD-SKYG-2500-LMQ4529
        .numeroSerie = "LMQ4529"
    }
};

*/

#endif
