#ifndef __OUT_SENDER__
#define __OUT_SENDER__

#include "config.h"
#include "Arduino.h"

class OutSender {
    public:
        virtual void sendActValveOpen(int value) = 0;
};

#endif