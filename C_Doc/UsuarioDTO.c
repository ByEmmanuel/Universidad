//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//

#include "UsuarioDTO.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LogicaNegocio.h"

int id_UsuarioLogico = 0;
// Declaración global del array de usuarios
ArrayUsuarios arrayUsuarios;

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

// 🔹 Inicializar el array con una capacidad inicial
void inicializarArray(int capacidadInicial) {
    arrayUsuarios.lista = (Usuario*)malloc(capacidadInicial * sizeof(Usuario));
    if (arrayUsuarios.lista == NULL) {
        printf("Error al reservar memoria para el array.\n");
        exit(1);
    }
    arrayUsuarios.total = 0;
    arrayUsuarios.capacidad = capacidadInicial;
}

// Función para agregar un usuario a la lista
int guardarUsuarioArray(Usuario usuario) {
    if (arrayUsuarios.total >= arrayUsuarios.capacidad) {
        int nuevaCapacidad = arrayUsuarios.capacidad * 2;
        Usuario* nuevoArray = realloc(arrayUsuarios.lista, nuevaCapacidad * sizeof(Usuario));
        if (nuevoArray == NULL) {
            printf("Error al redimensionar el array de usuarios.\n");
            return 0; // Retornar 0 en caso de error
        }
        arrayUsuarios.lista = nuevoArray;
        arrayUsuarios.capacidad = nuevaCapacidad;
    }

    arrayUsuarios.lista[arrayUsuarios.total] = usuario;
    arrayUsuarios.total++;
    return 1; // Retorna 1 si se guardó correctamente
}

// Función para obtener un usuario por ID
Usuario* obtenerUsuario(const int id) {

    for (int i = 0; i < arrayUsuarios.total; i++) {
        if (arrayUsuarios.lista[i].id_usuario == id) {
            mostrarUsuario(arrayUsuarios.lista[i]);
            return &arrayUsuarios.lista[i];
        }
    }
    // Retorna NULL si el usuario no existe
    printf("Usuario no encontrado... Vuelve a intentar\n");
    return NULL;
}

void modificarCliente(){
    printf("Ingrese ID, Folio o Numero de Cliente: ");
    int id_Cliente;
    scanf("%d", &id_Cliente);

    Usuario* usuarioNuevo = obtenerUsuario(id_Cliente);
    if (usuarioNuevo->nombreUsuario == NULL || usuarioNuevo->email == NULL || usuarioNuevo->nombreUsuario == "" || usuarioNuevo == NULL) {
        printf("Cliente no encontrado.\n");
        return;
    }

    printf("Ingrese la opción que desea modificar:\n");
    char* menuUno[] = {"Nombre", "Apellido", "Num Celular", "Email", "Contacto", "Salir"};
    for (int i = 0; i < 6; i++) {
        printf("%d. %s\n", i + 1, menuUno[i]);
    }

    int opcUsr;
    scanf("%d", &opcUsr);

    char reemplazoUsuario[50]; // Buffer para almacenar entrada

    switch (opcUsr) {
        case 1:
            printf("Ingrese nuevo Nombre: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}// Limpia cualquier residuo en el búfer

            if (fgets(reemplazoUsuario, sizeof(reemplazoUsuario), stdin) != NULL) {
                reemplazoUsuario[strcspn(reemplazoUsuario, "\n")] = '\0'; // Eliminar el salto de línea

                strncpy(usuarioNuevo->nombreUsuario, reemplazoUsuario, sizeof(usuarioNuevo->nombreUsuario) - 1);
                usuarioNuevo->nombreUsuario[sizeof(usuarioNuevo->nombreUsuario) - 1] = '\0'; // Asegurar terminación
            } else {
                printf("Error al leer entrada.\n");
            }
            break;
        case 2:
            printf("Ingrese nuevo Apellido: ");
            fgets(reemplazoUsuario, sizeof(reemplazoUsuario), stdin);
            strncpy(usuarioNuevo->apellido, reemplazoUsuario, sizeof(usuarioNuevo->apellido) - 1);
            usuarioNuevo->apellido[sizeof(usuarioNuevo->apellido) - 1] = '\0';
            break;
        case 3:
            printf("Ingrese nuevo Número Celular: ");
            scanf("%d", &usuarioNuevo->celular);
            break;
        case 4:
            printf("Ingrese nuevo Email: ");
            fgets(reemplazoUsuario, sizeof(reemplazoUsuario), stdin);
            strncpy(usuarioNuevo->email, reemplazoUsuario, sizeof(usuarioNuevo->email) - 1);
            usuarioNuevo->email[sizeof(usuarioNuevo->email) - 1] = '\0';
            break;
        case 5:
            printf("Ingrese nuevo Contacto: ");
            fgets(reemplazoUsuario, sizeof(reemplazoUsuario), stdin);
            strncpy(usuarioNuevo->contacto, reemplazoUsuario, sizeof(usuarioNuevo->contacto) - 1);
            usuarioNuevo->contacto[sizeof(usuarioNuevo->contacto) - 1] = '\0';
            break;
        case 6:
            printf("Saliendo...\n");
            return;
        default:
            printf("Opción inválida.\n");
            return;
    }

    printf("Modificación realizada con éxito.\n");
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
    printf("\n Agregar Cliente? 1\n Editar Cliente 2\n Menu Principal 3\n");
    int opcCliente;
    scanf("%d",&opcCliente);
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

        guardarUsuarioArray(usuario);

    }else if (opcCliente == 2){
        modificarCliente();
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
