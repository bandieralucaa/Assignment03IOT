#ifndef __CO__
#define __CO__

#include "CV.h"
#include "CM.h"
#include "config.h"

class ControllerObserver : public CV, public CM {
  public:
    // void setMeasurement(double measure);
    // void setConnection(NetworkState newState);
    // void setFreq(double newFreq);
    // virtual bool isBoardConnected() = 0;
};

#endif