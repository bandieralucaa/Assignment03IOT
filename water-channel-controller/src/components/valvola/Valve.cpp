#include "Valve.h"

#define AMOUNT_MOVE 30

Valve::Valve(int pin, bool isActOpen, OutSender* toSerial, Lcd* myLcd, OpeningDetection* od) {
    this->motor.attach(pin);
    if(isActOpen){
        this->currentPos = MAX_ANGLE;
        this->settedPos = MAX_ANGLE;
    } else {
        this->currentPos = MIN_ANGLE;
        this->settedPos = MIN_ANGLE;
    }
    this->toSerial = toSerial;
    this->myLcd = myLcd;
    this->od = od;
    this->period = SERVO_MOTOR_PERIOD;
}

void Valve::setPos(int newPos) {
    this->settedPos = newPos;
}

int Valve::getActPos() {
    return this->currentPos;
}

void Valve::init() {
    this->motor.write(this->settedPos);
}

void Valve::tick() {
    int toSetPos = od->getOpeningToSet();
    int tmpDir = this->currentPos - (((toSetPos*1.0) /  (100 * 1.0)) * (1.0 * MAX_ANGLE) );

    if ((tmpDir < (-1 * (AMOUNT_MOVE))) || (tmpDir > (1 * (AMOUNT_MOVE)))){
    
        if(tmpDir < 0){
            this->currentPos += 1 * AMOUNT_MOVE;
        } else {
            this->currentPos += -1 * AMOUNT_MOVE;
        }
    
    } else {
        this->currentPos = this->settedPos; //puoi raggiungere la posizione finale
    }
    
    this->motor.write(this->currentPos); //applica modifica al servo
    this->toSerial->sendActValveOpen(this->currentPos);
    this->myLcd->updateActValv(this->currentPos);
}