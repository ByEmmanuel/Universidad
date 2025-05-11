//
// Created by Jesus Emmanuel Garcia on 5/7/25.
//
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "UsuarioDTO.h"
#include "Util.h"
#include "UserInterface.h"
#include "LogicaNegocio.h"

#include "ConstantesMotores.h"
#include "Testing.h"

void historialTickets(){
    char* nombreArchivo = obtenerNombreArchivo("Tickets_"); // malloc

    FILE* archivo = fopen(nombreArchivo, "w"); //Abrir archivo

    exportarDetallesTickets(nombreArchivo, archivo);       // uso

    fclose(archivo);                                //Cerrar archivo
    free(nombreArchivo);                          // free -> string
};

void exportarDetallesTodoElSistema() {
    char* nombreArchivo = obtenerNombreArchivo("Detalles_SistemaCompleto");

    FILE* archivo = fopen(nombreArchivo,"w");

    //Imprimir en el siguiente orden
    /**
     * Usuarios
     * Motores Usuarios
     * Piezas de los usuarios
     * Tickets
     * Motores precargados
     */
    arrayUsuarios.tamanno > 0 ? exportarDetallesUsuarios(nombreArchivo,archivo) : fprintf(archivo, "No hay Usuarios creados en la base de datos (arrayUsuarios)\n");
    // Esto lo hace detalles usuarios por la gerarquia de relaciones de objetos
    //arrayMotoresUsuarios.tamanno > 0 ? exportarMotoresUsuarios(nombreArchivo, archivo) : fprintf(archivo, "No hay MotoresUsuarios creados en la base de datos (arrayMotoresUsuarios)\n");
    //arrayPiezas.tamanno > 0 ? exportarDetallesPiezas(nombreArchivo,archivo) : fprintf(archivo, "No hay Piezas creados en la base de datos (arrayPiezas)\n");
    arrayTickets.tamanno > 0 ? exportarDetallesTickets(nombreArchivo, archivo) : fprintf(archivo, "No hay Tickets creados en la base de datos (arrayTickets)\n");
    arrayMotoresPrecargados.tamanno > 0 ? exportarMotoresPrecargados(nombreArchivo, archivo) : fprintf(archivo, "No hay MotoresPrecargados creados en la base de datos (arrayMotoresPrecargados)\n");
    //Almacen


    free(nombreArchivo);
};

char* obtenerNombreArchivo(const char* textoInicial){
    char fecha[50];
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(fecha, sizeof(fecha), "%Y-%m-%d_%H-%M-%S", tm_info);


    char* nombreArchivo = malloc(200);
    if (nombreArchivo == NULL) {
        perror("Error al reservar memoria");
        exit(EXIT_FAILURE);
    }

    strcpy(nombreArchivo, textoInicial);
    strcat(nombreArchivo, fecha);
    strcat(nombreArchivo, ".txt");

    return nombreArchivo;
}

