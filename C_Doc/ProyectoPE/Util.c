//Utils
#include "Util.h"

#include <ctype.h>
#include <limits.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "UserInterface.h"
#include "LogicaNegocio.h"

char *strFill(const char *str) {
    if (str == NULL) return NULL;

    const char *start = str;
    while (*start == ' ') start++;

    if (*start == '\0') {
        char *result = (char *) malloc(1);
        result[0] = '\0';
        return result;
    }

    const char *end = str + strlen(str) - 1;
    while (end > start && *end == ' ') end--;

    int len = end - start + 1;
    char *result = (char *) malloc(len + 1);
    if (result == NULL) return NULL;

    strncpy(result, start, len);
    result[len] = '\0';
    return result;
}

int strEquals(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return (str1 == str2);
    }
    return strcmp(str1, str2) == 0;
}

int strIsEmpty(const char *str) {
    if (str == NULL) return 1;
    return str[0] == '\0';
}

int strContains(const char *src, const char *str) {
    if (src == NULL || str == NULL) return 0;
    return strstr(src, str) != NULL;
}


void asignString(char *dst, const char *src, const size_t n) {
    if (src == NULL) {
        dst[0] = '\0';
        return;
    }
    strncpy(dst, src, n - 1);
    dst[n - 1] = '\0';
}

char *generarFolio(const char *nombre) {
    char *folio = (char *) malloc(13);

    if (folio == NULL) {
        printf("Error de memoria al reservar %d bytes\n", 13);
        return NULL;
    }

    int len = strlen(nombre);

    for (int i = 0; i < 3; i++) {
        if (i < len) {
            folio[i] = toupper(nombre[i]);
        } else {
            folio[i] = 'X';
        }
    }

    srand(time(NULL) + len);
    for (int i = 3; i < 12; i++) {
        folio[i] = '0' + rand() % 10;
    }


    folio[12] = '\0';
    return folio;
}

void cleanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}


int validarString(const char *src) {
    if (src == NULL) {
        return -1;
    }
    return 1;
}

