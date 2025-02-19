//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//

#ifndef NEGOCIODTO_H
#define NEGOCIODTO_H
#include <sys/_types/_size_t.h>

//Entidad Usuario
typedef struct {
    int id_usuario;
    char nombreUsuario[20];
    char apellido[20];
    int celular;
    char email[30];
    char contacto[20];
}Usuario;

// Estructura para el array dinámico
typedef struct {
    int *data;      // Puntero al array
    size_t size;    // Tamaño actual
    size_t capacity; // Capacidad total
} Array;

Usuario inicializarUsuario(int id_usuario,const char* nombreUsuario,const char* apellido,int celular,const char* email,const char* contacto);

int cliente();

void mostrarUsuario(Usuario usr);


#endif //NEGOCIODTO_H