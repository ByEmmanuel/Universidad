//Testing
#ifndef TESTING_H
#define TESTING_H
#include "UsuarioDTO.h"


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

#endif
