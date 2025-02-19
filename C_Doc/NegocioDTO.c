//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//

#include "NegocioDTO.h"

#include <stdio.h>
#include <string.h>
#include "LogicaNegocio.h"

int id_UsuarioLogico = 0;

Usuario inicializarUsuario(const int id_usuario, const char* nombreUsuario, const char* apellido,
                           int celular, const char* email, const char* contacto) {
    Usuario usr = {0}; // Inicializa la estructura en 0 para evitar datos basura
    usr.id_usuario = id_usuario;

    // Copiamos las cadenas asegurándonos de que terminen en '\0'
    strncpy(usr.nombreUsuario, nombreUsuario, sizeof(usr.nombreUsuario) - 1);
    usr.nombreUsuario[sizeof(usr.nombreUsuario) - 1] = '\0';

    strncpy(usr.apellido, apellido, sizeof(usr.apellido) - 1);
    usr.apellido[sizeof(usr.apellido) - 1] = '\0';

    usr.celular = celular;

    strncpy(usr.email, email, sizeof(usr.email) - 1);
    usr.email[sizeof(usr.email) - 1] = '\0';

    strncpy(usr.contacto, contacto, sizeof(usr.contacto) - 1);
    usr.contacto[sizeof(usr.contacto) - 1] = '\0';

    //Adiciona 1 al ID usuario desde aqui para que el usuario nunca tenga el mismo ID sin importar si es valido el usuario o no
    id_UsuarioLogico = id_UsuarioLogico + 1;
    return usr;
}

int cliente(){
    printf("Opcion Cliente");
    //Funcion que crea a los clientes
    char* nombreUsr[] = {};
    char* apellidoUsr[] = {};
    int celularUsr;
    char* emailUsr[] = {};
    char* contactoUsr[] = {};

    //Agregar valores (Todo en un String A una lista)
    printf("\n Agregar Cliente? 1\n Eliminar Cliente 2\n Menu Principal 3\n");
    int opcCliente;
    scanf("%i",&opcCliente);
    if (opcCliente == 3){
        return 1;
    }
    if(opcCliente == 1){
        //Logica Agregar Cliente
        printf("Ingrese Nombre\n");
        scanf("%19s", nombreUsr);
        printf("Ingrese Apellido\n ");
        scanf("%19s", apellidoUsr);
        printf("Ingrese Celular\n");
        scanf("%9d", &celularUsr);
        printf("Ingrese Email\n");
        scanf("%29s", emailUsr);
        printf("Ingrese Contacto\n");
        scanf("%19s", contactoUsr);

        Usuario usuario = inicializarUsuario(id_UsuarioLogico, nombreUsr, apellidoUsr, celularUsr, emailUsr, contactoUsr);
        mostrarUsuario(usuario);

    };

    return 1;
}

void mostrarUsuario(Usuario usr) {
    printf("ID Usuario: %d\n", usr.id_usuario);
    printf("Nombre: %s\n", usr.nombreUsuario);
    printf("Apellido: %s\n", usr.apellido);
    printf("Celular: %d\n", usr.celular);
    printf("Email: %s\n", usr.email);
    printf("Contacto: %s\n", usr.contacto);
}
