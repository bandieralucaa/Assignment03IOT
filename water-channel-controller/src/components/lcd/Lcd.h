#ifndef __LCD__
#define __LCD__

#include "Arduino.h"

#define MAX_VALUE_PERCENTAGE_BAR 100

class Lcd {
    public:
        virtual void updateState() = 0;
        virtual void updateACtValv() = 0;
        virtual void printOnLcd() = 0;
};

#endif

