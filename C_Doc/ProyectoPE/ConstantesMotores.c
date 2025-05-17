//
// Created by Jesus Emmanuel Garcia on 5/11/25.
//

#include "LogicaNegocio.h"
#include "UsuarioDTO.h"


//---------------------------------------------------- MOTORES Y PIEZAS REGISTRADOS EN EL SOFTWARE  ----------------------------------------------------//
// Principalmente para uso en almacen

/**
                FD123456 (Ford Duratec 2.0)
                CHV09876 (Chevrolet Vortec 4800)
                FRD45678 (Ford EcoBoost 1.5)
                CMS23456 (Cummins 6.7)
                MZD67890 (Mazda SkyActiv-G 2.5)
                TYT56473 (Toyota 1KD-FTV)
                PWS98765 (Ford PowerStroke 6.4)
                HND13579 (Honda K20A)
                BMW24681 (BMW N57D30)
                HND12345 (Honda F20C)
         */

PiezaAlmacen componentes_motor[CANTIDAD_PIEZASPRECARGADAS] = {
    {
        .id_pieza = "PISTON_05MM_101",
        .id_unicoPieza = "P101", // Pistón
        .tipo = "Piston sobremedida",
        .tolerancia = 0.5f, // +0.5 mm para rectificación de cilindro
        .material = "Aluminio",.estadoPieza = "Nueva",
        .compatibilidad = "FD123456, HND13579, MZD67890",.cantidad = 40
    },
    {
        .id_pieza = "COJINETE_B_102",
        .id_unicoPieza = "C102", // Cojinete
        .tipo = "Cojinete de biela",
        .tolerancia = 0.25f, // +0.25 mm sobremedida
        .material = "Bimetal",
        .estadoPieza = "Nueva",
        .compatibilidad = "CMS23456, PWS98765, TYT56473",.cantidad = 60
    },
    {
        .id_pieza = "ANILLO_1.0MM_103",
        .id_unicoPieza = "A103", // Anillo
        .tipo = "Anillo de compresion",
        .tolerancia = 1.0f, // +1.0 mm para cilindro rectificado
        .material = "Acero",
        .estadoPieza = "Nueva",
        .compatibilidad = "CHV09876, HND13579",.cantidad = 100
    },
    {
        .id_pieza = "JUNTA_ADM_104",
        .id_unicoPieza = "J104", // Junta
        .tipo = "Junta de admision",
        .tolerancia = 0.0f, // Sin tolerancia específica
        .material = "Goma",
        .estadoPieza = "Nueva",
        .compatibilidad = "PWS98765, BMW24681",.cantidad = 50
    },
    {
        .id_pieza = "RETEN_CIG_105",
        .id_unicoPieza = "R105", // Retén
        .tipo = "Reten de cigüeñal",
        .tolerancia = 0.0f, // Sin tolerancia específica
        .material = "Nitrilo",
        .estadoPieza = "Nueva",
        .compatibilidad = "MZD67890, HND13579, FD123456",.cantidad = 70
    }
};

// Estructura de datos para las piezas de culata
PiezaAlmacen componentes_culata[CANTIDAD_PIEZASPRECARGADAS] = {
    {
        .id_pieza = "LAINA_1.3MM_201",
        .id_unicoPieza = "L201", // Laina
        .tipo = "Laina de culata",
        .tolerancia = 1.3f, // Espesor de 1.3 mm para ajuste de compresión
        .material = "Cobre",
        .estadoPieza = "Nueva",
        .compatibilidad = "HND13579, HND12345, MZD67890",.cantidad = 25
    },
    {
        .id_pieza = "VALVULA_EXH_202",
        .id_unicoPieza = "V202", // Válvula
        .tipo = "Valvula de escape",
        .tolerancia = 0.0f, // Estándar
        .material = "Acero inoxidable",
        .estadoPieza = "Nueva",
        .compatibilidad = "FD123456, FRD45678",.cantidad = 50
    },
    {
        .id_pieza = "GUIA_VAL_203",
        .id_unicoPieza = "G203", // Guía
        .tipo = "Guia de valvula",
        .tolerancia = 0.0f, // Sin tolerancia específica
        .material = "Bronce",
        .estadoPieza = "Nueva",
        .compatibilidad = "CHV09876, CMS23456",.cantidad = 80
    },
    {
        .id_pieza = "JUNTA_CUL_204",
        .id_unicoPieza = "J204", // Junta
        .tipo = "Junta de culata",
        .tolerancia = 1.4f, // Espesor de 1.4 mm
        .material = "Multicapa metalica",
        .estadoPieza = "Nueva",
        .compatibilidad = "TYT56473, BMW24681",.cantidad = 15
    },
    {
        .id_pieza = "RESORTE_VAL_205",
        .id_unicoPieza = "R205", // Resorte
        .tipo = "Resorte de valvula",
        .tolerancia = 0.0f, // Sin tolerancia específica
        .material = "Acero templado",
        .estadoPieza = "Nueva",
        .compatibilidad = "PWS98765, HND12345",.cantidad = 60
    }
};

// Estructura de datos para las piezas de monoblock
PiezaAlmacen componentes_monoblock[CANTIDAD_PIEZASPRECARGADAS] = {
    {
        .id_pieza = "BLOQUE_301",
        .id_unicoPieza = "B301", // Bloque
        .tipo = "Bloque de motor",
        .tolerancia = 0.0f, // Sin tolerancia específica
        .material = "Aluminio",
        .estadoPieza = "Reconstruida",
        .compatibilidad = "FD123456, MZD67890",.cantidad = 3
    },
    {
        .id_pieza = "CAMISA_0.75MM_302",
        .id_unicoPieza = "C302", // Camisa
        .tipo = "Camisa de cilindro",
        .tolerancia = 0.75f, // +0.75 mm para rectificación
        .material = "Hierro fundido",
        .estadoPieza = "Nueva",
        .compatibilidad = "CMS23456, PWS98765",.cantidad = 25
    },
    {
        .id_pieza = "PISTON_0.25MM_303",
        .id_unicoPieza = "P303", // Pistón
        .tipo = "Piston sobremedida",
        .tolerancia = 0.25f, // +0.25 mm para cilindro rectificado
        .material = "Aluminio",
        .estadoPieza = "Nueva",
        .compatibilidad = "HND13579, HND12345",.cantidad = 35
    },
    {
        .id_pieza = "COJINETE_BANC_304",
        .id_unicoPieza = "C304", // Cojinete
        .tipo = "Cojinete de bancada",
        .tolerancia = 0.5f, // +0.5 mm sobremedida
        .material = "Bimetal",
        .estadoPieza = "Nueva",
        .compatibilidad = "CHV09876, TYT56473",.cantidad = 45
    },
    {
        .id_pieza = "TAPA_CIL_305",
        .id_unicoPieza = "T305", // Tapa
        .tipo = "Tapa de cilindro",
        .tolerancia = 0.0f, // Sin tolerancia específica
        .material = "Acero",
        .estadoPieza = "Nueva",
        .compatibilidad = "FRD45678, BMW24681",.cantidad = 20
    }
};
//al querer hacer un print de los detalles de esto se debera hacer al ID pieza, Tipo, compatibilidades y cantidades
