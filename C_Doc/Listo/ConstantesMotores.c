///constantesMotores
#include "../ProyectoPE/LogicaNegocio.h"
#include "UsuarioDTO.h"

PiezaAlmacen componentes_motor[CANTIDAD_PIEZASPRECARGADAS] = {
    {
        .id_pieza = "PISTON_05MM_101",
        .id_unicoPieza = "P101",
        .tipo = "Pistón sobremedida",
        .tolerancia = 0.5f,
        .material = "Aluminio", .estadoPieza = "Nueva",
        .compatibilidad = "FD123456, HND13579, MZD67890", .cantidad = 40
    },
    {
        .id_pieza = "COJINETE_B_102",
        .id_unicoPieza = "C102",
        .tipo = "Cojinete de biela",
        .tolerancia = 0.25f,
        .material = "Bimetal",
        .estadoPieza = "Nueva",
        .compatibilidad = "CMS23456, PWS98765, TYT56473", .cantidad = 60
    },
    {
        .id_pieza = "ANILLO_1.0MM_103",
        .id_unicoPieza = "A103",
        .tipo = "Anillo de compresión",
        .tolerancia = 1.0f,
        .material = "Acero",
        .estadoPieza = "Nueva",
        .compatibilidad = "CHV09876, HND13579", .cantidad = 100
    },
    {
        .id_pieza = "JUNTA_ADM_104",
        .id_unicoPieza = "J104",
        .tipo = "Junta de admisión",
        .tolerancia = 0.0f,
        .material = "Goma",
        .estadoPieza = "Nueva",
        .compatibilidad = "PWS98765, BMW24681", .cantidad = 50
    },
    {
        .id_pieza = "RETEN_CIG_105",
        .id_unicoPieza = "R105",
        .tipo = "Retén de cigüeñal",
        .tolerancia = 0.0f,
        .material = "Nitrilo",
        .estadoPieza = "Nueva",
        .compatibilidad = "MZD67890, HND13579, FD123456", .cantidad = 70
    }
};


PiezaAlmacen componentes_culata[CANTIDAD_PIEZASPRECARGADAS] = {
    {
        .id_pieza = "LAINA_1.3MM_201",
        .id_unicoPieza = "L201",
        .tipo = "Laina de culata",
        .tolerancia = 1.3f,
        .material = "Cobre",
        .estadoPieza = "Nueva",
        .compatibilidad = "HND13579, HND12345, MZD67890", .cantidad = 25
    },
    {
        .id_pieza = "VALVULA_EXH_202",
        .id_unicoPieza = "V202",
        .tipo = "Válvula de escape",
        .tolerancia = 0.0f,
        .material = "Acero inoxidable",
        .estadoPieza = "Nueva",
        .compatibilidad = "FD123456, FRD45678", .cantidad = 50
    },
    {
        .id_pieza = "GUIA_VAL_203",
        .id_unicoPieza = "G203",
        .tipo = "Guía de válvula",
        .tolerancia = 0.0f,
        .material = "Bronce",
        .estadoPieza = "Nueva",
        .compatibilidad = "CHV09876, CMS23456", .cantidad = 80
    },
    {
        .id_pieza = "JUNTA_CUL_204",
        .id_unicoPieza = "J204",
        .tipo = "Junta de culata",
        .tolerancia = 1.4f,
        .material = "Multicapa metálica",
        .estadoPieza = "Nueva",
        .compatibilidad = "TYT56473, BMW24681", .cantidad = 15
    },
    {
        .id_pieza = "RESORTE_VAL_205",
        .id_unicoPieza = "R205",
        .tipo = "Resorte de válvula",
        .tolerancia = 0.0f,
        .material = "Acero templado",
        .estadoPieza = "Nueva",
        .compatibilidad = "PWS98765, HND12345", .cantidad = 60
    }
};


PiezaAlmacen componentes_monoblock[CANTIDAD_PIEZASPRECARGADAS] = {
    {
        .id_pieza = "BLOQUE_301",
        .id_unicoPieza = "B301",
        .tipo = "Bloque de motor",
        .tolerancia = 0.0f,
        .material = "Aluminio",
        .estadoPieza = "Reconstruida",
        .compatibilidad = "FD123456, MZD67890", .cantidad = 3
    },
    {
        .id_pieza = "CAMISA_0.75MM_302",
        .id_unicoPieza = "C302",
        .tipo = "Camisa de cilindro",
        .tolerancia = 0.75f,
        .material = "Hierro fundido",
        .estadoPieza = "Nueva",
        .compatibilidad = "CMS23456, PWS98765", .cantidad = 25
    },
    {
        .id_pieza = "PISTON_0.25MM_303",
        .id_unicoPieza = "P303",
        .tipo = "Pistón sobremedida",
        .tolerancia = 0.25f,
        .material = "Aluminio",
        .estadoPieza = "Nueva",
        .compatibilidad = "HND13579, HND12345", .cantidad = 35
    },
    {
        .id_pieza = "COJINETE_BANC_304",
        .id_unicoPieza = "C304",
        .tipo = "Cojinete de bancada",
        .tolerancia = 0.5f,
        .material = "Bimetal",
        .estadoPieza = "Nueva",
        .compatibilidad = "CHV09876, TYT56473", .cantidad = 45
    },
    {
        .id_pieza = "TAPA_CIL_305",
        .id_unicoPieza = "T305",
        .tipo = "Tapa de cilindro",
        .tolerancia = 0.0f,
        .material = "Acero",
        .estadoPieza = "Nueva",
        .compatibilidad = "FRD45678, BMW24681", .cantidad = 20
    }
};
