//UsuarioDTO
#ifndef NEGOCIODTO_H
#define NEGOCIODTO_H
#include <stddef.h>


#define FLAG_CILINDROS_OK       0x01
#define FLAG_BANCADAS_OK        0x02
#define FLAG_FISURAS_DETECTADAS 0x04
#define FLAG_SUPERFICIE_PLANA   0x08


#define IS_CILINDROS_OK(flags)    ((flags) & FLAG_CILINDROS_OK)
#define IS_BANCADAS_OK(flags)     ((flags) & FLAG_BANCADAS_OK)
#define IS_FISURAS_DETECTADAS(flags) ((flags) & FLAG_FISURAS_DETECTADAS)
#define IS_SUPERFICIE_PLANA(flags) ((flags) & FLAG_SUPERFICIE_PLANA)


typedef enum { MONOBLOCK = 0, CULATA = 1 } TipoPieza;

typedef enum { GASOLINA = 0, DIESEL = 1, HIBRIDO = 2 } TipoCombustible;


typedef struct {
    int id_pieza;
    int id_usuario;
    int numValvulas;
    double presionPrueba;
    int tieneFisuras;

    float desgaste;
    float tolerancia;

    float alturaOriginal;
    float alturaActual;
    float alturaMinima;


    int estadoTemporalPieza;


    int operacionesMotor;
} Culata;

typedef struct {
    int id_pieza;
    int id_usuario;
    int numCilindros;
    float *diametroCilindro;
    int num_bancadas;
    float *diametro_bancadas;

    float ovalizacion_max;
    float *conicidad_max;
    float *desalineacion_bancadas;
    float planitud_superficie;
    int flags;
    char *numero_serie;
    char *observaciones;
    int estado_diagnostico;
    int operacionesMonoblock;
    int estadoTemporalPieza;
    int operacionesMotor;
} Monoblock;

typedef struct {
    int id_pieza;
    int id_usuario;

    const char *modelo;
    const char *fabricante;
    int anno;
    char *carroAsociado;
    float cilindrada;
    float compresionOriginal;
    char *numeroSerie;
    TipoCombustible tipoCombustible;

    Culata *culata;
    Monoblock *monoblock;

    char material[30];


    float medidaOriginal;
    float medidaActual;
} Motor;


typedef struct {
    Motor *motor;
    int id_usuario;
    char folio[12];
    char nombreUsuario[20];
    char apellido[20];
    long long celular;
    char email[30];
    char contacto[20];
    long long numeroContacto;
    int activo;
} Usuario;

typedef struct {
    Usuario *usuario;

    int lavado;
    char *detalles;
    char *detalles2;
} Ticket;


typedef struct {
    Usuario *datos;
    int tamanno;
    int capacidad;
} ArrayUsuarios;

typedef struct {
    Ticket *datos;
    int tamanno;
    int capacidad;
} ArrayTickets;

typedef struct {
    void **datos;
    int id_usuario;
    int tamanno;
    int capacidad;
} ArrayPiezas;


typedef struct {
    void **data;
    size_t size;
    size_t capacidad;
} ArrayList;


typedef struct {
    int id_pieza;
    int id_usuario;
    const char *modelo;
    const char *fabricante;
    char *carroAsociado;
    int anno;
    float cilindrada;
    float compresionOriginal;
    char *numeroSerie;
    TipoCombustible tipoCombustible;


    char *material;

    float medidaOriginal;
    float medidaActual;
} Paramsmotor;


typedef struct {
} Proveedor;


typedef struct {
} Equipo;


typedef struct {
    char id_pieza[20];
    char *id_unicoPieza;
    char tipo[50];
    float tolerancia;
    char material[20];
    char estadoPieza[20];
    char compatibilidad[100];
    int cantidad;
} PiezaAlmacen;

typedef struct {
    char *id_herramienta;
    char *tipo;
    int usos;
    char *compatibilidad;
    float rango;
    char *material;
    int cantidad;
} Herramienta;

typedef struct {
    PiezaAlmacen *datos;
    int tamanno;
    int capacidad;
} ArrayPiezasAlmacen;

typedef struct {
    Herramienta *datos;
    int tamanno;
    int capacidad;
} ArrayHerramientasAlmacen;

typedef struct {
    ArrayTickets *array_list;


    ArrayUsuarios *array_usuarios;

    ArrayPiezasAlmacen *pieza_almacen;
} Almacen;


Usuario inicializarUsuario(int id_usuario, char *folio, const char *nombreUsuario, const char *apellido,
                           long long celular, const char *email, const char *contacto);

Motor *inicializarMotor(Paramsmotor paramsmotor, int id_usuario, int id_pieza, void *tipoDePieza, int numTipoDepieza);

Culata *inicializarCulata(int id_pieza, int numValvulas, double presionPrueba, int fisuras,
                          float alturaOriginal, float alturaActual, float alturaMinima, int id_usuario,
                          int estadoPieza);

Monoblock *inicializarMonoblock(int id_pieza, int id_usuario, int numCilindros, const float *diametroCilindro,
                                const float *conicidad_max, int num_bancadas, const float *diametro_bancadas,
                                const float *desalineacion_bancadas,
                                float ovalizacion_max, float planitud_superficie, int flags, char *numero_serie,
                                char *observaciones,
                                int estado_diagnostico);

Motor *clonarMotor(Motor *original, int nuevoIdUsuario);

void setIdUsuarioLogico(int nuevoId);

int getIdUsuarioLogico();

void setIdLog(int id);

int getIdLog();

void setIdPiezaGlobal(int id);

int getIdPiezaGlobal();

extern ArrayTickets arrayTickets;
extern ArrayUsuarios arrayUsuarios;
extern ArrayPiezas arrayMotoresUsuarios;
extern ArrayPiezas arrayMotoresPrecargados;
extern ArrayPiezas arrayPiezas;
extern ArrayPiezasAlmacen arrayPiezasAlmacen;
extern Almacen almacenBaseDatos;


void mostrarUsuario(Usuario usr);


void listarNumerosDeSerieMotores();

void liberarMotor(Motor *pz);


#define CANTIDAD_PIEZASPRECARGADAS 5
extern PiezaAlmacen componentes_motor[];
extern PiezaAlmacen componentes_culata[];
extern PiezaAlmacen componentes_monoblock[];


#endif
