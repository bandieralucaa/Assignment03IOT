
#include "PotentiometerImpl.h"

PotentiometerImpl::PotentiometerImpl(int pin){
    this->myPin = pin;
}


int PotentiometerImpl::getValue(){
    return analogRead(this->myPin);
}
