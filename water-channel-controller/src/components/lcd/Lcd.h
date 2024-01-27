#ifndef __LCD__
#define __LCD__

#include "Arduino.h"
#include "./state/State.h"

#define MAX_VALUE_PERCENTAGE_BAR 100

class Lcd {
    public:
        virtual void updateState(StateName newState) = 0;
        virtual void updateActValv(int newValvOp) = 0;
};

#endif

