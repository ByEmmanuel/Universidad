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

// Estructura Monoblock que "hereda" de Pieza
typedef struct {
    int id_pieza;              // IDENTIFICADOR UNICO DE LA PIEZA -> TODAS LAS PIEZAS DE UN MOTOR DEBEN CONTENER EL MISMO ID
    int id_usuario;            // IDENTIFICADOR UNICO DE LA PIEZA POR USUARIO, ES DECIR, A QUE USUARIO PERTENECE ESTA PIEZA
    int numValvulas;           // Número de válvulas en la culata
    double presionPrueba;      // Presión medida en prueba hidráulica (bar)
    int tieneFisuras;          // 1 = Sí, 0 = No (fisuras detectadas)

    float desgaste;      // Desgaste en altura de culata (mm o %)
    float tolerancia;    // Tolerancia de rectificado (mm)

    float alturaOriginal;      // Altura original de la culata (mm)
    float alturaActual;        // Altura actual de la culata tras desgaste (mm)
    float alturaMinima;        // Altura mínima aceptable (según fabricante) (mm)

    /* 0 = No intervención
     * 1 = Rectificación
     * 2 = Reconstrucción
     */
    int estadoTemporalPieza;

    /*    Operaciones Realizadas con el motor
     *  0 : No se han realizado operaciones con el motor
     *  1 : Desmote del motor
     *  2 : Lavado inicial
     *  3 : Rectificacion o Reconstruccion
     *  4 : Lavado final
     *  5 : Pruebas Unitarias
     *  6 : Montado del motor
     */
    int operacionesMotor;
} Culata;

typedef struct {
    int id_pieza;              // IDENTIFICADOR UNICO DE LA PIEZA -> TODAS LAS PIEZAS DE UN MOTOR DEBEN CONTENER EL MISMO ID
    int id_usuario;            // IDENTIFICADOR UNICO DE LA PIEZA POR USUARIO, ES DECIR, A QUE USUARIO PERTENECE ESTA PIEZA
    int numCilindros;           // Número de cilindros en el bloque

    float diametroCilindro;     // Diámetro nominal de los cilindros (mm)
    float ovalizacion;          // Deformación del cilindro (mm)
    float alineacionCiguenal;   // Desalineación del cigüeñal respecto al bloque (mm)
    float desgasteCilindros;    // Desgaste promedio de los cilindros (mm)

    float desgaste;      // Desgaste en altura de culata (mm o %)
    float tolerancia;    // Tolerancia de rectificado (mm)

    /* 0 = No intervención
     * 1 = Rectificación
     * 2 = Reconstrucción
     */
    int estadoPieza;
} Monoblock;

typedef struct {
    int id_pieza;              // IDENTIFICADOR UNICO DE LA PIEZA -> TODAS LAS PIEZAS DE UN MOTOR DEBEN CONTENER EL MISMO ID
    int id_usuario;            // IDENTIFICADOR UNICO DE LA PIEZA POR USUARIO, ES DECIR, A QUE USUARIO PERTENECE ESTA PIEZA

    const char* modelo;         // Nombre del motor (modelo).
    const char* fabricante;     // Fabricante del motor
    int anno;                    // Año del motor
    char* carroAsociado;
    float cilindrada;           // Cilindrada total (litros)
    float compresionOriginal;   // Compresión de fábrica (psi)
    const char* numeroSerie;    // Número de serie del motor
    TipoCombustible tipoCombustible; // Tipo de combustible (enum GASOLINA, DIESEL, etc.)

    Culata* culata;             // Culata asociada
    Monoblock* monoblock;       // Monoblock asociado

    char material[30];          // Material del bloque/cabeza (Aluminio, Hierro, etc.)
    /** Movido a culata y monoblock
    float desgaste;             // Nivel de desgaste general (0-100%)
    float tolerancia;           // Tolerancia máxima permitida de desgaste (mm)
     */

    float medidaOriginal;       // Medida original de referencia (por ejemplo, diámetro cilindros) (mm)
    float medidaActual;         // Medida actual tras desgaste (mm)

} Motor;

