#include "UserInterface.h"

#include <ctype.h>

#include "LogicaNegocio.h"
#include "UsuarioDTO.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define ESC 27
#define SIZE_DOS 2
#define SIZE_TRES 3
#define SIZE_CUATRO 4
#define SIZE_CINCO 5
#define SIZE_SEIS 6
#define SIZE_SIETE 7
int numOpciones = 0;

/**@deprecated */
char** menuActual = NULL; // Apuntador genérico para evitar repetición de código.

int (*funcionesInt[SIZE_SIETE])() = {
    cliente, servicio, NULL,almacen, NULL, NULL, salir // Solo "Clientes" está implementado
};

void ejecutarOpcion(int opcion) {
    clear();
    if (funcionesInt[opcion] != NULL) {
        mvprintw(10, 10, "Has seleccionado: Opción %d", opcion+1);
        refresh();
        funcionesInt[opcion]();  // Ejecuta la función de la opción
    } else {
        mvprintw(10, 10, "Opción %d no implementada aún.", opcion+1);
        refresh();
        getch();
    }
    //Por aqui no pasa el flujo del programa
    mvprintw(1, 60, "Presiona cualquier tecla para volver al menu...");
    refresh();
    //getch();
}
//-------------------------------------FUNCION PRINCIPAL (VENTANA) --------------------------
void imprimirMenu(char* menu[], int numOpciones, int highlight) {
    for (int i = 0; i < numOpciones; i++) {
        if (i == highlight) {
            attron(A_REVERSE);
        }
        mvprintw(i + 5, 10, "%s", menu[i]);
        attroff(A_REVERSE);
    }
    refresh();
}

int mostrarMenu(int menuventana, const char* pregunta) {
/**
    * Almacén
    ├── Inventario General
    │   ├── Ver piezas                      -> Listar Piezas
    │   ├── Buscar / Filtrar                -> Buscar piezas por numero de serie
    │   ├── Agregar / Editar / Eliminar     -> Create Update Delete Piezas
    │   └── Historial de movimientos        -> Ver el historial de Adicion, Edicion y Eliminacion de  las piezas. Cada apartado llevara la fecha
    ├── Herramientas y Equipos
    │   ├── Estado de herramientas
    │   ├── Registro de mantenimiento
    │   └── Asignación
    ├── Proveedores y Compras
    │   ├── Registro de proveedor
    │   ├── Historial de compras
    │   └── Pedidos pendientes
    └── Reportes
        ├── Movimientos
        ├── Piezas más usadas
        └── Piezas inactivas
 */
    int ch, highlight = 0;
    char* menuUno[SIZE_SIETE] = {"Clientes", "Servicio", "Pago", "Almacen", "Otros", "Dudas", "Salir"};
    char* menuDos[SIZE_CUATRO] = {"Agregar", "Editar", "Listar", "Menu Principal"};
    char* menuTres[SIZE_SIETE] = {"Nombre", "Apellido", "Num Celular", "Email", "Contacto", "Eliminar","Salir"};
    char* menuCuatro[SIZE_SEIS] = {"Ingreso", "Lavado", "Medidas", "Rectificar", "Ensamble", "Salir"};
    char* menuCinco[SIZE_TRES] = {"CULATA", "MONOBLOCK", "Listar Piezas"};
    char* menuSeis[SIZE_TRES] = {"1 : Gasolina","2: Diesel","3: Electrico"};
    char* menuSiete[SIZE_DOS] = {"NO","SI"};
    char* menuOcho[SIZE_CUATRO] = {"Inventario General / Stock","Herramientas y Equipos","Proveedores y Compras","Reportes"};


    char* subMenuUno[SIZE_TRES] = {"Ver piezas", "Buscar / Filtrar","Agregar / Editar / Eliminar"};
    char* subMenuDos[SIZE_TRES] = {"Entradas / Salidas","Alertas de stock mínimo","Historial de movimientos"};
    char* subMenuTres[SIZE_TRES] = {"Estado de herramientas", "Registro de mantenimiento","Asignación"};
    char* subMenuCuatro[SIZE_TRES] = {"Registro de proveedor","Historial de compras","Pedidos pendientes"};
    char* subMenuCinco[SIZE_TRES] = {"Movimientos","Piezas más usadas","Piezas inactivas"};

    char** menuActual = NULL;
    int numOpciones = 0;
    switch (menuventana) {
    case 1: menuActual = menuUno; numOpciones = SIZE_SIETE; break;
    case 2: menuActual = menuDos; numOpciones = SIZE_CUATRO; break;
    case 3: menuActual = menuTres; numOpciones = SIZE_SIETE; break;
    case 4: menuActual = menuCuatro; numOpciones = SIZE_SEIS; break;
    case 5: menuActual = menuCinco; numOpciones = SIZE_TRES; break;
    case 6: menuActual = menuSeis; numOpciones = SIZE_TRES; break;
    case 7: menuActual = menuSiete; numOpciones = SIZE_DOS; break;
    case 8: menuActual = menuOcho; numOpciones = SIZE_CUATRO; break;
    //SubMenus
    case 9: menuActual = subMenuUno; numOpciones = SIZE_TRES; break;
    case 10: menuActual = subMenuDos; numOpciones = SIZE_TRES; break;
    case 11: menuActual = subMenuTres; numOpciones = SIZE_TRES; break;
    case 12: menuActual = subMenuCuatro; numOpciones = SIZE_TRES; break;
    case 13: menuActual = subMenuCinco; numOpciones = SIZE_TRES; break;

    default:
        mvprintw(10, 10, "Opción no válida o ocurrió un error");
        refresh();
        getch();
        return -1;
    }


    ESCDELAY = 25;
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    while (1) {
        clear();
        mvprintw(2, 10, "%s", pregunta); // Mostrar pregunta arriba
        imprimirMenu(menuActual, numOpciones, highlight); // El menú comienza en línea 5
        ch = getch();

        switch (ch) {
        case KEY_UP: highlight = (highlight == 0) ? numOpciones - 1 : highlight - 1; break;
        case KEY_DOWN: highlight = (highlight == numOpciones - 1) ? 0 : highlight + 1; break;
        case 10: return highlight ; // ENTER
        case ESC: return -1;
        }
    }
}

