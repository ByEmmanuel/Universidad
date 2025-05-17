//
// Created by Jesus Emmanuel Garcia on 5/14/25.
//

#include "reloj.h"

#include <ncurses.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <unistd.h>


char *get_time_str() {
    time_t rawtime;
    struct tm *timeinfo;
    static char buffer[9];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    return buffer;
}

// Funcion que corre en el hilo del reloj
void *clock_thread(void *arg) {
    ClockData *data = (ClockData *)arg;
    WINDOW *win = data->win;

    while (data->running) {
        wmove(win, 0, COLS - 10);
        wprintw(win, "%s", get_time_str());
        wrefresh(win);
        sleep(1);
    }

    return NULL;
}
