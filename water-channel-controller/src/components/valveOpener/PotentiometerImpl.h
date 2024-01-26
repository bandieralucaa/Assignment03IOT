#ifndef __POTENTIOMETER_IMPL__
#define __POTENTIOMETER_IMPL__


#include "Potentiometer.h"
#include "Arduino.h"

#define MAX_VALUE 1023

class PotentiometerImpl : public Potentiometer {
    public:
        PotentiometerImpl(int pin);
        int getPercentageValue();
    private:
        int myPin;
};

#endif