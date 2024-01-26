#include "AutomaticState.h"


AutomaticState::AutomaticState(Button* button, Lcd* myLcd) {
    this->button = button;
    this->myLcd = myLcd;
}

void AutomaticState::init() {
    #ifdef STATE_CHANGE_DEBUG
    Serial.println("AutomaticState");
    #endif

    // this->blink->start();
    // this->myGate->start();

    // this->myGate->close();
    // this->blink->canBlink(false);
    // this->blink->switchOn();
}

StateName AutomaticState::changeState() {
    if (this->button->isPressed()) {
        myLcd->updateState(MANUAL_STATE);
        return MANUAL_STATE;
    } else {
        return NONE;
    }
}