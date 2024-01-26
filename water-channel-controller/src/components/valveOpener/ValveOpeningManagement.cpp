#include "ValveOpeningManagement.h"

ValveOpeningManagement::ValveOpeningManagement(Potentiometer* p, InReceiver* receiver) {
    this->pot = p;
    this->receiver = receiver;
    this->lastPotMod = 0;

}

int ValveOpeningManagement::getOpeningToSet() {
    if (this->controller->getActState() == AUTOMATIC_STATE) {
        return this->receiver->getParsedValveOpening();
    } else {
        // if (strcmp(this->datePotMod, this->receiver->getHourModApertura()) > 1) { //TODO: RISOLVERE PROBLEMA CASTING
        //     return this->lastPotMod;
        // } else {
            return this->receiver->getParsedValveOpening();
        // }
    }
    // unsigned long a = millis();
}

void ValveOpeningManagement::init() {
}

void ValveOpeningManagement::tick() {
    if (this->controller->getActState() == MANUAL_STATE) {
        int tmp = this->pot->getPercentageValue();
        if (tmp != this->lastPotMod) {
            this->lastPotMod = tmp;
            this->datePotMod = "0"; //TODO: prendere data con c++
        }
    }
}