//Reloj
#ifndef RELOJ_H
#define RELOJ_H
#include <curses.h>


typedef struct {
    WINDOW *win;
    int running;
} ClockData;

char *get_time_str();

void *clock_thread(void *arg);

#endif
