
#include "PotentiometerImpl.h"

PotentiometerImpl::PotentiometerImpl(int pin){
    // pinMode(pin, INPUT);
    this->myPin = pin;
}


int PotentiometerImpl::getAngleToSet(){
    //int tmp = ((int)(((analogRead(this->myPin) * 1.0) / (MAX_VALUE * 1.0)) * ((MAX_ANGLE_SERVO)*(1.0))));
    //tmp = (tmp > 100) ? MAX_ANGLE_SERVO : tmp;
    return map(analogRead(this->myPin), 0, MAX_VALUE, MIN_ANGLE_SERVO, MAX_ANGLE_SERVO);
}
