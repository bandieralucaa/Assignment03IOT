#include "ManualState.h"


ManualState::ManualState(Button* button) {
    this->button = button;
}

void ManualState::init() {
    #ifdef STATE_CHANGE_DEBUG
    Serial.println("ManualState");
    #endif

    // this->blink->start();
    // this->myGate->start();

    // this->myGate->close();
    // this->blink->canBlink(false);
    // this->blink->switchOn();
}

StateName ManualState::changeState() {
    if (this->button->isPressed()) {
        return AUTOMATIC_STATE;
    } else {
        return NONE;
    }
}