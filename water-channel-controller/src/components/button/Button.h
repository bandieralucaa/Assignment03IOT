#ifndef __BUTTON__
#define __BUTTON__

#include "config.h"

class Button {
    public:
        virtual StateName buttonState() = 0;
};

#endif