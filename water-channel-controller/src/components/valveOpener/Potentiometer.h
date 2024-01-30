#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

#include "Arduino.h"

class Potentiometer {
    public:
        virtual int getValue() = 0;
};

#endif