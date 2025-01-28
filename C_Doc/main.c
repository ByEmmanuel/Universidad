#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <_time.h>
#include <regex.h>


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

//variables
int opc = 0;
char* string[] = {"Cliente", "Ayuda", "Almacen", "Opc 4", "Opc 5", "Opc 6"};
const int *pattern = "^[0-9]+$";  // Solo numeros

// Estructura para el array dinámico
typedef struct {
    int *data;      // Puntero al array
    size_t size;    // Tamaño actual
    size_t capacity; // Capacidad total
} Array;

int main(void)
{
    printf("LOGO\n\n");

    for (int i = 0; i < 6; ++i){
        printf("%s\n", string[i]);

    }
    printf("Ingrese algo \n");
    scanf("%d", &opc);
    regex_t regex;

    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        printf("Error al compilar la expresión regular\n");
        return 1;
    }
    reti = regexec(&regex, &opc, 0, NULL, 0);
    if (!reti) {
        printf("La cadena '%c' coincide con el patrón '%s'\n", opc, pattern);
    } else if (reti == REG_NOMATCH) {
        printf("La cadena '%s' NO coincide con el patrón '%s'\n", opc, pattern);
    } else {
        printf("Ocurrió un error durante la ejecución del regex\n");
    }

    printf("%d\n", opc);
    printf("Hola !\n");
    return 0;
}