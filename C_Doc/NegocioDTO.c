//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//

#include "NegocioDTO.h"

#include <stdio.h>
#include <string.h>

int id_Usuario = 0;

Usuario inicializarUsuario(const int id_usuario, const char* nombreUsuario, const char* apellido,int celular, const char* email, const char* contacto) {
    Usuario usr;
    usr.id_usuario = id_usuario;
    strncpy(usr.nombreUsuario, nombreUsuario, sizeof(usr.nombreUsuario) - 1); // Asegura que no haya desbordamiento
    usr.nombreUsuario[sizeof(usr.nombreUsuario) - 1] = '\0'; // Asegura que la cadena estÈ terminada en null
    strncpy(usr.apellido, apellido, sizeof(usr.apellido) - 1);
    usr.apellido[sizeof(usr.apellido) - 1] = '\0';
    strncpy(usr.apellido, apellido, sizeof(usr.apellido) - 1);
    usr.apellido[sizeof(usr.apellido) - 1] = '\0';
    strncpy(usr.email, email, sizeof(usr.email) - 1);
    usr.nombreUsuario[sizeof(usr.nombreUsuario) - 1] = '\0';
    usr.celular = celular;
    strncpy(usr.contacto, contacto, sizeof(usr.contacto) - 1);
    usr.contacto[sizeof(usr.contacto) - 1] = '\0';


    return usr;
}


