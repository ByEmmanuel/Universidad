//
// Created by Jesus Emmanuel Garcia on 5/1/25.
//

#ifndef TESTING_H
#define TESTING_H
#include "UsuarioDTO.h"

//FUNCIONEs DE TESTEO, NO TENER EN PRODUCCION

#define CANTIDAD_MOTORES_PRECARGADOS 10
extern Culata culatasExistentes[CANTIDAD_MOTORES_PRECARGADOS];
extern Monoblock monoblocksExistentes[CANTIDAD_MOTORES_PRECARGADOS];
extern Motor motoresExistentesCONCulatasAsignadas[CANTIDAD_MOTORES_PRECARGADOS];
extern Motor motoresExistentesSINCulatasAsignadas[CANTIDAD_MOTORES_PRECARGADOS];

extern int testingMode;

void testing(int encendido);
void agregarUsuarios();
void agregarPiezas();
int precargarMotoresDB(Motor motores[], int cantidad);
void inicializarArrayMotoresPrecargados();
void listarMotoresPrecargados();

#endif //TESTING_H
