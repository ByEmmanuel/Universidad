#include <Arduino.h>
#include "Blink.h"

void setup() {
    initBlink();
}

void loop() {
    prender_led(13);
}