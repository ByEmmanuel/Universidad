//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//

#include "UsuarioDTO.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LogicaNegocio.h"
#include "Util.h"

int id_UsuarioLogico = 0;
int id_Pieza = 0;
// Declaración global del array de usuarios
ArrayUsuarios arrayUsuarios;
ArryTickets arrayTickets;
ArrayList array_list;
ArrayPiezas arrayPiezas;

//Funciones Importantes para la ejecucion detodo el programa y evitar la reutilizacion de codigo
// strncpy,

Usuario inicializarUsuario(const int id_usuario,const char* folio , const char* nombreUsuario, const char* apellido,
                           long long celular, const char* email, const char* contacto) {
    Usuario usr = {0}; // Inicializa la estructura en 0 para evitar datos basura
    usr.id_usuario = id_usuario;
    asignString(usr.folio, folio, sizeof(usr.folio));
    asignString(usr.nombreUsuario, nombreUsuario, sizeof(usr.nombreUsuario));
    asignString(usr.apellido, apellido, sizeof(usr.apellido));
    usr.celular = celular;
    asignString(usr.email, email, sizeof(usr.email));
    asignString(usr.contacto, contacto, sizeof(usr.contacto));

    usr.pieza = NULL;
    //Adiciona 1 al ID usuario desde aqui para que el usuario nunca tenga el mismo ID sin importar si es valido el usuario o no
    id_UsuarioLogico = id_UsuarioLogico + 1;
    return usr;
}
void asignarCulataUsuario(Usuario *usr, Culata* culata) {
    usr->pieza = (Pieza*) culata;
}
void asignarMonoblockUsuario(Usuario *usr, Monoblock* monoblock){
    usr->pieza = (Pieza*) monoblock;
}

Pieza inicializarPieza(const int id_Usuario, const int tipoPieza, const char* material, const float desgaste, float tolerancia,
                        const float medidaOriginal, const float medidaActual, const int necesitaRectificacion ){
    Pieza pz = {0};
    pz.id_Usuario = id_Usuario;
    pz.id_Pieza = id_Pieza;
    pz.tipo = tipoPieza;
    asignString(pz.material, material, sizeof(material));
    pz.desgaste = desgaste;
    pz.tolerancia = tolerancia;
    pz.medidaOriginal = medidaOriginal;
    pz.medidaActual = medidaActual;
    pz.necesitaRectificacion = necesitaRectificacion;

    return pz;
}

Culata inicializarCulata(const Pieza pieza, const int numValvulas ,const double presionPrueba,
                const int tipoCombustible, const int fisuras){
    Culata* culata = (Culata*)malloc(sizeof(Culata));
    culata->base = pieza;
    //culata.base.tipo = 1;
    //asignString(culata.base.material, material ,30);
    //culata.base.desgaste = desgaste;
    //culata.base.tolerancia = tolerancia;
    //culata.base.medidaOriginal = medidaOriginal;
    //culata.base.medidaActual = medidaActual;
    //culata.base.necesitaRectificacion = rectificacion;
    culata->numValvulas = numValvulas;
    culata->presionPrueba = presionPrueba;
    culata->tipoCombustible = tipoCombustible;
    culata->tieneFisuras = fisuras;
    // Agregar medidas manualmente
    return *culata;
}

// 🔹 Inicializar el array con una capacidad inicial
/**
 * @Deprecated
 */
void inicializarArray(int capacidadInicial) {
    arrayUsuarios.datos = (Usuario*)malloc(capacidadInicial * sizeof(Usuario));
    if (arrayUsuarios.datos == NULL) {
        printf("Error al reservar memoria para el array.\n");
        exit(1);
    }
    arrayUsuarios.total = 0;
    arrayUsuarios.capacidad = capacidadInicial;
}

