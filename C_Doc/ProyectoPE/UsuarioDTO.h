//
// Created by Jesus Emmanuel Garcia on 2/17/25.
//

#ifndef NEGOCIODTO_H
#define NEGOCIODTO_H
#include <stddef.h>

//Flags usados en monoblock debido a que un monoblock tiene varios estados
#define FLAG_CILINDROS_OK       0x01 // 0b0001
#define FLAG_BANCADAS_OK        0x02 // 0b0010
#define FLAG_FISURAS_DETECTADAS 0x04 // 0b0100
#define FLAG_SUPERFICIE_PLANA   0x08 // 0b1000

// Funciones para verificar banderas
#define IS_CILINDROS_OK(flags)    ((flags) & FLAG_CILINDROS_OK)
#define IS_BANCADAS_OK(flags)     ((flags) & FLAG_BANCADAS_OK)
#define IS_FISURAS_DETECTADAS(flags) ((flags) & FLAG_FISURAS_DETECTADAS)
#define IS_SUPERFICIE_PLANA(flags) ((flags) & FLAG_SUPERFICIE_PLANA)

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
    float* diametroCilindro;     // Diámetro nominal de los cilindros (mm)
    int num_bancadas;                   // Número de bancadas (determina tamaño de diametro_bancadas)
    float* diametro_bancadas;           // Arreglo dinámico para diámetros de bancadas (en mm)

    float ovalizacion_max;          // Deformación del cilindro (mm) / Máxima ovalización detectada (en mm)
    float* conicidad_max;                // Máxima conicidad detectada (en mm)
    float* desalineacion_bancadas;       // Desalineación máxima de bancadas (en mm)
    float planitud_superficie;          // Desviación de planitud de la superficie superior (en mm)
    int flags;                         // FLAGS DE CILINDROS/BANCADAS/FISURAS
    char* numero_serie;              // Número de serie del motor/monoblock
    char* observaciones;            // Notas del técnico
    int estado_diagnostico;           // 0: sin intervención, 1: rectificación, 2: reconstrucción
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
    char* numeroSerie;    // Número de serie del motor
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
    char* numeroSerie;        // Número de serie único del motor
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

// listas de cosas


// Detalles de los proveedores
typedef struct{

}Proveedor;

// Maquinaria
typedef struct  {

}Equipo;

// Caracteristicas y detalles de las Herramientas del almacen (tornillos) lainas, empaques, etc
typedef struct {
    char id_pieza[20];       // Identificador único de la pieza
    char* id_unicoPieza;
    char tipo[50];           // Tipo de pieza (e.g., Laina, Pistón, Válvula)
    float tolerancia;        // Tolerancia o medida específica (mm, bar, etc.)
    char material[20];       // Material de la pieza (e.g., Acero, Aluminio)
    char estadoPieza[20];    // Estado (Nueva, Reconstruida, Usada)
    char compatibilidad[100]; // Modelos/motores compatibles
    int cantidad;            // Cantidad en inventario
} PiezaAlmacen;

typedef struct{
    char* id_herramienta;    // Identificador único de la herramienta
    char* tipo;             // Tipo de herramienta (e.g., Micrómetro, Bruñidora, Llave de torque)
    int usos;                  // Número de veces que la herramienta ha sido utilizada
    char* compatibilidad;  // Motores o tareas compatibles (e.g., "Ford Duratec 2.0, Honda K20A")
    float rango;               // Rango de operación (e.g., 0-25 mm para micrómetro, 50-100 Nm para llave de torque)
    char* material;         // Material principal (e.g., Acero, Plástico)
    int cantidad;              // Cantidad disponible en inventario
}Herramienta;

typedef struct {
    PiezaAlmacen* datos;  // Puntero a la lista de PiezasAlmacen
    int tamanno;       // Número actual de usuarios / elementos
    int capacidad;   // Capacidad máxima del array
} ArrayPiezasAlmacen;
//No esta en uso
typedef struct {
    Herramienta* datos;  // Puntero a Herramientas
    int tamanno;       // Numero actual de Herramientas/ elementos
    int capacidad;   // Capacidad máxima del array
} ArrayHerramientasAlmacen;

typedef struct{
    // Array de tickets
    ArrayTickets* array_list;
    //Array de piezas
    //ArrayPiezas* array_piezas;
    //Array de usuarios
    ArrayUsuarios* array_usuarios;
    //Array de piezas del almacen
    ArrayPiezasAlmacen* pieza_almacen;

}Almacen;

//---------------------------------USUARIO DTO
Usuario inicializarUsuario(int id_usuario, char* folio,const char* nombreUsuario,const char* apellido,
                          long long celular,const char* email,const char* contacto);
Motor* inicializarMotor(Paramsmotor paramsmotor, int id_usuario, int id_pieza, void* tipoDePieza, int numTipoDepieza);
Culata* inicializarCulata(int id_pieza , int numValvulas, double presionPrueba,int fisuras,
                          float alturaOriginal, float alturaActual, float alturaMinima, int id_usuario, int estadoPieza);
Monoblock* inicializarMonoblock(int id_pieza, int id_usuario, int numCilindros, const float* diametroCilindro,
    const float* conicidad_max, int num_bancadas, const float* diametro_bancadas, const float* desalineacion_bancadas,
    float ovalizacion_max, float planitud_superficie, int flags, char* numero_serie, char* observaciones,
    int estado_diagnostico);
Motor* clonarMotor(Motor* original, int nuevoIdUsuario);
//Public
void setIdUsuarioLogico(int nuevoId);
int getIdUsuarioLogico();
void setIdLog(int id);
int getIdLog();

extern ArrayTickets arrayTickets;  // ← accedida desde otros .c
extern ArrayUsuarios arrayUsuarios; // ← accedida desde otros .c
extern ArrayPiezas arrayMotoresUsuarios;
extern ArrayPiezas arrayMotoresPrecargados;
extern ArrayPiezas arrayPiezas;
extern ArrayPiezasAlmacen arrayPiezasAlmacen;
extern Almacen almacenBaseDatos;
//private -> Declarada en UsuarioDTO.c
extern int id_UsuarioGlobal;
extern int id_piezaGlobal;


//---------------------------------UTIL
void mostrarUsuario(Usuario usr);

/**@deprecated */
void listarNumerosDeSerieMotores();
void liberarMotor(Motor* pz);



//---------------------------------ConstanteMotores.c
#define CANTIDAD_PIEZASPRECARGADAS 5
extern PiezaAlmacen componentes_motor[];
extern PiezaAlmacen componentes_culata[];
extern PiezaAlmacen componentes_monoblock[];


#endif //NEGOCIODTO_H