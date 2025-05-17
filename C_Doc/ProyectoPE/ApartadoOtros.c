//
// Created by Jesus Emmanuel Garcia on 5/7/25.
//
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "UsuarioDTO.h"
#include "Util.h"
#include "UserInterface.h"
#include "LogicaNegocio.h"

#include "Testing.h"

void historialTickets(){
    char* nombreArchivo = obtenerNombreArchivo("Tickets_"); // malloc

    //Si existe por lo menos 1 ticket creara el archivo
    if (arrayTickets.tamanno < 1){
        imprimirMensaje(5, 5, "No existen Tickets Creados, porfavor crea nuevos tickets");
        return;
    }
    FILE* archivo = fopen(nombreArchivo, "w"); //Abrir archivo

    exportarDetallesTickets(nombreArchivo, archivo); // uso

    fclose(archivo); //Cerrar archivo
    free(nombreArchivo); // free -> string
};

void exportarDetallesTodoElSistema(){
    char* nombreArchivo = obtenerNombreArchivo("Detalles_SistemaCompleto");

    FILE* archivo = fopen(nombreArchivo, "w");

    //Imprimir en el siguiente orden
    /**
     * Usuarios
     * Motores Usuarios
     * Piezas de los usuarios
     * Tickets
     * Motores precargados
     */
    arrayUsuarios.tamanno > 0
        ? exportarDetallesUsuarios(nombreArchivo, archivo)
        : fprintf(archivo, "NO HAY USUARIOS EN LA BASE DE DATOS (arrayUsuarios)\n\n");
    // Esto lo hace detalles usuarios por la gerarquia de relaciones de objetos
    //arrayMotoresUsuarios.tamanno > 0 ? exportarMotoresUsuarios(nombreArchivo, archivo) : fprintf(archivo, "No hay MotoresUsuarios creados en la base de datos (arrayMotoresUsuarios)\n");
    //arrayPiezas.tamanno > 0 ? exportarDetallesPiezas(nombreArchivo,archivo) : fprintf(archivo, "No hay Piezas creados en la base de datos (arrayPiezas)\n");
    arrayTickets.tamanno > 0
        ? exportarDetallesTickets(nombreArchivo, archivo)
        : fprintf(archivo, "NO HAY TICKETS CREADOS EN LA BASE DE DATOS (arrayTickets)\n\n");
    arrayMotoresPrecargados.tamanno > 0
        ? exportarDetallesMotoresPrecargados(nombreArchivo, archivo)
        : fprintf(archivo, "NO HAY MOTORES PRECARCAGOS EN LA BASE DE DATOS (arrayMotoresPrecargados)\n\n");
    //Almacen
    arrayPiezasAlmacen.tamanno > 0
        ? exportarDetallesPiezasAlmacen(nombreArchivo, archivo)
        : fprintf(archivo, "No hay Piezas en el almacen registradas en la base de datos (arrayPiezasAlmacen)\n");
    //arrayAlmacen.tamanno > 0 ? exportarDetallesHerramientasAlmacen(nombreArchivo, archivo) : fprintf(archivo, "No hay Almacen creado en la base de datos (arrayAlmacen)\n");
    fclose(archivo);
    free(nombreArchivo);
};


/*
 * @param nombreArchivo
 * @param archivo
 * @return
 */
int exportarDetallesUsuarios(const char* nombreArchivo, FILE* archivo){
    RETURN_IF_ESC(validarArchivo(archivo));

    fprintf(archivo, "EXPORTANDO DETALLES DE ARRAY USUARIOS\n");
    fprintf(archivo, "Tamaño del array: %d\n\n", arrayUsuarios.tamanno);
    //Esto hace que por cada usuario valido imprima sus caracteristicas,
    //Asi Esto obliga a que cada usuario solamente tenga un motor asignado
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
        if (!motor){
            fprintf(archivo, "Motor: No asignado.\n\n");
            continue;
        }

        fprintf(archivo, "\n----------- DETALLES DEL MOTOR -----------\n");
        fprintf(archivo, "FOLIO: %s\n", usr->folio);
        fprintf(archivo, "ID Pieza: %d\n", motor->id_pieza);
        fprintf(archivo, "ID Usuario Asociado: %d\n", motor->id_usuario);
        fprintf(archivo, "Modelo: %s\n", motor->modelo);
        fprintf(archivo, "Numero de serie : %s\n", motor->numeroSerie);
        fprintf(archivo, "Fabricante: %s\n", motor->fabricante);
        fprintf(archivo, "Material: %s\n", motor->material);
        fprintf(archivo, "Carro Asociado: %s\n", motor->carroAsociado);
        fprintf(archivo, "Anno: %d\n", motor->anno);
        fprintf(archivo, "Carro Asociado: %s\n", motor->carroAsociado);
        fprintf(archivo, "Cilindrada (Litros) : %.2f\n", motor->cilindrada);
        fprintf(archivo, "Compresion Original (psi) : %.2f\n", motor->compresionOriginal);
        fprintf(archivo, "Combustible: %s", tipoCombustibleToStr(motor->tipoCombustible));
        fprintf(archivo, "Medida Original (mm) : %.2f\n", motor->medidaOriginal);
        fprintf(archivo, "Medida Actual (mm) : %.2f\n", motor->medidaActual);

        if (motor->culata){
            Culata* culata = motor->culata;
            fprintf(archivo, "\n----------- CULATA -----------\n");
            fprintf(archivo, "ID Pieza: %d\n", culata->id_pieza);
            fprintf(archivo, "ID Usuario: %d\n", culata->id_usuario);
            fprintf(archivo, "Desgaste Pieza: %.3f\n", culata->desgaste);
            fprintf(archivo, "Tolerancia Maxima: %.3f\n", culata->tolerancia);
            fprintf(archivo, "Altura Original: %.3f\n", culata->alturaOriginal);
            fprintf(archivo, "Altura Actual: %.3f\n", culata->alturaActual);
            fprintf(archivo, "Altura minima: %.3f\n", culata->alturaMinima);

            fprintf(archivo, "Numero Valvulas: %d\n", culata->numValvulas);
            fprintf(archivo, "Presion de Prueba: %.2f bar\n", culata->presionPrueba);
            fprintf(archivo, "Fisuras: %s \n", culata->tieneFisuras ? "Si" : "No");
            fprintf(archivo, "Estado de la Pieza: %s\n", estadoPiezaTexto(culata->operacionesMotor));
        }

        if (motor->monoblock && motor->monoblock->numCilindros){
            Monoblock* mono = motor->monoblock;
            fprintf(archivo, "\n----------- MONOBLOCK -----------\n");
            fprintf(archivo, "ID Pieza: %d\n", mono->id_pieza);
            fprintf(archivo, "ID Usuario: %d\n", mono->id_usuario);
            fprintf(archivo, "Numero Cilindros: %d\n", mono->numCilindros);
            fprintf(archivo, "Ovalizacion: %.2f mm\n", mono->ovalizacion_max);
            for (int j = mono->numCilindros; j < mono->numCilindros; j++){
                fprintf(archivo, "Diametro Cilindro %d : %.2f mm \n", j , mono->diametroCilindro[j]);
                fprintf(archivo, "Desalineacion Bancada: %.2f mm\n", mono->desalineacion_bancadas[j]);
            }
            fprintf(archivo, "Estado de la Pieza: %s\n", estadoPiezaTexto(mono->estado_diagnostico));
        }

        fprintf(archivo, "==============================================\n\n");
    }

    printf("Archivo generado exitosamente: %s\n", nombreArchivo);

    return 1;
}

