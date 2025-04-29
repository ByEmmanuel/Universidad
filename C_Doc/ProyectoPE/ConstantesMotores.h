//
// Created by Jesus Emmanuel Garcia on 4/28/25.
//

#ifndef CONSTANTESMOTORES_H
#define CONSTANTESMOTORES_H

#include "LogicaNegocio.h"
#include "UsuarioDTO.h"

Culata culatasExistentes[10] = {
    { .id_pieza = 0, .numValvulas = 16, .presionPrueba = 25.0, .tieneFisuras = 0, .alturaOriginal = 130.0, .alturaActual = 129.8, .alturaMinima = 129.0 }, // Duratec 2.0 (4 cil, 4 válvulas/cil)
    { .id_pieza = 1, .numValvulas = 16, .presionPrueba = 20.0, .tieneFisuras = 0, .alturaOriginal = 135.0, .alturaActual = 134.8, .alturaMinima = 134.0 }, // Vortec 5300 (V8, 2 válvulas/cil)
    { .id_pieza = 2, .numValvulas = 12, .presionPrueba = 22.0, .tieneFisuras = 0, .alturaOriginal = 125.0, .alturaActual = 124.9, .alturaMinima = 124.5 }, // EcoBoost 1.5 (3 cil, 4 válvulas/cil)
    { .id_pieza = 3, .numValvulas = 24, .presionPrueba = 30.0, .tieneFisuras = 1, .alturaOriginal = 140.0, .alturaActual = 139.7, .alturaMinima = 139.0 }, // Cummins 6.7 (6 cil, 4 válvulas/cil)
    { .id_pieza = 4, .numValvulas = 16, .presionPrueba = 23.0, .tieneFisuras = 0, .alturaOriginal = 128.0, .alturaActual = 127.8, .alturaMinima = 127.5 }, // SkyActiv-G 2.5 (4 cil, 4 válvulas/cil)
    { .id_pieza = 5, .numValvulas = 16, .presionPrueba = 28.0, .tieneFisuras = 0, .alturaOriginal = 132.0, .alturaActual = 131.7, .alturaMinima = 131.0 }, // 1KD-FTV (4 cil, 4 válvulas/cil)
    { .id_pieza = 6, .numValvulas = 16, .presionPrueba = 30.0, .tieneFisuras = 0, .alturaOriginal = 138.0, .alturaActual = 137.9, .alturaMinima = 137.5 }, // Power Stroke 6.4 (V8, 4 válvulas/cil, 16 por culata)
    { .id_pieza = 7, .numValvulas = 16, .presionPrueba = 24.0, .tieneFisuras = 0, .alturaOriginal = 126.0, .alturaActual = 125.9, .alturaMinima = 125.5 }, // K20A (4 cil, 4 válvulas/cil)
    { .id_pieza = 8, .numValvulas = 24, .presionPrueba = 27.0, .tieneFisuras = 0, .alturaOriginal = 133.0, .alturaActual = 132.8, .alturaMinima = 132.5 }, // N57D30 (6 cil, 4 válvulas/cil)
    { .id_pieza = 9, .numValvulas = 16, .presionPrueba = 23.0, .tieneFisuras = 0, .alturaOriginal = 124.0, .alturaActual = 123.9, .alturaMinima = 123.5 }  // F20C (4 cil, 4 válvulas/cil)
};

