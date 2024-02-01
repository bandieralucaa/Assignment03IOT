#include "Cooldown.h"

Cooldown::Cooldown(unsigned long amountTime) {
    this->amountTime = amountTime;
}

void Cooldown::init() {
    this->t.start();
}

bool Cooldown::isOver(){
    return this->t.read() > amountTime;
}

void Cooldown::pause(){
    this->t.pause();
}

void Cooldown::resume(){
    this->t.resume();
}

void Cooldown::reset(){
    this->t.stop();
    this->t.start();
} // reset the timer and start it again

int Cooldown::percentageComplete(){
    return this->isOver() ? 100 : ((int) (((this->t.read()*1.0)/(this->amountTime*1.0))*100.0));
}

void Cooldown::format(unsigned long newClock){
    this->amountTime = newClock;
    this->reset();
}
