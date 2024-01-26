#include "ManualState.h"


ManualState::ManualState(Button* button, Lcd* myLcd) {
    this->button = button;
    this->myLcd = myLcd;
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
        myLcd->updateState(AUTOMATIC_STATE);
        return AUTOMATIC_STATE;
    } else {
        return NONE;
    }
}