#ifndef __BUTTON__
#define __BUTTON__

#include "config.h"

class Button {
    public:
        // Return the current state of the button
        virtual StateName buttonState() = 0;
};

#endif