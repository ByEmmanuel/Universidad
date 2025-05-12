//
// Created by Jesus Emmanuel Garcia on 5/7/25.
//

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "UserInterface.h"
#include "LogicaNegocio.h"

/**
* 8     "Inventario General / Stock","Herramientas y Equipos","Proveedores y Compras","Reportes"};
|
v
(0) 9     "Ver piezas", "Buscar / Filtrar","Agregar / Editar / Eliminar"};
(1) 10    "Entradas / Salidas","Alertas de stock mínimo","Historial de movimientos"};
(2) 11    "Estado de herramientas", "Registro de mantenimiento","Asignación"};
(3) 12    "Registro de proveedor","Historial de compras","Pedidos pendientes"};

//¿?¿?¿?¿
(4) 13    "Movimientos","Piezas más usadas","Piezas inactivas"};
 */

int (*funcionesInventarioAlmacen[4])() = {
    listarPiezasAlmacen, buscarPiezasAlmacen, agregarPizasAlmacen , eliminarPiezasAlmacen
};

int (*funcionesHerramientas[3])() = {
    //entradas, alertasStock, historialDeMovimientosAlmacen
};

int (*funcionesProveedores[3])() = {
    //"estadoHerramientas, registroMantenimiento, asignación
};

int (*funcionesReportes[3])() = {
    //registroProveedor, historialCompras, pedidosPendientes
};

void ejecutarOpcionAlmacen(int opcionMenu, int opcionSubMenu) {
    clear();
    refresh();
    switch (opcionMenu){
    case 0:
        funcionesInventarioAlmacen[opcionSubMenu]();
        break;
    case 1:
        funcionesHerramientas[opcionSubMenu]();
        break;
    case 2:
        funcionesProveedores[opcionSubMenu]();
        break;
    case 3:
        funcionesReportes[opcionSubMenu]();
        break;
        default:
            imprimirMensaje(5,5,"Opcion no valida -> Ocurrio un problema");
        break;
    }

    mvprintw(1, 60, "Presiona cualquier tecla para volver al menu...");
    refresh();
    //getch();
}

int listarPiezasAlmacen(){
    //imprimirMensaje(1, 5, "====== LISTADO DE PIEZAS EN ALMACEN ======");
    imprimirArrayPiezasAlmacen();
    char* nombreArchivo = obtenerNombreArchivo("PiezaAlmacen");
    FILE* archivo = fopen(nombreArchivo, "w");
    imprimirArrayPiezasAlmacenArchivo(archivo);
    fclose(archivo);
    return 0;
};

int buscarPiezasAlmacen(){
    imprimirMensaje(1, 5, "====== BUSQUEDA DE PIEZAS EN ALMACEN ======");
    return 0;
};

int agregarPizasAlmacen(){
    imprimirMensaje(1, 5, "====== AGREGAR PIEZAS EN ALMACEN ======");
    return 0;
};

int eliminarPiezasAlmacen(){
    imprimirMensaje(1, 5, "====== ELIMINAR PIEZAS EN ALMACEN ======");
    return 0;
};

Herramienta* incializarHerramienta(char* id_herramienta, char* tipo, int usos, char* compatibilidad, float rango, char* material, int cantidad){
    Herramienta* herramienta = (Herramienta*)malloc(sizeof(Herramienta));
    if (herramienta == NULL)return NULL;

    herramienta->id_herramienta = id_herramienta;
    herramienta->tipo = tipo;
    herramienta->usos = usos;
    herramienta->compatibilidad = compatibilidad;
    herramienta->rango = rango;
    herramienta->material = material;
    herramienta->cantidad = cantidad;

    return herramienta;
}

int cargarAlmacen(){
    //Hace referencia a los arrays, si se modifican en otros lados, almacen tambien sera modificado
    almacenBaseDatos.array_list = &arrayTickets;        // ArrayTickets* ← OK
    //almacenBaseDatos.array_piezas = &arrayPiezas;       // ArrayPiezas* ← OK
    almacenBaseDatos.array_usuarios = &arrayUsuarios;   // ArrayUsuarios* ← OK
    almacenBaseDatos.pieza_almacen = &arrayPiezasAlmacen;

    precargarPiezasAlmacen(componentes_motor, CANTIDAD_PIEZASPRECARGADAS);
    precargarPiezasAlmacen(componentes_culata, CANTIDAD_PIEZASPRECARGADAS);
    precargarPiezasAlmacen(componentes_monoblock, CANTIDAD_PIEZASPRECARGADAS);

    return 1;
}

