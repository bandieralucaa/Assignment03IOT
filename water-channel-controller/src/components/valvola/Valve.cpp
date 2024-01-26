#include "Valve.h"

#define AMOUNT_MOVE 30

Valve::Valve(int pin, bool isActOpen) {
    this->motor.attach(pin);
}

void Valve::setPos() {
    this->motor.write(this->delta);
}

int Valve::getActPos() {
    return this->delta;
}

void Valve::init() {
    this->delta = MIN_ANGLE;
    this->motor.write(this->delta);
}

void Valve::tick() {
    //muovere valvola
}