Monoblock monoblocksExistentes[10] = {
    { .id_pieza = 0, .numCilindros = 4, .diametroCilindro = 87.5, .ovalizacion = 0.03, .alineacionCiguenal = 0.04, .desgasteCilindros = 0.1 },  // Duratec 2.0
    { .id_pieza = 1, .numCilindros = 8, .diametroCilindro = 96.0, .ovalizacion = 0.02, .alineacionCiguenal = 0.03, .desgasteCilindros = 0.08 }, // Vortec 5300
    { .id_pieza = 2, .numCilindros = 3, .diametroCilindro = 79.0, .ovalizacion = 0.015, .alineacionCiguenal = 0.02, .desgasteCilindros = 0.05 }, // EcoBoost 1.5
    { .id_pieza = 3, .numCilindros = 6, .diametroCilindro = 107.0, .ovalizacion = 0.04, .alineacionCiguenal = 0.05, .desgasteCilindros = 0.15 }, // Cummins 6.7
    { .id_pieza = 4, .numCilindros = 4, .diametroCilindro = 89.0, .ovalizacion = 0.02, .alineacionCiguenal = 0.03, .desgasteCilindros = 0.06 },  // SkyActiv-G 2.5
    { .id_pieza = 5, .numCilindros = 4, .diametroCilindro = 96.0, .ovalizacion = 0.03, .alineacionCiguenal = 0.04, .desgasteCilindros = 0.12 },  // 1KD-FTV
    { .id_pieza = 6, .numCilindros = 8, .diametroCilindro = 98.0, .ovalizacion = 0.02, .alineacionCiguenal = 0.03, .desgasteCilindros = 0.1 },   // Power Stroke 6.4
    { .id_pieza = 7, .numCilindros = 4, .diametroCilindro = 86.0, .ovalizacion = 0.015, .alineacionCiguenal = 0.02, .desgasteCilindros = 0.04 }, // K20A
    { .id_pieza = 8, .numCilindros = 6, .diametroCilindro = 84.0, .ovalizacion = 0.02, .alineacionCiguenal = 0.03, .desgasteCilindros = 0.08 },  // N57D30
    { .id_pieza = 9, .numCilindros = 4, .diametroCilindro = 87.0, .ovalizacion = 0.015, .alineacionCiguenal = 0.02, .desgasteCilindros = 0.05 }  // F20C
};

