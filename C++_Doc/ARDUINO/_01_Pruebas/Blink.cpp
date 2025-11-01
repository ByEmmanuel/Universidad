#include <Arduino.h>
#include "Blink.h"

void initBlink() {
    pinMode(13, OUTPUT);
}

void prender_led(int pin) {
    digitalWrite(pin, HIGH);
    delay(1000);
    digitalWrite(pin, LOW);
    delay(1000);
}