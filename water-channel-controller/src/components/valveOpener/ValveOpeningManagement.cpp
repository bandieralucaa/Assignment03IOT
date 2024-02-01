#include "ValveOpeningManagement.h"

ValveOpeningManagement::ValveOpeningManagement(Potentiometer* p) {
    this->pot = p;
    this->lastParsedValue = 50;
    this->lastPotVal = 0;
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
    this->lastParsedValue = newVal;
    this->isSerialLastInfo = true;
}

bool ValveOpeningManagement::isOutOfTollerance(int act) {
    return abs(this->lastPotVal - act) > TOLL_VAL;
}

void ValveOpeningManagement::tick() {
    if (this->obs->getActState() == MANUAL_STATE) {
        int tmp = this->pot->getValue();
        if (isOutOfTollerance(tmp)) {
            this->lastPotVal = tmp;
            this->isSerialLastInfo = false;
        }
    }
}
