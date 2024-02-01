#ifndef __CONTROLLER__
#define __CONTROLLER__

#include "config.h"
#include <Arduino.h>

#include "ControllerObserver.h"

#include "Led.h"
#include "Sonar.h"
#include "NView.h"

#include "MeasurementTask.h"
#include "NetworkTask.h"


#include <Arduino.h>

class Controller : public ControllerObserver {
  public:
    Controller();
    /** see CM  */
    void setMeasurement(double measure);
    void setConnection(NetworkState newState);
    bool isBoardConnected();
    void reconnectBoard();
    /** see CV */
    void setFreq(unsigned long newFreq);

    /** method that inherit "setup" and "loop" of .ino class */
    void init();
    void tick();
  
  private:
    // /* manage the request of reconnection started by a task */
    double actMeasure;
    NetworkState actNS;
    unsigned long actFreq;
    unsigned long lastTime;

    NView* view;

    Led* okLed;
    Led* errLed;
    Sonar* sonar;

};

static MeasurementTask* taskmes;
static NetworkTask* tasknet;

#endif 