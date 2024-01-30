#include "ValveOpeningManagement.h"

ValveOpeningManagement::ValveOpeningManagement(Potentiometer* p) {
    this->pot = p;
    this->lastParsedValue = 50;
    this->lastPotVal = -1;
    this->isSerialLastInfo = false;
    this->period = VALVE_OPENER_PERIOD;
    

}

int ValveOpeningManagement::getOpeningToSet() {
    if (this->obs->getActState() == AUTOMATIC_STATE) {
        return this->lastParsedValue;
    } else {
        return this->isSerialLastInfo ? this->lastParsedValue : this->lastPotVal;
    }
}

void ValveOpeningManagement::init() {
    
}


void ValveOpeningManagement::setValveOpBySerial(int newVal) {
    this->lastParsedValue = map(newVal, 0, 100, MIN_ANGLE_SERVO, MAX_ANGLE_SERVO);
    this->isSerialLastInfo = true;
}

void ValveOpeningManagement::tick() {
    if (this->obs->getActState() == MANUAL_STATE) {
        int tmp = this->pot->getAngleToSet();
        if (tmp != this->lastPotVal) {
            this->lastPotVal = tmp;
            this->isSerialLastInfo = false;
        }
    }
}
