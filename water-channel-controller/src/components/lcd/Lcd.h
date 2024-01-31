#ifndef __LCD__
#define __LCD__

#include "Arduino.h"

#define MAX_VALUE_PERCENTAGE_BAR 100

class Lcd {
    public:
        //update the lcd with the new state
        virtual void updateState(StateName newState) = 0;

        //update the lcd with the new value of the valve
        virtual void updateActValv(int newValvOp) = 0;
};

#endif

