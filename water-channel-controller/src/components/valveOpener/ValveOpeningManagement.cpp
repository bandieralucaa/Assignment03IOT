#include "ValveOpeningManagement.h"

ValveOpeningManagement::ValveOpeningManagement(Potentiometer* p) {
    this->pot = p;
    this->lastParsedValue = 50;
    this->period = VALVE_OPENER_PERIOD;

}

int ValveOpeningManagement::getOpeningToSet() {
    return this->lastParsedValue;

    // if (this->obs->getActState() == AUTOMATIC_STATE) {
    //     //return this->receiver->getParsedValveOpening();
    // } else {
    //     // if (strcmp(this->datePotMod, this->receiver->getHourModApertura()) > 1) { //TODO: RISOLVERE PROBLEMA CASTING
    //     //     return this->lastPotMod;
    //     // } else {
    //        //return this->receiver->getParsedValveOpening();
    //     // }
    // }
    // // unsigned long a = millis();
}

void ValveOpeningManagement::init() {
    
}


void ValveOpeningManagement::setValveOpBySerial(int newVal) {
    this->lastParsedValue = newVal;
}

void ValveOpeningManagement::tick() {
    if (this->obs->getActState() == MANUAL_STATE) {
        int tmp = this->pot->getPercentageValue();
        if (tmp != this->lastPotVal) {
            this->lastParsedValue = tmp;
        }
    }
}