Motor motoresExistentes[10] = {
    {
        .modelo = "Duratec 2.0",
        .fabricante = "Ford",
        .numeroSerie = "FD12345678",
        .material = "Aluminio",
        .carroAsociado = "Ford Focus",
        .id_pieza = 0,
        .id_usuario = 0,
        .anno = 2012,
        .cilindrada = 2.0,
        .compresionOriginal = 130.0,
        .tipoCombustible = GASOLINA,
        .culata = &culatasExistentes[0],
        .monoblock = &monoblocksExistentes[0],
        .desgaste = 0.125,
        .tolerancia = 0.05,
        .medidaOriginal = 84.0,
        .medidaActual = 83.9,
        .necesitaRectificacion = 1,
        .necesitaReconstruccion = 0
    },
    {
        .modelo = "Vortec 5300",
        .fabricante = "Chevrolet",
        .numeroSerie = "CHV0987654",
        .material = "Hierro",
        .carroAsociado = "Chevrolet Silverado 1500",
        .id_pieza = 1,
        .id_usuario = 1,
        .anno = 2008,
        .cilindrada = 5.3,
        .compresionOriginal = 150.0,
        .tipoCombustible = GASOLINA,
        .culata = &culatasExistentes[1],
        .monoblock = &monoblocksExistentes[1],
        .desgaste = 0.08,
        .tolerancia = 0.08,
        .medidaOriginal = 92.0,
        .medidaActual = 91.9,
        .necesitaRectificacion = 0,
        .necesitaReconstruccion = 0
    },
    {
        .modelo = "EcoBoost 1.5",
        .fabricante = "Ford",
        .numeroSerie = "FRD4567890",
        .material = "Aluminio",
        .carroAsociado = "Ford Escape",
        .id_pieza = 2,
        .id_usuario = 2,
        .anno = 2016,
        .cilindrada = 1.5,
        .compresionOriginal = 140.0,
        .tipoCombustible = GASOLINA,
        .culata = &culatasExistentes[2],
        .monoblock = &monoblocksExistentes[2],
        .desgaste = 0.052,
        .tolerancia = 0.06,
        .medidaOriginal = 79.0,
        .medidaActual = 78.95,
        .necesitaRectificacion = 0,
        .necesitaReconstruccion = 0
    },
    {
        .modelo = "Cummins 6.7",
        .fabricante = "Cummins",
        .numeroSerie = "CMS2345678",
        .material = "Hierro",
        .carroAsociado = "Dodge Ram 2500",
        .id_pieza = 3,
        .id_usuario = 3,
        .anno = 2015,
        .cilindrada = 6.7,
        .compresionOriginal = 195.0,
        .tipoCombustible = DIESEL,
        .culata = &culatasExistentes[3],
        .monoblock = &monoblocksExistentes[3],
        .desgaste = 0.18,
        .tolerancia = 0.07,
        .medidaOriginal = 107.0,
        .medidaActual = 106.85,
        .necesitaRectificacion = 1,
        .necesitaReconstruccion = 0
    },
    {
        .modelo = "SkyActiv-G 2.5",
        .fabricante = "Mazda",
        .numeroSerie = "MZD6789012",
        .material = "Aluminio",
        .carroAsociado = "Mazda CX-5",
        .id_pieza = 4,
        .id_usuario = 4,
        .anno = 2019,
        .cilindrada = 2.5,
        .compresionOriginal = 160.0,
        .tipoCombustible = GASOLINA,
        .culata = &culatasExistentes[4],
        .monoblock = &monoblocksExistentes[4],
        .desgaste = 0.065,
        .tolerancia = 0.05,
        .medidaOriginal = 89.0,
        .medidaActual = 88.95,
        .necesitaRectificacion = 0,
        .necesitaReconstruccion = 0
    },
    {
        .modelo = "1KD-FTV",
        .fabricante = "Toyota",
        .numeroSerie = "TYT5647382",
        .material = "Hierro",
        .carroAsociado = "Toyota Hilux",
        .id_pieza = 5,
        .id_usuario = 5,
        .anno = 2010,
        .cilindrada = 3.0,
        .compresionOriginal = 175.0,
        .tipoCombustible = DIESEL,
        .culata = &culatasExistentes[5],
        .monoblock = &monoblocksExistentes[5],
        .desgaste = 0.142,
        .tolerancia = 0.06,
        .medidaOriginal = 95.0,
        .medidaActual = 94.85,
        .necesitaRectificacion = 1,
        .necesitaReconstruccion = 0
    },
    {
        .modelo = "Power Stroke 6.4",
        .fabricante = "Ford",
        .numeroSerie = "PWS9876543",
        .material = "Hierro Fundido",
        .carroAsociado = "Ford F-350 Super Duty",
        .id_pieza = 6,
        .id_usuario = 6,
        .anno = 2009,
        .cilindrada = 6.4,
        .compresionOriginal = 200.0,
        .tipoCombustible = DIESEL,
        .culata = &culatasExistentes[6],
        .monoblock = &monoblocksExistentes[6],
        .desgaste = 0.115,
        .tolerancia = 0.07,
        .medidaOriginal = 104.0,
        .medidaActual = 103.9,
        .necesitaRectificacion = 0,
        .necesitaReconstruccion = 0
    },
    {
        .modelo = "K20A",
        .fabricante = "Honda",
        .numeroSerie = "HND1357924",
        .material = "Aluminio",
        .carroAsociado = "Honda Civic Type R",
        .id_pieza = 7,
        .id_usuario = 7,
        .anno = 2005,
        .cilindrada = 2.0,
        .compresionOriginal = 210.0,
        .tipoCombustible = GASOLINA,
        .culata = &culatasExistentes[7],
        .monoblock = &monoblocksExistentes[7],
        .desgaste = 0.045,
        .tolerancia = 0.04,
        .medidaOriginal = 86.0,
        .medidaActual = 85.98,
        .necesitaRectificacion = 0,
        .necesitaReconstruccion = 0
    },
    {
        .modelo = "N57D30",
        .fabricante = "BMW",
        .numeroSerie = "BMW2468135",
        .material = "Aluminio reforzado",
        .carroAsociado = "BMW 330d",
        .id_pieza = 8,
        .id_usuario = 8,
        .anno = 2018,
        .cilindrada = 3.0,
        .compresionOriginal = 175.0,
        .tipoCombustible = DIESEL,
        .culata = &culatasExistentes[8],
        .monoblock = &monoblocksExistentes[8],
        .desgaste = 0.09,
        .tolerancia = 0.06,
        .medidaOriginal = 84.0,
        .medidaActual = 83.92,
        .necesitaRectificacion = 0,
        .necesitaReconstruccion = 0
    },
    {
        .modelo = "F20C",
        .fabricante = "Honda",
        .numeroSerie = "HND1234567",
        .material = "Aluminio",
        .carroAsociado = "Honda S2000",
        .id_pieza = 9,
        .id_usuario = 9,
        .anno = 2003,
        .cilindrada = 2.0,
        .compresionOriginal = 220.0,
        .tipoCombustible = GASOLINA,
        .culata = &culatasExistentes[9],
        .monoblock = &monoblocksExistentes[9],
        .desgaste = 0.05,
        .tolerancia = 0.05,
        .medidaOriginal = 87.0,
        .medidaActual = 86.95,
        .necesitaRectificacion = 0,
        .necesitaReconstruccion = 0
    }
};
//---------------------------------------------------- MOTORES REGISTRADOS EN EL SOFTWARE ----------------------------------------------------//
/*

### Motores
Motor[0]:
  modelo: "Duratec 2.0"
  fabricante: "Ford"
  numeroSerie: "FD12345678"
  material: "Aluminio"
  carroAsociado: "Ford Focus"
  id_pieza: 0
  id_usuario: 0
  año: 2012
  cilindrada: 2.0
  compresionOriginal: 130.0
  tipoCombustible: GASOLINA
  culata: &culatasExistentes[0]
  monoblock: &monoblocksExistentes[0]
  desgaste: 0.125
  tolerancia: 0.05
  medidaOriginal: 84.0
  medidaActual: 83.9
  necesitaRectificacion: 1
  necesitaReconstruccion: 0

Motor[1]:
  modelo: "Vortec 5300"
  fabricante: "Chevrolet"
  numeroSerie: "CHV0987654"
  material: "Hierro"
  carroAsociado: "Chevrolet Silverado 1500"
  id_pieza: 1
  id_usuario: 1
  año: 2008
  cilindrada: 5.3
  compresionOriginal: 150.0
  tipoCombustible: GASOLINA
  culata: &culatasExistentes[1]
  monoblock: &monoblocksExistentes[1]
  desgaste: 0.08
  tolerancia: 0.08
  medidaOriginal: 92.0
  medidaActual: 91.9
  necesitaRectificacion: 0
  necesitaReconstruccion: 0

Motor[2]:
  modelo: "EcoBoost 1.5"
  fabricante: "Ford"
  numeroSerie: "FRD4567890"
  material: "Aluminio"
  carroAsociado: "Ford Escape"
  id_pieza: 2
  id_usuario: 2
  año: 2016
  cilindrada: 1.5
  compresionOriginal: 140.0
  tipoCombustible: GASOLINA
  culata: &culatasExistentes[2]
  monoblock: &monoblocksExistentes[2]
  desgaste: 0.052
  tolerancia: 0.06
  medidaOriginal: 79.0
  medidaActual: 78.95
  necesitaRectificacion: 0
  necesitaReconstruccion: 0

Motor[3]:
  modelo: "Cummins 6.7"
  fabricante: "Cummins"
  numeroSerie: "CMS2345678"
  material: "Hierro"
  carroAsociado: "Dodge Ram 2500"
  id_pieza: 3
  id_usuario: 3
  año: 2015
  cilindrada: 6.7
  compresionOriginal: 195.0
  tipoCombustible: DIESEL
  culata: &culatasExistentes[3]
  monoblock: &monoblocksExistentes[3]
  desgaste: 0.18
  tolerancia: 0.07
  medidaOriginal: 107.0
  medidaActual: 106.85
  necesitaRectificacion: 1
  necesitaReconstruccion: 0

Motor[4]:
  modelo: "SkyActiv-G 2.5"
  fabricante: "Mazda"
  numeroSerie: "MZD6789012"
  material: "Aluminio"
  carroAsociado: "Mazda CX-5"
  id_pieza: 4
  id_usuario: 4
  año: 2019
  cilindrada: 2.5
  compresionOriginal: 160.0
  tipoCombustible: GASOLINA
  culata: &culatasExistentes[4]
  monoblock: &monoblocksExistentes[4]
  desgaste: 0.065
  tolerancia: 0.05
  medidaOriginal: 89.0
  medidaActual: 88.95
  necesitaRectificacion: 0
  necesitaReconstruccion: 0

Motor[5]:
  modelo: "1KD-FTV"
  fabricante: "Toyota"
  numeroSerie: "TYT5647382"
  material: "Hierro"
  carroAsociado: "Toyota Hilux"
  id_pieza: 5
  id_usuario: 5
  año: 2010
  cilindrada: 3.0
  compresionOriginal: 175.0
  tipoCombustible: DIESEL
  culata: &culatasExistentes[5]
  monoblock: &monoblocksExistentes[5]
  desgaste: 0.142
  tolerancia: 0.06
  medidaOriginal: 95.0
  medidaActual: 94.85
  necesitaRectificacion: 1
  necesitaReconstruccion: 0

Motor[6]:
  modelo: "Power Stroke 6.4"
  fabricante: "Ford"
  numeroSerie: "PWS9876543"
  material: "Hierro Fundido"
  carroAsociado: "Ford F-350 Super Duty"
  id_pieza: 6
  id_usuario: 6
  año: 2009
  cilindrada: 6.4
  compresionOriginal: 200.0
  tipoCombustible: DIESEL
  culata: &culatasExistentes[6]
  monoblock: &monoblocksExistentes[6]
  desgaste: 0.115
  tolerancia: 0.07
  medidaOriginal: 104.0
  medidaActual: 103.9
  necesitaRectificacion: 0
  necesitaReconstruccion: 0

Motor[7]:
  modelo: "K20A"
  fabricante: "Honda"
  numeroSerie: "HND1357924"
  material: "Aluminio"
  carroAsociado: "Honda Civic Type R"
  id_pieza: 7
  id_usuario: 7
  año: 2005
  cilindrada: 2.0
  compresionOriginal: 210.0
  tipoCombustible: GASOLINA
  culები: &culatasExistentes[7]
  monoblock: &monoblocksExistentes[7]
  desgaste: 0.045
  tolerancia: 0.04
  medidaOriginal: 86.0
  medidaActual: 85.98
  necesitaRectificacion: 0
  necesitaReconstruccion: 0

Motor[8]:
  modelo: "N57D30"
  fabricante: "BMW"
  numeroSerie: "BMW2468135"
  material: "Aluminio reforzado"
  carroAsociado: "BMW 330d"
  id_pieza: 8
  id_usuario: 8
  año: 2018
  cilindrada: 3.0
  compresionOriginal: 175.0
  tipoCombustible: DIESEL
  culata: &culatasExistentes[8]
  monoblock: &monoblocksExistentes[8]
  desgaste: 0.09
  tolerancia: 0.06
  medidaOriginal: 84.0
  medidaActual: 83.92
  necesitaRectificacion: 0
  necesitaReconstruccion: 0

Motor[9]:
  modelo: "F20C"
  fabricante: "Honda"
  numeroSerie: "HND1234567"
  material: "Aluminio"
  carroAsociado: "Honda S2000"
  id_pieza: 9
  id_usuario: 9
  año: 2003
  cilindrada: 2.0
  compresionOriginal: 220.0
  tipoCombustible: GASOLINA
  culata: &culatasExistentes[9]
  monoblock: &monoblocksExistentes[9]
  desgaste: 0.05
  tolerancia: 0.05
  medidaOriginal: 87.0
  medidaActual: 86.95
  necesitaRectificacion: 0
  necesitaReconstruccion: 0

### Culatas
Culata[0]:
  id_pieza: 0
  numValvulas: 16
  presionPrueba: 25.0
  tieneFisuras: 0
  alturaOriginal: 130.0
  alturaActual: 129.8
  alturaMinima: 129.0

Culata[1]:
  id_pieza: 1
  numValvulas: 16
  presionPrueba: 20.0
  tieneFisuras: 0
  alturaOriginal: 135.0
  alturaActual: 134.8
  alturaMinima: 134.0

Culata[2]:
  id_pieza: 2
  numValvulas: 12
  presionPrueba: 22.0
  tieneFisuras: 0
  alturaOriginal: 125.0
  alturaActual: 124.9
  alturaMinima: 124.5

Culata[3]:
  id_pieza: 3
  numValvulas: 24
  presionPrueba: 30.0
  tieneFisuras: 1
  alturaOriginal: 140.0
  alturaActual: 139.7
  alturaMinima: 139.0

Culata[4]:
  id_pieza: 4
  numValvulas: 16
  presionPrueba: 23.0
  tieneFisuras: 0
  alturaOriginal: 128.0
  alturaActual: 127.8
  alturaMinima: 127.5

Culata[5]:
  id_pieza: 5
  numValvulas: 16
  presionPrueba: 28.0
  tieneFisuras: 0
  alturaOriginal: 132.0
  alturaActual: 131.7
  alturaMinima: 131.0

Culata[6]:
  id_pieza: 6
  numValvulas: 16
  presionPrueba: 30.0
  tieneFisuras: 0
  alturaOriginal: 138.0
  alturaActual: 137.9
  alturaMinima: 137.5

Culata[7]:
  id_pieza: 7
  numValvulas: 16
  presionPrueba: 24.0
  tieneFisuras: 0
  alturaOriginal: 126.0
  alturaActual: 125.9
  alturaMinima: 125.5

Culata[8]:
  id_pieza: 8
  numValvulas: 24
  presionPrueba: 27.0
  tieneFisuras: 0
  alturaOriginal: 133.0
  alturaActual: 132.8
  alturaMinima: 132.5

Culata[9]:
  id_pieza: 9
  numValvulas: 16
  presionPrueba: 23.0
  tieneFisuras: 0
  alturaOriginal: 124.0
  alturaActual: 123.9
  alturaMinima: 123.5

### Monoblocks
Monoblock[0]:
  id_pieza: 0
  numCilindros: 4
  diametroCilindro: 87.5
  ovalizacion: 0.03
  alineacionCiguenal: 0.04
  desgasteCilindros: 0.1

Monoblock[1]:
  id_pieza: 1
  numCilindros: 8
  diametroCilindro: 96.0
  ovalizacion: 0.02
  alineacionCiguenal: 0.03
  desgasteCilindros: 0.08

Monoblock[2]:
  id_pieza: 2
  numCilindros: 3
  diametroCilindro: 79.0
  ovalizacion: 0.015
  alineacionCiguenal: 0.02
  desgasteCilindros: 0.05

Monoblock[3]:
  id_pieza: 3
  numCilindros: 6
  diametroCilindro: 107.0
  ovalizacion: 0.04
  alineacionCiguenal: 0.05
  desgasteCilindros: 0.15

Monoblock[4]:
  id_pieza: 4
  numCilindros: 4
  diametroCilindro: 89.0
  ovalizacion: 0.02
  alineacionCiguenal: 0.03
  desgasteCilindros: 0.06

Monoblock[5]:
  id_pieza: 5
  numCilindros: 4
  diametroCilindro: 96.0
  ovalizacion: 0.03
  alineacionCiguenal: 0.04
  desgasteCilindros: 0.12

Monoblock[6]:
  id_pieza: 6
  numCilindros: 8
  diametroCilindro: 98.0
  ovalizacion: 0.02
  alineacionCiguenal: 0.03
  desgasteCilindros: 0.1

Monoblock[7]:
  id_pieza: 7
  numCilindros: 4
  diametroCilindro: 86.0
  ovalizacion: 0.015
  alineacionCiguenal: 0.02
  desgasteCilindros: 0.04

Monoblock[8]:
  id_pieza: 8
  numCilindros: 6
  diametroCilindro: 84.0
  ovalizacion: 0.02
  alineacionCiguenal: 0.03
  desgasteCilindros: 0.08

Monoblock[9]:
  id_pieza: 9
  numCilindros: 4
  diametroCilindro: 87.0
  ovalizacion: 0.015
  alineacionCiguenal: 0.02
  desgasteCilindros: 0.05

*/

#endif //CONSTANTESMOTORES_H
