#ifndef __CM__
#define __CM__

#include "config.h"

class CM {
public:
    virtual void setMeasurement(double measure) = 0;
    
    virtual void setConnection(NetworkState newState) = 0;

    virtual bool isBoardConnected() = 0;
};

#endif