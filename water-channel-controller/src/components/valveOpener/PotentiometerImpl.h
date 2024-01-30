#ifndef __POTENTIOMETER_IMPL__
#define __POTENTIOMETER_IMPL__

#include "config.h"
#include "Potentiometer.h"
#include "Arduino.h"

#define MAX_VALUE 1023 //sarebbe 1023 ma non lo facciamo arrivare fino a fine corsa

class PotentiometerImpl : public Potentiometer {
    public:
        PotentiometerImpl(int pin);
        int getAngleToSet();
    private:
        int myPin;
};

#endif