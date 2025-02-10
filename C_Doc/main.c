/*
 * Hacer un programa de interface de usuario
 * Crear una constante de usuarios y contraseñas
 * Hacer logo
 * Esperar 3 segundos
 * Ingresar a interface de login
 * pasar a la pantalla de login y pedir usuario
 * si el usuario es valido entrar a la pantalla de contraseñas
 * maximo 3 intentos
 * si el usuario y contraseña son validos acceder al menu
 * si no salir y camniar el color de la terminal
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <_time.h>
#include <regex.h>

#define MAX_USUARIOS 6
#define MAX_LONGITUD 50

//variables
const int *pattern = "^[0-9]+$";  // Solo numeros
char* menuUno[6] = {"Clientes","Pago","Almacen","Dudas","Otros","Salir"};
// Simulación de base de datos de usuarios y contraseñas
char usuariosRegistrados[MAX_USUARIOS][MAX_LONGITUD] =  {"David","Jose","Admin","Pepe","Luis","Maria"};
char contraseñasUsuarios[MAX_USUARIOS][MAX_LONGITUD] = {"123456789","987654321","13579","24680"};

int opc;
int bandera = 1;
int id_Usuario;

// Estructura para el array dinámico
typedef struct {
    int *data;      // Puntero al array
    size_t size;    // Tamaño actual
    size_t capacity; // Capacidad total
} Array;

//Entidad Usuario
typedef struct Usuario{
    int id_usuario;
    char nombreUsuario[20];
    char apellido;
    int celular;
    char email;
    char contacto;
};
int loginUsuario(){
    int intentosUsuario = 0;

    do {
        char usuarioID[MAX_LONGITUD];
        printf("Ingrese Usuario: ");
        scanf("%s", usuarioID);

        // Buscar el usuario en la lista
        int usuarioIndex = -1;
        for (int i = 0; i < MAX_USUARIOS; i++) {
            if (strcmp(usuarioID, usuariosRegistrados[i]) == 0) {
                usuarioIndex = i;
                break;
            }
        }

        if (usuarioIndex != -1) {
            char passwUsuario[MAX_LONGITUD];
            // Si se encontró el usuario
            printf("Ingrese Contraseña: ");
            scanf("%s", passwUsuario);

            // Verificar contraseña
            if (strcmp(passwUsuario, contraseñasUsuarios[usuarioIndex]) == 0) {
                printf("Inicio de sesión exitoso.\n");
                return 1;
            } else {
                printf("Contraseña incorrecta.\n");
            }
        } else {
            printf("Usuario no encontrado.\n");
        }

        intentosUsuario++;
    } while (intentosUsuario < 3);  // Permitir 3 intentos

    printf("Se agotaron los intentos.\n");
    return 0;
}

inline static int preguntaSalida(){

    printf("\n øDesea Volver A agregar otros?\n 1 : SI \n 2 : NO \n");
    int opcUsuario;
    scanf("%i", &opcUsuario);
    printf("%i",opcUsuario);
    if(opcUsuario == 1){
        printf("RECURSION");
        return opcUsuario;
    }
    return 0;
}

void inicializarUsuario(struct Usuario *U,
    int* id_usuario,
    char* nombreUsuario,
    char* apellido,
    int celular,
    char* email,
    char* contacto) {
    strncpy(U->nombreUsuario, nombreUsuario, sizeof(U->nombreUsuario) - 1); // Asegura que no haya desbordamiento
    U->nombreUsuario[sizeof(U->nombreUsuario) - 1] = '\0'; // Asegura que la cadena estÈ terminada en null
    U->apellido = *apellido;
    U->celular = celular;
    U->email = *email;
    U->contacto = *contacto;

}

inline static int cliente(int bandera){
    printf("Opcion Cliente");
//Funcion que crea a los clientes
char* nombreUsuario[] = {};
char* apellido[] = {};
int* celular[] = {};
char* email[] = {};
char* contacto[] = {};

//Agregar valores (Todo en un String A una lista)
    printf("\n Agregar Cliente? 1\n Eliminar Cliente 2\n");
    int opcCliente;
    scanf("%i",&opcCliente);
    if(opcCliente == 1){
        struct Usuario usuario;
        inicializarUsuario(&usuario,&id_Usuario + 1, "NombreUsuarioAQUI", "ApellidoAQUI", 1111, "EmailAQUI", "ContactoAQUI");

            };

    //"%i",
    if(preguntaSalida() == 1){
            printf("HOLASDFHKI");
        return cliente(0);
    }
    return 0;
}

inline static int servicio(int bandera){
printf("Opcion Servicio ");
return 0;
}

inline static int pago(int bandera){
printf("Opcion pago ");
return 0;
}

inline static int almacen(int bandera){
printf("Opcion Almacen");
return 0;
}

inline static int otro(int bandera){
printf("Opcion otro");
return 0;
}

inline static int salir(int bandera){
printf("Opcion salir");
return 0;
}

inline int validador(){

    return 0;
}

int main(){
    printf("Bienvenido al sistema\n");
printf("    ____         __ \n");
printf("   / __/__  ____/ /___  _________ _\n");
printf("   / __/__  ____/ /___  _________ _\n");
printf("  / /_/ _ \\/ __  / __ \\/ ___/ __ `/\n");
printf("/ __/  __/ /_/ / /_/ / /  / /_/ / \n");
printf("/_/  \\___/\\__,_/\\____/_/   \\__,_/  \n");
printf("      /\\     \n");
printf("     /  \\    \n");

    if (loginUsuario() == 1){
        for(int i = 0; i < 6; i++){
            printf(menuUno[i]);
            printf("\n");
        }

        printf("Ingrese la opcion que desea \n");
        scanf("%i",&opc);

        printf(&opc);

        while (bandera == 1){
            switch ("%i",opc){
            case 1:
                bandera = cliente(bandera);


                break;
            case 2:
                bandera = servicio(bandera);

                break;
            case 3:
                bandera = pago(bandera);


                break;
            case 4:
                bandera = almacen(bandera);

                break;
            case 5:
                bandera = otro(bandera);

                break;
            case 6:
                bandera = salir(bandera);

                break;
            default:
                printf(" introdujo una opcion Invalida");
                bandera = 0;
            }
        }
    }

    printf("Usuario Invalido");
    return 0;

}

