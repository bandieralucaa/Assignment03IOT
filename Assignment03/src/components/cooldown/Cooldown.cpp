#include "Cooldown.h"

Cooldown::Cooldown(unsigned long amountTime) {
    this->amountTime = amountTime;
}

void Cooldown::init() {
    this->timer.init();
}

bool Cooldown::isOver() {
    return this->timer.read() > amountTime;
}

void Cooldown::pause() {
    this->timer.pause();
}

void Cooldown::resume() {
    this->timer.stop();
    this->timer.start();
}

void Cooldown::reset() {
    this->timer.reset();
}

int Cooldown::percentageComplete() {
    return this->isOver() ? 100 : ((int) (((this->timer.read() * 1.0) / (this->amountTime * 1.0)) * 100));
}

void Cooldown::format(unsigned long newClock) {
    this->amountTime = newClock;
    this->reset();
}