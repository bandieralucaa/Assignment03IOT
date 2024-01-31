#ifndef __CM__
#define __CM__

#include "config.h"

class CM {
public:
    //Help Measurement to upload last measure that he parsed to the Controller
    virtual void setMeasurement(double measure) = 0;
    
    //Help NetworkTask to advise all system if there is connection or not
    virtual void setConnection(NetworkState newState) = 0;

    //Help tasks to check if there is connection
    virtual bool isBoardConnected() = 0;

    //Help tasks to launch the reconnection code
    virtual void reconnectBoard() = 0;
};

#endif