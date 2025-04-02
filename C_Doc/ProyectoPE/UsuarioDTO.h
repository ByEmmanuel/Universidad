//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//

#ifndef NEGOCIODTO_H
#define NEGOCIODTO_H
#include <stddef.h>

// 0 Monoblock, 1 culata
typedef enum { MONOBLOCK, CULATA } TipoPieza;
// 0 GASOLINA, 1 DIESEL, 2 HIBRIDO
typedef enum { GASOLINA = 0, DIESEL = 1, HIBRIDO = 2 } TipoCombustible;

typedef struct{
    int id_Pieza;            // Identificador único de la pieza
    int id_Usuario;
    TipoPieza tipo;
    char material[30];      // Material de la pieza (Hierro, Aluminio, etc.)
    float desgaste;         // Nivel de desgaste en porcentaje (0-100%)
    float tolerancia;       // Tolerancia máxima de desgaste permitida antes de rectificar
    float medidaOriginal;   // Medida original de la pieza en mm
    float medidaActual;     // Medida actual después del desgaste
    int necesitaRectificacion; // 1 = Sí, 0 = No (según tolerancia)
}Pieza;

// Estructura Culata que "hereda" de Pieza
typedef struct {
    Pieza base; // Composición: Culata contiene una Pieza
    int numValvulas;
    double presionPrueba;
    TipoCombustible tipoCombustible;
    int tieneFisuras;
} Culata;

// Estructura Monoblock que "hereda" de Pieza
typedef struct {
    Pieza base; // Composición: Monoblock contiene una Pieza
    int numCilindros;
    float diametroCilindro;
    float ovalizacion;
    float alineacionCiguenal;
} Monoblock;

//Entidad Usuario
typedef struct {
    Pieza* pieza;
    int id_usuario;
    char folio[12];
    char nombreUsuario[20];
    char apellido[20];
    long long celular;
    char email[30];
    char contacto[20];
}Usuario;

typedef struct{
    Usuario* usuario;
    Pieza* pieza;
    char detalles[255];
    char detalles2[255];
}Ticket;

// Estructura para el array dinámico de Usuarios
typedef struct {
    Usuario* datos;  // Puntero a la lista de usuarios
    int total;       // Número actual de usuarios / elementos
    int capacidad;   // Capacidad máxima del array
} ArrayUsuarios;

typedef struct{
    Ticket* datos;
    int tamaño;
    int capacidad;
}ArryTickets;

typedef struct {
    void** datos;  // Puntero a la lista de usuarios
    int tamaño;       // Número actual de Piezas / elementos
    int capacidad;   // Capacidad máxima del array
} ArrayPiezas;

// Array para x Objeto
typedef struct {
    void** data;    // Arreglo dinámico de punteros genéricos
    size_t size;    // Número de elementos actuales
    size_t capacidad;// Capacidad total del arreglo
} ArrayList;

void asignarPiezaUsuario(Usuario *usr, Pieza *pieza);

Usuario inicializarUsuario(int id_usuario, const char* folio,const char* nombreUsuario,const char* apellido,long long celular,const char* email,const char* contacto);

int cliente();

void mostrarUsuario(Usuario usr);

void modificarCliente();

int guardarUsuarioArray(Usuario usuario);

/**
 * @Deprecated
 */
ArrayUsuarios* inicializarArrayUsuarios(int capacidadInicial);

int guardarPiezaArray(void* pieza);

Pieza inicializarPieza(int id_Usuario, int tipoPieza, const char* material,float desgaste, float tolerancia,
    float medidaOriginal, float medidaActual, int necesitaRectificacion );

Culata inicializarCulata(Pieza pieza,int numValvulas ,double presionPrueba,
    int tipoCombustible,int fisuras);

void imprimirPiezasPorUsuario(int id_usuario);

void listarUsuarios(ArrayUsuarios listaUsuarios);

void listarPiezas();

#endif //NEGOCIODTO_H