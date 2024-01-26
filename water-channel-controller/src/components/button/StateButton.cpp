#include "StateButton.h"

StateButton::StateButton(int pin) {
    this->pin = pin;
    this->period = BUTTON_PERIOD;
    this->pushed = false;
}

bool StateButton::isPressed() {
    return this->pushed;

}

void StateButton::init(){
    
}

void StateButton::tick(){
    this->pushed = digitalRead(this->pin) == HIGH ? true : false;
}