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
    //this->settedPos = newPos;
    this->settedPos = map(newPos, 0, 1024, 0, 180);
}

int Valve::getActPos() {
    return this->currentPos;
}

void Valve::init() {
    this->motor.write(this->settedPos);
}

void Valve::tick() {
    int toSetPos = od->getOpeningToSet();
    this->settedPos = MIN_ANGLE + ((int)(((toSetPos) / 100.0) * ((MAX_ANGLE - MIN_ANGLE)*1.0)));
    int tmpDir = this->currentPos - this->settedPos;

    #ifdef SERVO_MOTOR_DEBUG
    Serial.print("READ " + ((String)this->settedPos) + "\n");
    Serial.print("NOW " + ((String)this->currentPos) + "\n");
    Serial.print("ELAPSED "  + ((String)tmpDir) + "\n");
    #endif

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

    int advise = ((int) ( ( ((this->currentPos - MIN_ANGLE)*1.0) / ((MAX_ANGLE - MIN_ANGLE)*1.0) ) * 100 ));

    #ifdef SERVO_MOTOR_DEBUG
    Serial.print("AFTER " + ((String)this->currentPos) + "\n");
    #endif

    this->toSerial->sendActValveOpen(advise);
    this->myLcd->updateActValv(advise);

}