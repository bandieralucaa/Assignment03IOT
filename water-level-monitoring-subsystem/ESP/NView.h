#ifndef __NVIEW__
#define __NVIEW__

#include "config.h"
#include "ControllerObserver.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

class NView {
    public:
      NView();
      void setObserver(ControllerObserver* newObserver);

      void keepAliveFunctions();

      bool isConnected();
      void reconnect();
      void sendSample(double sample);

    private:
      bool isPrevConn = false;
      //void modifyFreq(String newVal);
};



#endif 