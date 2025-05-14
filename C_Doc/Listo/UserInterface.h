#ifndef USERINTERFACE_H
#define USERINTERFACE_H

void ejecutarOpcion(int opcion);
int mostrarMenu(int menuventana, const char *pregunta);
void imprimirMensaje(int POS_Y, int POS_X, char *pregunta);
void imprimirBarraDeCarga(int delay_ms, const char *mensaje);

#endif
