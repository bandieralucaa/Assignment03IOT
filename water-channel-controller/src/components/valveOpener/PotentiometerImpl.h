#ifndef __POTENTIOMETER_IMPL__
#define __POTENTIOMETER_IMPL__

#include "config.h"
#include "Potentiometer.h"
#include "Arduino.h"

#define MAX_VALUE MAX_POT_VALUE

class PotentiometerImpl : public Potentiometer {
    public:
        PotentiometerImpl(int pin);
        int getValue();
    private:
        int myPin;
};

#endif