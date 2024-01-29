#ifndef __POTENTIOMETER_IMPL__
#define __POTENTIOMETER_IMPL__


#include "Potentiometer.h"
#include "Arduino.h"

#define MAX_VALUE 1000 //sarebbe 1023 ma non lo facciamo arrivare fino a fine corsa

class PotentiometerImpl : public Potentiometer {
    public:
        PotentiometerImpl(int pin);
        int getPercentageValue();
    private:
        int myPin;
};

#endif