
#include "PotentiometerImpl.h"

PotentiometerImpl::PotentiometerImpl(int pin){
    this->myPin = pin;
}


int PotentiometerImpl::getPercentageValue(){
    return (int) ((analogRead(this->myPin) * 1.0) / (MAX_VALUE * 1.0));
}