int exportarDetallesMotoresPrecargados(const char* nombreArchivo, FILE* archivo){
    RETURN_IF_ESC(validarArchivo(archivo));

    fprintf(archivo, "EXPORTANDO DETALLES DE MOTORES PRECARGADOS\n");
    fprintf(archivo, "Tamaño del array: %d\n\n", arrayMotoresPrecargados.tamanno);

    for (int i = 0; i < arrayMotoresPrecargados.tamanno; i++){
        Motor* m = arrayMotoresPrecargados.datos[i];

        fprintf(archivo, "Motor #%d\n", i + 1);
        fprintf(archivo, "  ID de pieza: %d\n", m->id_pieza);
        fprintf(archivo, "  ID de usuario: %d\n", m->id_usuario);
        fprintf(archivo, "  Modelo: %s\n", m->modelo);
        fprintf(archivo, "  Fabricante: %s\n", m->fabricante);
        fprintf(archivo, "  Año: %d\n", m->anno);
        fprintf(archivo, "  Carro asociado: %s\n", m->carroAsociado ? m->carroAsociado : "N/A");
        fprintf(archivo, "  Cilindrada: %.2f L\n", m->cilindrada);
        fprintf(archivo, "  Compresion original: %.2f psi\n", m->compresionOriginal);
        fprintf(archivo, "  Numero de serie: %s\n", m->numeroSerie);
        fprintf(archivo, "  Tipo de combustible: %s\n", tipoCombustibleToStr(m->tipoCombustible));

        fprintf(archivo, "  Material: %s\n", m->material);
        fprintf(archivo, "  Medida original: %.2f mm\n", m->medidaOriginal);
        fprintf(archivo, "  Medida actual: %.2f mm\n", m->medidaActual);
        fprintf(archivo, "\n");
    }

    return 1;
}

int exportarDetallesPiezasAlmacen(const char* nombreArchivo, FILE* archivo){
    RETURN_IF_ESC(validarArchivo(archivo));

    fprintf(archivo, "==============================================\n\n");
    fprintf(archivo, "EXPORTANDO DETALLES DE MOTORES PRECARGADOS\n");
    fprintf(archivo, "Tamaño del array: %d\n\n", arrayPiezasAlmacen.tamanno);

    for (int i = 0; i < arrayPiezasAlmacen.tamanno; i++){
        PiezaAlmacen* p = &arrayPiezasAlmacen.datos[i];

        fprintf(archivo, "===== INVENTARIO DE PIEZAS EN ALMACEN =====");
        fprintf(archivo, "Pieza #%d\n", i + 1);
        fprintf(archivo, "ID: %s\n", p->id_pieza);
        fprintf(archivo, "ID Unico: %s\n", p->id_unicoPieza);
        fprintf(archivo, "Tipo: %s\n", p->tipo);
        fprintf(archivo, "Tolerancia: %.2f mm\n", p->tolerancia);
        fprintf(archivo, "Material: %s\n", p->material);
        fprintf(archivo, "Estado: %s\n", p->estadoPieza);
        fprintf(archivo, "Compatibilidad: %s\n", p->compatibilidad);
        fprintf(archivo, "Cantidad: %d\n", p->cantidad);
        fprintf(archivo, "------------------------\n");

        fprintf(archivo, "==============================================\n\n");
    }
    return 1;
}

int validarArchivo(FILE* archivo){
    if (!archivo){
        perror("No se pudo abrir el archivo");
        return -1;
    }
    return 1;
}