/*
int exportarDetallesArrayPiezas(const char* nombreArchivo, FILE* archivo) {
    RETURN_IF_ESC(validarArchivo(archivo));

    fprintf(archivo, "EXPORTANDO DETALLES DE ARRAY PIZAS\n");
    fprintf(archivo, "Tamaño del array: %d\n\n", arrayPiezas.tamanno);

    for (int i = 0; i < arrayPiezas.tamanno; i++){
        Pieza* usr = arrayPiezas.datos[i];
        if (!usr) continue;

        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "         INFORMACION DEL USUARIO\n");
        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "ID Usuario: %d\n", usr->id_usuario);
        fprintf(archivo, "Folio: %s\n", usr->folio);
        fprintf(archivo, "Nombre: %s %s\n", usr->nombreUsuario, usr->apellido);
        fprintf(archivo, "Celular: %lld\n", usr->celular);
        fprintf(archivo, "Email: %s\n", usr->email);
        fprintf(archivo, "Contacto: %s\n", usr->contacto);
        fprintf(archivo, "Activo: %s\n", usr->activo ? "Si" : "No");

        Motor* motor = usr->motor;
        if (!motor) {
            fprintf(archivo, "Motor: No asignado.\n\n");
            continue;
        }

        fprintf(archivo, "\n----------- DETALLES DEL MOTOR -----------\n");
        fprintf(archivo, "Modelo: %s\n",motor->modelo );
        fprintf(archivo, "Fabricante: %s\n", motor->material);
        fprintf(archivo, "Material: %s\n", motor->material);
        fprintf(archivo, "Carro Asociado: %s\n", motor->carroAsociado);

        if (motor->culata) {
            Culata* culata = motor->culata;
            fprintf(archivo, "\n----------- CULATA -----------\n");
            fprintf(archivo, "Numero Valvulas: %d\n", culata->numValvulas);
            fprintf(archivo, "Presion de Prueba: %.2f bar\n", culata->presionPrueba);
            fprintf(archivo, "Fisuras: %s\n", culata->tieneFisuras ? "Si" : "No");
            fprintf(archivo, "Estado de la Pieza: %s\n", estadoPiezaTexto(culata->operacionesMotor));
        }

        if (motor->monoblock) {
            Monoblock* mono = motor->monoblock;
            fprintf(archivo, "\n----------- MONOBLOCK -----------\n");
            fprintf(archivo, "Numero Cilindros: %d\n", mono->numCilindros);
            fprintf(archivo, "Diametro: %.2f mm\n", mono->diametroCilindro);
            fprintf(archivo, "Ovalizacion: %.2f mm\n", mono->ovalizacion);
            fprintf(archivo, "Alineacion Ciguenal: %.2f mm\n", mono->alineacionCiguenal);
            fprintf(archivo, "Estado de la Pieza: %s\n", estadoPiezaTexto(mono->estadoPieza));
        }

        fprintf(archivo, "==============================================\n\n");
    }

    printf("Archivo generado exitosamente: %s\n", nombreArchivo);
    }

    return 1;
}
*/
long long a;
/**
 *
 *
 * typedef struct {
    int id_pieza;              // IDENTIFICADOR UNICO DE LA PIEZA -> TODAS LAS PIEZAS DE UN MOTOR DEBEN CONTENER EL MISMO ID
    int id_usuario;            // IDENTIFICADOR UNICO DE LA PIEZA POR USUARIO, ES DECIR, A QUE USUARIO PERTENECE ESTA PIEZA
    int numCilindros;           // Número de cilindros en el bloque

    float diametroCilindro;     // Diámetro nominal de los cilindros (mm)
    float ovalizacion;          // Deformación del cilindro (mm)
    float alineacionCiguenal;   // Desalineación del cigüeñal respecto al bloque (mm)
    float desgasteCilindros;    // Desgaste promedio de los cilindros (mm)

    float desgaste;      // Desgaste en altura de culata (mm o %)
    float tolerancia;    // Tolerancia de rectificado (mm)

     0 = No intervención
     * 1 = Rectificación
     * 2 = Reconstrucción

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
    float medidaOriginal;       // Medida original de referencia (por ejemplo, diámetro cilindros) (mm)
    float medidaActual;         // Medida actual tras desgaste (mm)
} Motor;
//Entidad Usuario
typedef struct {
    Motor* motor;
    char contacto[20];
    long long numeroContacto;
    int activo;
}Usuario;
 * @param nombreArchivo
 * @param archivo
 * @return
 */
