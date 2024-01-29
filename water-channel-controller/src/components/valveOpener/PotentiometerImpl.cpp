
#include "PotentiometerImpl.h"

PotentiometerImpl::PotentiometerImpl(int pin){
    // pinMode(pin, INPUT);
    this->myPin = pin;
}


int PotentiometerImpl::getPercentageValue(){
    int tmp = (((analogRead(this->myPin) * 1.0) / (MAX_VALUE * 1.0)) * 100);
    tmp = (tmp > 100) ? 100 : tmp;
    return tmp;//;
}