// Función para agregar un usuario a la lista
int guardarUsuarioArray(Usuario usuario) {
    if (arrayUsuarios.total >= arrayUsuarios.capacidad) {
        int nuevaCapacidad = arrayUsuarios.capacidad == 0 ? 1 : arrayUsuarios.capacidad * 2;
        Usuario* nuevoArray = realloc(arrayUsuarios.datos, nuevaCapacidad * sizeof(Usuario));
        if (nuevoArray == NULL) {
            printf("Error al redimensionar el array de usuarios.\n");
            return -1;
        }
        arrayUsuarios.datos = nuevoArray;
        arrayUsuarios.capacidad = nuevaCapacidad;
    }
    arrayUsuarios.datos[arrayUsuarios.total] = usuario;
    arrayUsuarios.total++;
    return 1; // Retorna 1 si se guardó correctamente
}

int guardarPiezaArray(void* pieza) {
    if (arrayPiezas.tamaño >= arrayPiezas.capacidad) {
        // Si la capacidad está llena, redimensionamos el arreglo
        int nuevaCapacidad = arrayPiezas.capacidad == 0 ? 1 : arrayPiezas.capacidad * 2;
        void** nuevoArray = realloc(arrayPiezas.datos, nuevaCapacidad * sizeof(void*));
        if (nuevoArray == NULL) {
            printf("Error al redimensionar el array de Piezas.\n");
            return -1;  // Si realloc falla, retornar error
        }
        arrayPiezas.datos = nuevoArray;  // Asignar el nuevo arreglo redimensionado
        arrayPiezas.capacidad = nuevaCapacidad; // Actualizar la capacidad
    }
    arrayPiezas.datos[arrayPiezas.tamaño] = pieza;  // Guardar puntero a la pieza
    arrayPiezas.tamaño++;  // Incrementar el número de elementos
    return 0;  // Éxito
}

// Función para obtener un usuario por ID
Usuario* obtenerUsuario(const int id) {
    cleanScreen();
    for (int i = 0; i < arrayUsuarios.total; i++) {
        if (arrayUsuarios.datos[i].id_usuario == id) {
            mostrarUsuario(arrayUsuarios.datos[i]);
            return &arrayUsuarios.datos[i];
        }
    }
    // Retorna NULL si el usuario no existe
    printf("Usuario no encontrado... Vuelve a intentar\n");
    return NULL;
}

void modificarCliente(){
    cleanScreen();
    printf("Ingrese ID, Folio o Numero de Cliente: ");
    int id_Cliente;
    scanf("%d", &id_Cliente);

    //Esta funcion puede ser contraproducente ya que si algun campo del objeto Usuario, esta vacio,
    //esta opcion nunca va a funcionar
    Usuario* usuarioNuevo = obtenerUsuario(id_Cliente);
    if (strIsEmpty(usuarioNuevo->nombreUsuario) || strIsEmpty(usuarioNuevo->email) || strIsEmpty(usuarioNuevo->nombreUsuario) || usuarioNuevo == NULL) {
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

    //char reemplazoUsuario[50]; // Buffer para almacenar entrada
    char* reemplazoUsuario;
    cleanBuffer();

    switch (opcUsr) {
        case 1:
            printf("Ingrese nuevo Nombre: ");
            reemplazoUsuario = cinString(50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")) {
                asignString(usuarioNuevo->nombreUsuario, reemplazoUsuario, sizeof(usuarioNuevo->nombreUsuario));
                printf("Modificación realizada con éxito.\n");
                break;
            }
            printf("Error al leer entrada.\n");
            break;
        case 2:
            printf("Ingrese nuevo Apellido: ");
            reemplazoUsuario = cinString(50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->apellido, reemplazoUsuario, sizeof(usuarioNuevo->apellido));
                printf("Modificación realizada con éxito.\n");
                break;
            }
            printf("Error al leer entrada.\n");
            break;
        case 3:
            printf("Ingrese nuevo Número Celular: ");
            long long numero;
            scanf("%9lld",&numero);
            if (numero != 0){
                usuarioNuevo->celular = numero;
                printf("Número guardado: %lld\n", usuarioNuevo->celular);
            }
            cleanBuffer();
            break;
        case 4:
            printf("Ingrese nuevo Email: ");
            reemplazoUsuario = cinString(50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->email, reemplazoUsuario, sizeof(usuarioNuevo->email));
                printf("Modificación realizada con éxito.\n");
                break;
            };
            printf("Error al leer entrada.\n");
            break;
        case 5:
            printf("Ingrese nuevo Contacto: ");
            reemplazoUsuario = cinString(50);
            if (reemplazoUsuario != NULL && !strEquals(reemplazoUsuario, "")){
                asignString(usuarioNuevo->contacto, reemplazoUsuario, sizeof(usuarioNuevo->contacto));
                printf("Modificación realizada con éxito.\n");
                break;
            };
            printf("Error al leer entrada.\n");
            break;
        case 6:
            printf("Saliendo...\n");
            return;
        default:
            printf("Opción inválida.\n");
            return;
    }
}