int exportarDetallesArrayUsuarios(const char* nombreArchivo, FILE* archivo) {
    RETURN_IF_ESC(validarArchivo(archivo));

    fprintf(archivo, "EXPORTANDO DETALLES DE ARRAY USUARIOS\n");
    fprintf(archivo, "Tamaño del array: %d\n\n", arrayUsuarios.tamanno);

    for (int i = 0; i < arrayUsuarios.tamanno; i++){
        Usuario* usr = arrayUsuarios.datos;
        if (!usr) continue;

        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "         INFORMACION DEL USUARIO\n");
        fprintf(archivo, "==============================================\n");
        fprintf(archivo, "ID Usuario: %d\n", usr->id_usuario);
        fprintf(archivo, "Folio: %s\n", usr->folio);
        fprintf(archivo, "Nombre: %s %s\n", usr->nombreUsuario, usr->apellido);
        fprintf(archivo, "Celular: %lld\n", usr->celular);
        fprintf(archivo, "Email: %s\n", usr->email);
        fprintf(archivo, "Contacto: %s\n", usr->contacto);
        fprintf(archivo, "Activo: %s\n", usr->activo ? "Si" : "No");
        //fprintf(archivo, "Numero contacto: %ll\n", usr->numeroContacto);

        Motor* motor = usr->motor;
        if (!motor) {
            fprintf(archivo, "Motor: No asignado.\n\n");
            continue;
        }

        fprintf(archivo, "\n----------- DETALLES DEL MOTOR -----------\n");
        fprintf(archivo, "Modelo: %s\n",motor->modelo );
        fprintf(archivo, "Fabricante: %s\n", motor->material);
        fprintf(archivo, "Material: %s\n", motor->material);
        fprintf(archivo, "Carro Asociado: %s\n", motor->carroAsociado);

        if (motor->culata) {
            Culata* culata = motor->culata;
            fprintf(archivo, "\n----------- CULATA -----------\n");
            fprintf(archivo, "Numero Valvulas: %d\n", culata->numValvulas);
            fprintf(archivo, "Presion de Prueba: %.2f bar\n", culata->presionPrueba);
            fprintf(archivo, "Fisuras: %s\n", culata->tieneFisuras ? "Si" : "No");
            fprintf(archivo, "Estado de la Pieza: %s\n", estadoPiezaTexto(culata->operacionesMotor));
        }

        if (motor->monoblock) {
            Monoblock* mono = motor->monoblock;
            fprintf(archivo, "\n----------- MONOBLOCK -----------\n");
            fprintf(archivo, "Numero Cilindros: %d\n", mono->numCilindros);
            fprintf(archivo, "Diametro: %.2f mm\n", mono->diametroCilindro);
            fprintf(archivo, "Ovalizacion: %.2f mm\n", mono->ovalizacion);
            fprintf(archivo, "Alineacion Ciguenal: %.2f mm\n", mono->alineacionCiguenal);
            fprintf(archivo, "Estado de la Pieza: %s\n", estadoPiezaTexto(mono->estadoPieza));
        }

        fprintf(archivo, "==============================================\n\n");
    }

    printf("Archivo generado exitosamente: %s\n", nombreArchivo);

    return 1;
}

int exportarDetallesMotoresPrecargados(const char* nombreArchivo, FILE* archivo) {
    RETURN_IF_ESC(validarArchivo(archivo));

    fprintf(archivo, "EXPORTANDO DETALLES DE MOTORES PRECARGADOS\n");
    fprintf(archivo, "Tamaño del array: %d\n\n", arrayMotoresPrecargados.tamanno);

    return 1;
}

int exportarDetallesUsuarios(const char* nombreArchivo, FILE* archivo) {
    RETURN_IF_ESC(validarArchivo(archivo));

    fprintf(archivo, "EXPORTANDO DETALLES DE ARRAY USUARIOS\n");
    fprintf(archivo, "Tamaño del array: %d\n\n", arrayUsuarios.tamanno);


    return 1;
}

int validarArchivo(FILE* archivo){
    if (!archivo) {
        perror("No se pudo abrir el archivo");
        return -1;
    }
    return 1;
}
//arrayPiezas.tamanno > 0 ? imprimirMensaje(5,5,"array Piezas Esta Vacio") : fprintf(archivo, "\n");
//arrayUsuarios.tamanno > 0 ? imprimirMensaje(5,5,"arrayUsuarios esta vacio") : fprintf(archivo, "\n");
//arrayMotoresPrecargados.tamanno > 0 ? imprimirMensaje(5,5,"arrayMotoresPrecargados esta vacio") : fprintf(archivo, "\n");
//arrayMotoresUsuarios.tamanno > 0 ? imprimirMensaje(5,5,"arrayMotoresUsuarios esta vacio") : fprintf(archivo, "\n");