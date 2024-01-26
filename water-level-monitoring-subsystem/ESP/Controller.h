#ifndef __CONTROLLER__
#define __CONTROLLER__

#include "config.h"
#include <Arduino.h>
//#include <FreeRTOS.h>

#include "ControllerObserver.h"

#include "Led.h"
#include "Sonar.h"
#include "NView.h"

#include "MeasurementTask.h"
#include "NetworkTask.h"
//#include "NetworkTask.h"

#include <Arduino.h>

class Controller : public ControllerObserver {
  public:
    Controller();
    void setMeasurement(double measure);
    void setConnection(NetworkState newState);
    void setFreq(double newFreq);
    bool isBoardConnected();

    void init();
    void tick();
  
  private:

    void resumeConnection();

    double actMeasure;
    NetworkState actNS;
    double actFreq;
    

    NView* view;

    Led* okLed;
    Led* errLed;
    Sonar* sonar;

    
    //NetworkTask* tasknet;
};

static MeasurementTask* taskmes;
static NetworkTask* tasknet;

#endif 