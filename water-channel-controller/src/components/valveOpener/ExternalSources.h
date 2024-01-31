#ifndef __EXTERNAL_SOURCES__
#define __EXTERNAL_SOURCES__

#include "Arduino.h"

class ExternalSources {
    public:
        //set the value of the valve by the serial
        virtual void setValveOpBySerial(int newVal) = 0;
};

#endif