char *enterString(int length) {
    char *buffer = (char *) malloc(length + 1);
    if (buffer == NULL) {
        perror("Error al asignar memoria");
        exit(1);
    }
    if (fgets(buffer, length + 1, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
    return buffer;
}


char *leerString(int y, int x, int maxLen, char *pregunta) {
    mvprintw(y, x, "%s  ", pregunta);
    char *buffer = (char *) malloc(maxLen + 1);
    if (!buffer) {
        mvprintw(y + 1, x, "Error: No se pudo asignar memoria.");
        refresh();
        return NULL;
    }
    memset(buffer, 0, maxLen + 1);

    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int ch, pos = 0;
    move(y, x + strlen(pregunta) + 2);
    while (1) {
        ch = getch();
        if (ch == 27) {
            free(buffer);
            return NULL;
        } else if (ch == '\n' || ch == KEY_ENTER) {
            break;
        } else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
            if (pos > 0) {
                pos--;
                move(y, x + strlen(pregunta) + 2 + pos);
                addch(' ');
                move(y, x + strlen(pregunta) + 2 + pos);
                buffer[pos] = '\0';
                refresh();
            }
        } else if (isprint(ch) && pos < maxLen) {
            buffer[pos] = ch;
            mvaddch(y, x + strlen(pregunta) + 2 + pos, ch);
            pos++;
            refresh();
        }
    }

    buffer[pos] = '\0';
    if (strlen(buffer) == 0) {
        free(buffer);
        return NULL;
    }
    return buffer;
}

int *leerInt(int y, int x, int maxLen, char *pregunta, int *codigoError) {
    if (codigoError) *codigoError = 0;

    mvprintw(y, x, "%s  ", pregunta);
    refresh();

    char buffer[maxLen + 1];
    memset(buffer, 0, maxLen + 1);
    echo();

    int ch = getch();
    if (ch == 27) {
        noecho();
        if (codigoError) *codigoError = LEERINT_ESC;
        return NULL;
    }

    ungetch(ch);

    mvgetnstr(y, x + (int)strlen(pregunta) + 2, buffer, maxLen);
    noecho();

    if (strlen(buffer) == 0) {
        if (codigoError) *codigoError = LEERINT_EMPTY;
        return NULL;
    }

    int i = 0;
    if (buffer[0] == '-') i++;
    for (; buffer[i] != '\0'; i++) {
        if (!isdigit((unsigned char)buffer[i])) {
            mvprintw(y + 1, x, "Entrada no válida: solo números.");
            refresh();
            if (codigoError) *codigoError = LEERINT_ERROR;
            return NULL;
        }
    }

    char *endptr;
    long numLong = strtol(buffer, &endptr, 10);
    if (*endptr != '\0' || numLong > INT_MAX || numLong < INT_MIN) {
        mvprintw(y + 1, x, "Error: número fuera de rango.");
        refresh();
        if (codigoError) *codigoError = LEERINT_ERROR;
        return NULL;
    }

    int *num = (int *) malloc(sizeof(int));
    if (!num) {
        mvprintw(y + 1, x, "Error al asignar memoria.");
        refresh();
        if (codigoError) *codigoError = LEERINT_ERROR;
        return NULL;
    }

    *num = (int) numLong;
    return num;
}

float *leerFloat(int y, int x, int maxLen, char *pregunta) {
    mvprintw(y, x, "%s  ", pregunta);
    if (maxLen <= 0) {
        mvprintw(y + 1, x, "Error: Longitud máxima inválida.");
        refresh();
        return NULL;
    }

    char buffer[maxLen + 1];
    memset(buffer, 0, maxLen + 1);
    echo();
    mvgetnstr(y, x + strlen(pregunta) + 2, buffer, maxLen);
    noecho();

    if (strlen(buffer) == 0) {
        return NULL;
    }

    int i = 0, dotCount = 0;
    if (buffer[0] == '-') {
        i++;
    }

    for (; buffer[i] != '\0'; i++) {
        if (buffer[i] == '.') {
            dotCount++;
            if (dotCount > 1) {
                mvprintw(y + 1, x, "Error: Número no válido.");
                refresh();
                return NULL;
            }
        } else if (!isdigit((unsigned char)buffer[i])) {
            mvprintw(y + 1, x, "Error: Solo números válidos.");
            refresh();
            return NULL;
        }
    }

    char *endptr;
    float numFloat = strtof(buffer, &endptr);
    if (*endptr != '\0') {
        mvprintw(y + 1, x, "Error: Conversión inválida.");
        refresh();
        return NULL;
    }

    float *num = (float *) malloc(sizeof(float));
    if (!num) {
        mvprintw(y + 1, x, "Error: No se pudo asignar memoria.");
        refresh();
        return NULL;
    }

    *num = numFloat;
    return num;
}

int leerIntSeguro(int y, int x, int maxLen, char *pregunta) {
    int *valor = NULL;
    int codigoError = 0;

    do {
        move(y + 1, x);
        clrtoeol();
        refresh();

        valor = leerInt(y, x, maxLen, pregunta, &codigoError);

        if (valor == NULL) {
            if (codigoError == LEERINT_ESC) {
                return -1;
            }
        }
    } while (valor == NULL);

    int resultado = *valor;
    free(valor);
    return resultado;
}

float leerFloatSeguro(int y, int x, int maxLen, char *pregunta) {
    float *valor = NULL;
    do {
        valor = leerFloat(y, x, maxLen, pregunta);
        if (valor == NULL) {
            mvprintw(y + 1, x, "X Entrada invalida. Intentalo de nuevo.");
            getch();
            refresh();
            mvprintw(y + 1, 0,
                     "                                                                                                                                                        ");
        }
    } while (valor == NULL);

    float resultado = *valor;
    free(valor);
    return resultado;
}


char *leerStringSeguro(int y, int x, int maxLen, char *pregunta) {
    char *valor = NULL;
    do {
        valor = leerString(y, x, maxLen, pregunta);
        if (valor == NULL) {
            mvprintw(y + 1, x, "Entrada inválida o cancelada con (ESC). Presione ESC de nuevo.");
            refresh();
            int ch = getch();
            if (ch == 27) return NULL;

            move(y + 1, x);
            clrtoeol();
            mvprintw(y + 1, 0,
                     "                                                                                                                                                        ");
        }
    } while (valor == NULL);

    return valor;
}

void imprimirTextoMultilinea(int fila, int columna, const char *texto, int anchoMaximo) {
    int len = strlen(texto);
    int inicio = 0;

    while (inicio < len) {
        char buffer[anchoMaximo + 1];
        int fin = inicio + anchoMaximo;

        if (fin >= len) fin = len;
        else {
            while (fin > inicio && texto[fin] != ' ') fin--;
            if (fin == inicio) fin = inicio + anchoMaximo;
        }

        int largoLinea = fin - inicio;
        strncpy(buffer, texto + inicio, largoLinea);
        buffer[largoLinea] = '\0';

        mvprintw(fila++, columna, "%s", buffer);
        while (texto[fin] == ' ') fin++;
        inicio = fin;
    }
}

void imprimirTextoMultilineaArchivo(FILE *archivo, const char *texto, int anchoMaximo) {
    if (!texto || !archivo) return;

    int len = strlen(texto);
    int inicio = 0;

    while (inicio < len) {
        int longitudLinea = (len - inicio > anchoMaximo) ? anchoMaximo : len - inicio;
        char linea[anchoMaximo + 1];
        strncpy(linea, texto + inicio, longitudLinea);
        linea[longitudLinea] = '\0';
        fprintf(archivo, "%s\n", linea);
        inicio += longitudLinea;
    }
}

int arrayPiezasSize(ArrayPiezas *list) {
    int tamanno = 0;
    for (int i = 0; i < list->tamanno; i++) {
        if (list->datos[i] != NULL) {
            tamanno++;
        }
    }
    return tamanno;
}

const char *tipoCombustibleToStr(TipoCombustible tipo) {
    switch (tipo) {
        case GASOLINA: return "Gasolina";
        case DIESEL: return "Diesel";
        case HIBRIDO: return "Híbrido";
        default: return "Desconocido";
    }
}

void mostrarUsuario(Usuario usr) {
    mvprintw(10, 10, "ID Usuario: %d\n", usr.id_usuario);
    mvprintw(10, 11, "Folio Usuario: %s\n", usr.folio);
    mvprintw(10, 12, "Activo?: %d", usr.activo);
    mvprintw(10, 13, "Nombre: %s\n", usr.nombreUsuario);
    mvprintw(10, 14, "Apellido: %s\n", usr.apellido);
    mvprintw(10, 15, "Celular: %lld\n", usr.celular);
    mvprintw(10, 16, "Email: %s\n", usr.email);
    mvprintw(10, 17, "Contacto: %s\n", usr.contacto);
}

char *obtenerNombreArchivo(const char *textoInicial) {
    char fecha[50];
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(fecha, sizeof(fecha), "%Y-%m-%d_%H-%M-%S", tm_info);

    char *nombreArchivo = malloc(200);
    if (nombreArchivo == NULL) {
        perror("Error al reservar memoria");
        exit(EXIT_FAILURE);
    }

    strcpy(nombreArchivo, textoInicial);
    strcat(nombreArchivo, fecha);
    strcat(nombreArchivo, ".txt");

    return nombreArchivo;
}

void cleanScreen() {
    printf("\033[2J\033[H");
}
