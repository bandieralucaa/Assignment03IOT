#include "Valve.h"

#define AMOUNT_MOVE 30

Valve::Valve(int pin, bool isActOpen, OutSender* toSerial, Lcd* myLcd, OpeningDetection* od) {
    this->motor.attach(pin);
    if (isActOpen) {
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

int Valve::getActPos() {
    return this->currentPos;
}

void Valve::init() {
    this->motor.write(this->settedPos);
}

void Valve::tick() {
    int toSetPos = od->getOpeningToSet();
    this->settedPos = map(toSetPos, 0, MAX_POT_VALUE, MIN_ANGLE, MAX_ANGLE);
    int tmpDir = this->currentPos - this->settedPos;

    #ifdef SERVO_MOTOR_DEBUG
    Serial.print("READ " + ((String)this->settedPos) + "\n");
    Serial.print("NOW " + ((String)this->currentPos) + "\n");
    Serial.print("ELAPSED "  + ((String)tmpDir) + "\n");
    #endif

    if ((tmpDir < (-1 * (AMOUNT_MOVE))) || (tmpDir > (1 * (AMOUNT_MOVE)))) { //servo couldn't reach final position: move it of AMOUNT_MOVE degrees
    
        if(tmpDir < 0) {
            this->currentPos += 1 * AMOUNT_MOVE;
        } else {
            this->currentPos += -1 * AMOUNT_MOVE;
        }
    
    } else {
        this->currentPos = this->settedPos; //servo can reach final position
    }
    
    this->motor.write(this->currentPos); //apply new computed angle

    int advise = map(this->currentPos, MIN_ANGLE, MAX_ANGLE, 0, MAX_POT_VALUE);

    #ifdef SERVO_MOTOR_DEBUG
    Serial.print("AFTER " + ((String)this->currentPos) + "\n");
    #endif

    this->toSerial->sendActValveOpen(advise);
    this->myLcd->updateActValv(advise);

}