int cliente(){
    //Funcion que crea a los clientes
    printf("Opcion Cliente");
    //Agregar valores (Todo en un String A una lista)
    printf("\n Agregar Cliente? 1\n Editar Cliente 2\n Listar Cliente 3\n Menu Principal 4\n");
    int opcCliente;
    scanf("%d",&opcCliente);
    //cleanBuffer();
    printf("Debug - Opción ingresada: %d\n", opcCliente); // <-- Añade esto
    if (opcCliente == 4){
        return 1;
    }
    if(opcCliente == 1){
        cleanScreen();
        long long celularUsr;
        //Logica Agregar Cliente
        printf("Ingrese Nombre\n");
        char* nombreUsr = cinString(19);
        char* folio = generarFolio(nombreUsr);
        printf("Ingrese Apellido\n");
        char* apellidoUsr = cinString(19);
        printf("Ingrese Celular\n");
        scanf("%9d", &celularUsr);
        cleanBuffer();
        printf("Ingrese Email\n");
        char* emailUsr = cinString(49);
        printf("Ingrese Contacto\n");
        char* contactoUsr = cinString(29);

        while (!strContains(emailUsr,"@")){
            free(emailUsr);
            printf("Tu Email no es valido, ¿Deseas volver a ingrearlo? \n 1: SI 2: NO");
            const char* opcUsr = cinString(5);
            if (strContains(opcUsr, "1")){
                printf("\033[2A\033[2K\033[1B\033[2K");
                fflush(stdout);
                printf("Ingrese Email\n");
                emailUsr = cinString(49);
            }else{
                printf("Registro INVALIDO  : Email Invalido");
                return 1;
            }
        }
        Usuario usuario = inicializarUsuario(id_UsuarioLogico, folio, nombreUsr, apellidoUsr, celularUsr, emailUsr, contactoUsr);

        mostrarUsuario(usuario);

        guardarUsuarioArray(usuario);
        free(nombreUsr);
        free(folio);
        free(apellidoUsr);
        //free(celularUsr);
        free(emailUsr);
        free(contactoUsr);

    }else if (opcCliente == 2){
        modificarCliente();
    }else if (opcCliente == 3) {
        for (int i = 0; i < arrayUsuarios.capacidad; i++) {
            printf("ID: %d\nFolio: %s\nNombre: %s\nApellido: %s\nCelular: %lld\nEmail: %s\nContacto: %s\n\n",
                   arrayUsuarios.datos[i].id_usuario,
                   arrayUsuarios.datos[i].folio,
                   arrayUsuarios.datos[i].nombreUsuario,
                   arrayUsuarios.datos[i].apellido,
                   arrayUsuarios.datos[i].celular,
                   arrayUsuarios.datos[i].email,
                   arrayUsuarios.datos[i].contacto);
                   //ArrayUsuarios->datos[i].id, ArrayUsuarios->datos[i].nombre, ArrayUsuarios->datos[i].edad);
        }

    };

    cleanScreen();
    return 1;
}

