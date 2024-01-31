#ifndef __OUT_SENDER__
#define __OUT_SENDER__

#include "config.h"
#include "Arduino.h"

class OutSender {
    public:
        //send the value of the valve to be set
        virtual void sendActValveOpen(int value) = 0;
};

#endif