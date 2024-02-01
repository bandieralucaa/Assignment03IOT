#include "StateButtonInterupt.h"

StateName actState = AUTOMATIC_STATE;
ControllerSchedulerObserver* myObs;

    unsigned long lastPressed = millis();
    unsigned long debouncingTime = BTN_DEBOUNCING_TIME;

void pressedButton() {
    unsigned long tmp = millis();
    
    #ifdef BUTTON_DEBUG
    delay(100);
    Serial.print("BUTTON");
    delay(100);
    Serial.println(tmp);
    delay(100);
    #endif
    
    if ((tmp - lastPressed) > debouncingTime ) {
        StateName newState = (actState == AUTOMATIC_STATE) ? MANUAL_STATE : AUTOMATIC_STATE;
        actState = newState;
        lastPressed = tmp;
        myObs->setNewState(actState);
    }
    
}

StateButtonInterupt::StateButtonInterupt(int pin, ControllerSchedulerObserver* obs) {
    pinMode(pin,INPUT);
    myObs = obs;
    attachInterrupt(digitalPinToInterrupt(pin),pressedButton, RISING);
}



StateName StateButtonInterupt::buttonState(){
    return actState;
}