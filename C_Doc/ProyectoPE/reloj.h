//
// Created by Jesus Emmanuel Garcia on 5/14/25.
//

#ifndef RELOJ_H
#define RELOJ_H
#include <curses.h>

// Estructura para pasar datos al hilo del reloj
typedef struct {
    WINDOW *win;
    int running;
} ClockData;

char *get_time_str();
void *clock_thread(void *arg);

#endif //RELOJ_H
