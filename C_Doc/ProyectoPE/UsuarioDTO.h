//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//

#ifndef NEGOCIODTO_H
#define NEGOCIODTO_H
#include <stddef.h>


// 0 Monoblock, 1 culata
typedef enum { MONOBLOCK = 0, CULATA = 1 } TipoPieza;
// 0 GASOLINA, 1 DIESEL, 2 HIBRIDO
typedef enum { GASOLINA = 0, DIESEL = 1, HIBRIDO = 2 } TipoCombustible;
//  Encapsulamiento Privado
//  Dejar de usar Pieza como Base -> Cambiar a motor

typedef struct{
    int id_pieza;            // Identificador único de la pieza
    int id_usuario;         // Este id esta sujeto con una relacion al usuario

    const char* nombre;
    const char* fabricante;
    float cilindrada;              // Litros
    float compresionOriginal;      // psi
    const char* numeroSerie;       // Número de serie único del motor
    TipoCombustible tipoCombustible;

    TipoPieza tipoPieza;
    char material[30];      // Material de la pieza (Hierro, Aluminio, etc.)
    float desgaste;         // Nivel de desgaste en porcentaje (0-100%)
    float tolerancia;       // Tolerancia máxima de desgaste permitida antes de rectificar
    float medidaOriginal;   // Medida original de la pieza -> mm
    float medidaActual;     // Medida actual después del desgaste -> mm
    int necesitaRectificacion; // 1 = Sí, 0 = No (según tolerancia)
}Motor;

// Estructura Culata que "hereda" de Pieza
typedef struct {
    Motor motor; // Composición: Culata contiene una Pieza
    int numValvulas;
    double presionPrueba;
    //TipoCombustible tipoCombustible;// Movido a Motor
    int tieneFisuras;
} Culata;

// Estructura Monoblock que "hereda" de Pieza
/**@deprecated Funcion en desuso*/
typedef struct {
    Motor motor; // Composición: Monoblock contiene una Pieza
    int numCilindros;
    float diametroCilindro;
    float ovalizacion;
    float alineacionCiguenal;
} Monoblock;

//Entidad Usuario
typedef struct {
    //Antes
    //Pieza* pieza
    Motor* motor;
    int id_usuario;
    char folio[12];
    char nombreUsuario[20];
    char apellido[20];
    long long celular;
    char email[30];
    char contacto[20];
    int activo;
}Usuario;

/**@deprecated Funcion en desuso*/
typedef struct{
    Usuario* usuario;
    Culata* culata;
    Monoblock* monoblock;
    char detalles[255];
    char detalles2[255];
}Ticket;

// Estructura para el array dinámico de Usuarios
typedef struct {
    Usuario* datos;  // Puntero a la lista de usuarios
    int total;       // Número actual de usuarios / elementos
    int capacidad;   // Capacidad máxima del array
} ArrayUsuarios;

/**@deprecated Funcion en desuso*/
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

/**Variables globales que se usan en todo momento de la ejecucion del programa,
 * No se crean nuevas instancias de estos objetos
V2 - NO USAR -> Causa Error de compilacion
ArrayUsuarios arrayUsuarios;
ArryTickets arrayTickets;
ArrayList array_list;
ArrayPiezas arrayPiezas;
*/

typedef struct {
    const char* nombre;
    const char* fabricante;
    float cilindrada;              // Litros
    float compresionOriginal;      // psi
    TipoCombustible tipoCombustible;

    TipoPieza tipoPieza;
    char* material;      // Material de la pieza (Hierro, Aluminio, etc.)
    float desgaste;         // Nivel de desgaste en porcentaje (0-100%)
    float tolerancia;       // Tolerancia máxima de desgaste permitida antes de rectificar
    float medidaOriginal;   // Medida original de la pieza -> mm
    float medidaActual;     // Medida actual después del desgaste -> mm
    int necesitaRectificacion; // 1 = Sí, 0 = No (según tolerancia)
}Paramsmotor;

Usuario inicializarUsuario(int id_usuario, const char* folio,const char* nombreUsuario,
    const char* apellido,long long celular,const char* email,const char* contacto);

int cliente();

void mostrarUsuario(Usuario usr);

void modificarCliente();

int guardarUsuarioArray(Usuario usuario);

int guardarPiezaArray(void* pieza);

Motor inicializarMotor(Paramsmotor motor, int id_usuario, int id_pieza, const char* numero_serie);

//Culata* inicializarCulata(Paramsmotor pieza, int num_valvulas, double presion_prueba, int fisuras);
Culata* inicializarCulata(const Motor pieza, const int numValvulas ,const double presionPrueba
                /** const int tipoCombustible */, const int fisuras);

//Culata* inicializarCulata(Motor pieza,int numValvulas , double presionPrueba
//    /** int tipoCombustible */ ,int fisuras);

/**@deprecated */
void imprimirPiezasPorUsuario(int id_usuario);

/**@deprecated */
void listarUsuarios(ArrayUsuarios listaUsuarios);

void listarFoliosUsuarios();

void listarPiezas();

#endif //NEGOCIODTO_H