void imprimirPiezasPorUsuario(int idUsuario) {
    printf("Piezas para el Usuario ID: %d\n", idUsuario);
    // Recorrer todas las piezas almacenadas
    for (int i = 0; i < arrayPiezas.tamaño; i++) {
        Pieza* pieza = arrayPiezas.datos[i];  // Obtener puntero a la pieza

        // Verificar si el id_Usuario coincide
        if (pieza->id_Usuario == idUsuario) {
            // Imprimir datos comunes de la pieza
            printf("ID Pieza: %d, Tipo: %d, Material: %s, Desgaste: %.2f%%\n",
                   pieza->id_Pieza, pieza->tipo, pieza->material, pieza->desgaste);

            // Si la pieza es una Culata
            if (pieza->tipo == CULATA) {
                Culata* culata = (Culata*)pieza;  // Hacer cast a Culata

                printf("Tolerancia: %.2f,\n Medida Original: %.2f,\n Medida Actual: %.2f,\n Necesita Rectificacion: %d,\n"
                       "Número de válvulas: %d,\n Presión de prueba: %.2f,\n Combustible: %d,\n Tiene fisuras: %d,\n",
                       pieza->tolerancia, pieza->medidaOriginal, pieza->medidaActual, culata->numValvulas,
                       pieza->necesitaRectificacion, culata->presionPrueba, culata->tipoCombustible,
                       culata->tieneFisuras);
            }
            // Si la pieza es un Monoblock
            else if (pieza->tipo == MONOBLOCK) {
                Monoblock* monoblock = (Monoblock*)pieza;  // Hacer cast a Monoblock
                printf("Monoblock: Número de cilindros: %d, Diámetro del cilindro: %.2f, Ovalización: %.2f, Alineación cigüeñal: %.2f\n",
                       monoblock->numCilindros, monoblock->diametroCilindro, monoblock->ovalizacion, monoblock->alineacionCiguenal);
            }
            printf("\n");  // Línea en blanco entre piezas
        }
    }
}

void listarPiezas(){
    printf("==============================================\n");
    printf("          LISTADO DE TODAS LAS PIEZAS         \n");
    printf("==============================================\n");

    for (size_t i = 0; i < arrayPiezas.tamaño; i++) {
        Pieza* pieza = (Pieza*)arrayPiezas.datos[i];  // Convertimos a Pieza*

        printf("\nID Pieza: %d\n", pieza->id_Pieza);
        printf("ID Usuario: %d\n", pieza->id_Usuario);
        printf("Material: %s\n", pieza->material);
        printf("Desgaste: %.2f%%\n", pieza->desgaste);
        printf("Tolerancia: %.2f mm\n", pieza->tolerancia);
        printf("Medida Original: %.2f mm\n", pieza->medidaOriginal);
        printf("Medida Actual: %.2f mm\n", pieza->medidaActual);
        printf("Necesita Rectificación: %s\n", pieza->necesitaRectificacion ? "Si" : "No");

        if (pieza->tipo == CULATA) {
            Culata* culata = (Culata*)pieza;
            printf("Numero de Valvulas: %d\n", culata->numValvulas);
            printf("Presion de Prueba: %.2f\n", culata->presionPrueba);
            printf("Tipo de Combustible: %s\n", culata->tipoCombustible == 0 ? "Gasolina" : "Diesel");
            printf("Tiene Fisuras: %s\n", culata->tieneFisuras ? "Si" : "No");
        } else if (pieza->tipo == MONOBLOCK) {
            Monoblock* monoblock = (Monoblock*)pieza;
            printf("Numero de Cilindros: %d\n", monoblock->numCilindros);
            printf("Diametro Cilindros: %.2f mm\n", monoblock->diametroCilindro);
            printf("Altura Bloque: %.2f mm\n", monoblock->alineacionCiguenal);
        }

        printf("----------------------------------------------\n");
    }
}

void mostrarUsuario(Usuario usr) {
    printf("ID Usuario: %d\n", usr.id_usuario);
    printf("Folio Usuario: %s\n", usr.folio);
    printf("Nombre: %s\n", usr.nombreUsuario);
    printf("Apellido: %s\n", usr.apellido);
    printf("Celular: %lld\n", usr.celular);
    printf("Email: %s\n", usr.email);
    printf("Contacto: %s\n", usr.contacto);
}
