//
// Created by Jesus Emmanuel Garcia on 4/2/25.
//

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

/*void menuPrincipal(int highlight);
int mainMenu();
//void menuModificarCliente(int highlight);
*/
int menuServicio();
void ejecutarOpcion(int opcion);
int mostrarMenu(int menuventana, const char* pregunta);


char* leerString(int y, int x, int maxLen);
int* leerInt(int y, int x, int maxLen);
float* leerFloat(int y, int x, int maxLen);

#endif //USERINTERFACE_H