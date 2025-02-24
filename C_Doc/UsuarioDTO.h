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
    long long celular;
    char email[30];
    char contacto[20];
}Usuario;

// Estructura para el array dinámico de Usuarios
typedef struct {
    Usuario* lista;  // Puntero a la lista de usuarios
    int total;       // Número actual de usuarios
    int capacidad;   // Capacidad máxima del array
} ArrayUsuarios;

// Array para x Objeto
typedef struct {
    void** data;    // Arreglo dinámico de punteros genéricos
    size_t size;    // Número de elementos actuales
    size_t capacidad;// Capacidad total del arreglo
} ArrayList;

Usuario inicializarUsuario(int id_usuario,const char* nombreUsuario,const char* apellido,long long celular,const char* email,const char* contacto);

int cliente();

void mostrarUsuario(Usuario usr);

void modificarCliente();

int guardarUsuarioArray(Usuario usuario);

ArrayUsuarios* inicializarArrayUsuarios(int capacidadInicial);

#endif //NEGOCIODTO_H