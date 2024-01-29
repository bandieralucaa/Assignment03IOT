#include "ManualState.h"


ManualState::ManualState(Button* button, Lcd* myLcd) {
    this->button = button;
    this->myLcd = myLcd;
}

void ManualState::init() {
    #ifdef STATE_CHANGE_DEBUG
    Serial.println("DEBUG: ManualState");
    #endif
    digitalWrite(5, LOW);
    // this->blink->start();
    // this->myGate->start();

    // this->myGate->close();
    // this->blink->canBlink(false);
    // this->blink->switchOn();
}

StateName ManualState::changeState() {
    // Serial.print(this->button->isPressed());
    if (this->button->isPressed()) {
        myLcd->updateState(AUTOMATIC_STATE);
        return AUTOMATIC_STATE;
    } else {
        return NONE;
    }
}