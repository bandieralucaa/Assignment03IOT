#include "StateButton.h"

StateButton::StateButton(int pin) {
    //pinMode(pin, INPUT);
    pinMode(pin, INPUT);
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
    // Serial.print(this->pin);
    // Serial.print("CC");
    this->pushed = digitalRead(this->pin) == HIGH ? true : false;
}