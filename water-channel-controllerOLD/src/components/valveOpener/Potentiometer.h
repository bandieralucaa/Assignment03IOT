#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

#include "Arduino.h"

class Potentiometer {
    public:
        virtual int getPercentageValue() = 0;
};

#endif