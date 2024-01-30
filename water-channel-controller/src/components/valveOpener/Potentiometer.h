#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

#include "Arduino.h"

class Potentiometer {
    public:
        virtual int getAngleToSet() = 0;
};

#endif