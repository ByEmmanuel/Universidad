//
// Created by byemmanuel on 8/19/26.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(void) {

    int16_t i = 1;
    int8_t* p = (int8_t*)&i;

    p[0] == 1 ? printf("Little Endian \n") : printf("Big Endian \n");
    printf("%p \n", (void*) p);
    printf("%d \n", p[1]);
    return 0;
}