void precargarPiezasAlmacen(PiezaAlmacen pieza_almacen[], const int cantidad){
    for (int i = 0; i < cantidad; i++) {
        if (arrayPiezasAlmacen.tamanno >= arrayPiezasAlmacen.capacidad) {
            int nuevaCapacidad = arrayPiezasAlmacen.capacidad == 0 ? 1 : arrayPiezasAlmacen.capacidad * 2;
            PiezaAlmacen* nuevoArray = realloc(arrayPiezasAlmacen.datos, nuevaCapacidad * sizeof(PiezaAlmacen*));
            if (!nuevoArray) {
                imprimirMensaje(10,10,"Error al redimensionar el array de motores precargados");
                return;
            }
            arrayPiezasAlmacen.datos = nuevoArray;
            arrayPiezasAlmacen.capacidad = nuevaCapacidad;
        }

        arrayPiezasAlmacen.datos[arrayPiezasAlmacen.tamanno++] = pieza_almacen[i];
        id_piezaGlobal++;
    }
    //return ;

}

PiezaAlmacen* buscarPiezaPorIdUnico(ArrayPiezasAlmacen* inventario, int numPiezas, char *id_unico) {
    for (int i = 0; i < numPiezas; i++) {
        if (strcmp(inventario->datos[i].id_unicoPieza, id_unico) == 0) {
            return inventario[i].datos;
        }
    }
    return NULL;
}

void imprimirArrayPiezasAlmacen() {
    clear();  // Limpia la pantalla
    int fila = 2, columna = 4;

    // Título principal
    mvprintw(fila, columna, "===== INVENTARIO DE PIEZAS EN ALMACEN =====");
    fila += 2;

    if (arrayPiezasAlmacen.tamanno == 0) {
        mvprintw(fila, columna, "[No hay piezas registradas en el inventario]");
        fila += 2;
    } else {
        for (int i = 0; i < arrayPiezasAlmacen.tamanno; i++) {
            PiezaAlmacen* pieza = &arrayPiezasAlmacen.datos[i];

            mvprintw(fila++, columna, "Pieza #%d", i + 1);
            mvprintw(fila++, columna, "ID: %s", pieza->id_pieza);
            mvprintw(fila++, columna, "ID Unico: %s", pieza->id_unicoPieza);
            mvprintw(fila++, columna, "Tipo: %s", pieza->tipo);
            mvprintw(fila++, columna, "Tolerancia: %.2f mm", pieza->tolerancia);
            mvprintw(fila++, columna, "Material: %s", pieza->material);
            mvprintw(fila++, columna, "Estado: %s", pieza->estadoPieza);
            mvprintw(fila++, columna, "Compatibilidad: %s", pieza->compatibilidad);
            mvprintw(fila++, columna, "Cantidad: %d", pieza->cantidad);

            fila++; // Línea en blanco entre piezas
        }
    }

    // Instrucción final
    fila += 2;
    attron(A_BOLD);
    mvprintw(fila, columna, "Presione cualquier tecla para continuar...");
    attroff(A_BOLD);

    refresh();
    getch();
}

void imprimirArrayPiezasAlmacenArchivo(FILE* archivo) {
    if (archivo == NULL) return;

    fprintf(archivo, "===== INVENTARIO DE PIEZAS EN ALMACEN =====\n\n");

    if (arrayPiezasAlmacen.tamanno == 0) {
        fprintf(archivo, "[No hay piezas registradas en el inventario]\n\n");
    } else {
        for (int i = 0; i < arrayPiezasAlmacen.tamanno; i++) {
            PiezaAlmacen* pieza = &arrayPiezasAlmacen.datos[i];

            fprintf(archivo, "Pieza #%d\n", i + 1);
            fprintf(archivo, "ID: %s\n", pieza->id_pieza);
            fprintf(archivo, "ID Unico: %s\n", pieza->id_unicoPieza);
            fprintf(archivo, "Tipo: %s\n", pieza->tipo);
            fprintf(archivo, "Tolerancia: %.2f mm\n", pieza->tolerancia);
            fprintf(archivo, "Material: %s\n", pieza->material);
            fprintf(archivo, "Estado: %s\n", pieza->estadoPieza);
            fprintf(archivo, "Compatibilidad: %s\n", pieza->compatibilidad);
            fprintf(archivo, "Cantidad: %d\n", pieza->cantidad);
            fprintf(archivo, "\n"); // Espacio entre piezas
        }
    }

    fprintf(archivo, "--------------------------------------------\n");
}