//Entidad Usuario
typedef struct {
    //Antes
    //Pieza* pieza
    /* Ahora usuario solo tendra Motor y no cada pieza por separado
     *Culata* culata;
    Monoblock* monoblock;
    */
    Motor* motor;
    int id_usuario;
    char folio[12];
    char nombreUsuario[20];
    char apellido[20];
    long long celular;
    char email[30];
    char contacto[20];
    long long numeroContacto;
    int activo;
}Usuario;

typedef struct{
    Usuario* usuario;
    /*
     *Culata* culata;
    Monoblock* monoblock;
    */
    int lavado;
    char* detalles;
    char* detalles2;
}Ticket;

// Estructura para el array dinámico de Usuarios
typedef struct {
    Usuario* datos;  // Puntero a la lista de usuarios
    int tamanno;       // Número actual de usuarios / elementos
    int capacidad;   // Capacidad máxima del array
} ArrayUsuarios;

typedef struct{
    Ticket* datos;
    int tamanno;
    int capacidad;
}ArrayTickets;

typedef struct {
    void** datos;  // Puntero a la lista de usuarios
    int id_usuario;
    int tamanno;       // Número actual de Piezas / elementos
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
    int id_pieza;
    int id_usuario;
    const char* modelo;             // Modelo específico del motor
    const char* fabricante;         // Marca o fabricante (Ford, Toyota, etc.)
    char* carroAsociado;
    int anno;                        // Año de fabricación del motor
    float cilindrada;               // Cilindrada total en litros
    float compresionOriginal;       // Compresión de fábrica en psi
    const char* numeroSerie;        // Número de serie único del motor
    TipoCombustible tipoCombustible;// Tipo de combustible (GASOLINA, DIESEL, etc.)

    //TipoPieza tipoPieza;            // Tipo de pieza: CULATA, MONOBLOCK, etc.
    //Culata* culata;                 // Puntero a Culata asociada
    //Monoblock* monoblock;           // Puntero a Monoblock asociada

    char* material;              // Material principal del motor (Hierro, Aluminio, etc.)
    /*
    float desgaste;                 // Porcentaje de desgaste (0-100%)
    float tolerancia;               // Margen máximo de desgaste permitido (mm)
    */
    float medidaOriginal;           // Medida nominal de fábrica (mm)
    float medidaActual;             // Medida actual después de desgaste (mm)

    /** movidos a culata y monoblock
    int necesitaRectificacion;      // 1 = Sí (rectifica) / 0 = No
    int necesitaReconstruccion;     // 1 = Sí (reconstruir por daño grave) / 0 = No
    */

} Paramsmotor;

Usuario inicializarUsuario(int id_usuario, const char* folio,const char* nombreUsuario,
    const char* apellido,long long celular,const char* email,const char* contacto);

Ticket inicializarTicket(Usuario* usuario,Motor* motor ,char* detalles, char* detalles2);

extern ArrayTickets arrayTickets;  // ← accedida desde otros .c
extern ArrayUsuarios arrayUsuarios; // ← accedida desde otros .c
extern ArrayPiezas arrayMotoresUsuarios;
extern ArrayPiezas arrayMotoresPrecargados;
extern ArrayPiezas arrayPiezas;
//private -> Declarada en UsuarioDTO.c
extern int id_UsuarioGlobal;
extern int id_piezaGlobal;

//Public
void setIdUsuarioLogico(int nuevoId);
int getIdUsuarioLogico();

int cliente();

void mostrarUsuario(Usuario usr);

int modificarCliente();

int guardarUsuarioArray(Usuario usuario);

int guardarMotorArray(void* motor, int id_usuario);

int guardarPiezaArray(void* pieza, int id_usuario);

int guardarTicket(Ticket ticket);

Motor* inicializarMotor(Paramsmotor paramsmotor, int id_usuario, int id_pieza, void* tipoDePieza, int numTipoDepieza);

Culata* inicializarCulata(int id_pieza , int numValvulas, double presionPrueba,int fisuras,
    float alturaOriginal, float alturaActual, float alturaMinima, int id_usuario, int estadoPieza);



//Culata* inicializarCulata(Motor pieza,int numValvulas , double presionPrueba
//    /** int tipoCombustible */ ,int fisuras);


/**@deprecated */
void listarUsuarios(ArrayUsuarios listaUsuarios);

void listarFoliosUsuarios();
void listarNumerosDeSerieMotores();

void listarPiezas();

#endif //NEGOCIODTO_H