#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

#include "Arduino.h"

class Potentiometer {
    public:
        //get the value of the potentiometer
        virtual int getValue() = 0;
};

#endif