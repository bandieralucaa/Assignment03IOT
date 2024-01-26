#include "AutomaticState.h"


AutomaticState::AutomaticState(Button* button) {
    this->button = button;
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
        return MANUAL_STATE;
    } else {
        return NONE;
    }
}