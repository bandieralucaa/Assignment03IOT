#ifndef __EXTERNAL_SOURCES__
#define __EXTERNAL_SOURCES__

#include "Arduino.h"

class ExternalSources {
    public:
        virtual void setValveOpBySerial() = 0;
};

#endif
