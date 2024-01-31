#include "Led.h"

Led::Led(int pin) {
    #ifdef DEBUG_NOPANIC
    Serial.println("LED");
    #endif
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Led::switchOn() {
  #ifdef DEBUG_NOPANIC
  Serial.println("LED");
  #endif
  digitalWrite(pin, HIGH);
}

void Led::switchOff() {
  #ifdef DEBUG_NOPANIC
    Serial.println("LED");
    #endif
    digitalWrite(pin, LOW);
}