#ifndef __STATE__
#define __STATE__

#include "config.h"

enum StateName {
    NONE = -1,
    AUTOMATIC_STATE,
    MANUAL_STATE
};

class State {
    public:
        virtual void init() = 0;
        virtual StateName changeState() = 0;
};

#endif