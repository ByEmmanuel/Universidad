#include "UserInterface.h"

#include <ctype.h>

#include "LogicaNegocio.h"
#include "UsuarioDTO.h"
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#define ESC 27
#define SIZE_DOS 2
#define SIZE_TRES 3
#define SIZE_CUATRO 4
#define SIZE_CINCO 5
#define SIZE_SEIS 6
#define SIZE_SIETE 7
int numOpciones = 0;

//Define para la barra de carga
#define BAR_WIDTH 50      // Longitud de la barra de carga
#define DELAY 100000       // Microsegundos entre cada avance
#define BAR_WIDTH 50  // Ancho de la barra de carga


int (*funcionesSistema[SIZE_SIETE])() = {
    cliente, servicio,pago , almacen, otro, dudas, salir // Solo "Clientes" está implementado
};

void ejecutarOpcion(int opcion) {
    clear();
    if (funcionesSistema[opcion] != NULL) {
        //mvprintw(10, 10, "Has seleccionado: Opción %d", opcion+1);
        refresh();
        funcionesSistema[opcion]();  // Ejecuta la función de la opción
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
    /*
    *Otros -> Seccion de varios menus
        Reportar Bug
        Solicitar Mejora/Feature
        Ver historial de tickets
        Limpieza de caché / reinicio local del sistema
        Enviar logs del sistema

    Dudas
        Consulta tecnica
        Preguntas Frecuentes
        Manual de usuario

     */
    int ch, highlight = 0;
    //Menu Principal
    char* menuPrincipal[SIZE_SIETE] = {"Clientes", "Servicio", "Pago", "Almacen", "Otros", "Dudas", "Salir"};
    //Clientes
    char* menuClientesUno[SIZE_CUATRO] = {"Agregar", "Editar", "Listar", "Menu Principal"};
    char* menuClientesDos[SIZE_SIETE] = {"Nombre", "Apellido", "Num Celular", "Email", "Contacto", "Eliminar","Salir"};
    //Servicio
    char* menuServicioUno[SIZE_CINCO] = {"Ingreso caracteristicas motor", "Medidas", "Operaciones", "Listar Motores Precargados","Salir"};

    //Este listar piezas debe estar en otro lado
    char* menuServicioDos[SIZE_DOS] = {"CULATA", "MONOBLOCK"};
    char* menuServicioTres[SIZE_TRES] = {"1 : Gasolina","2: Diesel","3: Electrico"};
    char* menuServicioCuatro[SIZE_DOS] = {"NO","SI"};
    //Almacen
    char* menuAlmacenUno[SIZE_CUATRO] = {"Inventario General / Stock","Herramientas y Equipos","Proveedores y Compras","Reportes"};

    char* menuAlmacenDos[SIZE_TRES] = {"Ver piezas", "Buscar / Filtrar","Agregar / Editar / Eliminar"};
    char* menuAlmacenTres[SIZE_TRES] = {"Entradas / Salidas","Alertas de stock mínimo","Historial de movimientos"};
    char* menuAlmacenCuatro[SIZE_TRES] = {"Estado de herramientas", "Registro de mantenimiento","Asignación"};
    char* menuAlmacenCinco[SIZE_TRES] = {"Registro de proveedor","Historial de compras","Pedidos pendientes"};
    char* menuAlmacenSeis[SIZE_TRES] = {"Movimientos","Piezas más usadas","Piezas inactivas"};

    //Pago
    char* menuPagoUno[SIZE_CUATRO] = {"Generar Nota", "Generar Ticket" , "Generar Factura", "Listar detalles del usuario"};
    char* menuPagoDos[SIZE_SIETE] = {"Desmontado", "Lavado Inicial", "Rectificacion", "Pruebas Unitarias", "Lavado Secundario", "Montar Motor", "Salir"};
    //Otros
    char* menuOtrosUno[SIZE_SIETE] = {"Reportar Bug/Solicitar Mejora", "Listar Piezas Guardadas Sistema", "Ver Historial de tickets", "Limpieza de cache - Reinicio local del sistema",
        "Enviar Logs del sistema", "Exportar Todo el sistema", "Salir"};
    //Dudas
    char* menuDudasUno[SIZE_CINCO] = {"Consulta Tecnica", "Consultar Version", "Manual de usuario", "Documentacion", "Salir"};

    char** menuActual = NULL;
    int numOpciones = 0;
    switch (menuventana) {
    case 1: menuActual = menuPrincipal; numOpciones = SIZE_SIETE; break;
        //CLientes
    case 2: menuActual = menuClientesUno; numOpciones = SIZE_CUATRO; break;
    case 3: menuActual = menuClientesDos; numOpciones = SIZE_SIETE; break;
        //Servicio
    case 4: menuActual = menuServicioUno; numOpciones = SIZE_CINCO; break;
    case 5: menuActual = menuServicioDos; numOpciones = SIZE_DOS; break;
    case 6: menuActual = menuServicioTres; numOpciones = SIZE_TRES; break;
    case 7: menuActual = menuServicioCuatro; numOpciones = SIZE_DOS; break;
    case 8: menuActual = menuAlmacenUno; numOpciones = SIZE_CUATRO; break;
    case 9: menuActual = menuAlmacenDos; numOpciones = SIZE_TRES; break;
    case 10: menuActual = menuAlmacenTres; numOpciones = SIZE_TRES; break;
    case 11: menuActual = menuAlmacenCuatro; numOpciones = SIZE_TRES; break;
    case 12: menuActual = menuAlmacenCinco; numOpciones = SIZE_TRES; break;
    case 13: menuActual = menuAlmacenSeis; numOpciones = SIZE_TRES; break;
    case 14: menuActual = menuPagoUno; numOpciones = SIZE_CUATRO; break;
    case 15: menuActual = menuPagoDos; numOpciones = SIZE_SIETE; break;
    case 16: menuActual = menuOtrosUno; numOpciones = SIZE_SIETE; break;
    case 17: menuActual = menuDudasUno; numOpciones = SIZE_CINCO; break;

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

void imprimirMensaje(const int POS_Y, const int POS_X, char* pregunta){
    clear();
    mvprintw(POS_Y,POS_X,"%s",pregunta);
    getch();
}

void imprimirBarraDeCarga(const int delay_ms, const char* mensaje) {
    noecho();
    curs_set(FALSE);
    clear();


    int fila = LINES / 2;
    int columna = (COLS - BAR_WIDTH) / 2;
    mvprintw(fila-2, columna, mensaje);

    // Dibujar límites de la barra
    mvprintw(fila, columna, "[");
    mvprintw(fila, columna + BAR_WIDTH + 1, "]");

    for (int i = 0; i <= BAR_WIDTH; i++) {
        mvprintw(fila, columna + 1 + i, "=");

        // Mostrar porcentaje
        mvprintw(fila + 2, columna, "Progreso: %d%%", (i * 100) / BAR_WIDTH);
        refresh();
        usleep(delay_ms * 1000);  // Convertir milisegundos a microsegundos
    }

    // Mostrar mensaje final
    mvprintw(fila + 4, columna, "Carga completada. Presiona una tecla para salir.");
    refresh();
    getch();    // Esperar tecla

}