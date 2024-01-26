#ifndef __S_M__
#define __S_M__

#include "config.h"

#include "./task/Task.h"
#include "OutSender.h"
#include "InReceiver.h"

#include "MsgService.h"

#include <Arduino.h>


class SerialManager: public Task, public OutSender, public InReceiver{
public:
    SerialManager();

    void init();
    void tick();

    bool updateAndCheckTime(int millis){
        bool res = false;
        this->millis += millis;
        if (this->millis >= this->period){
            res = true;
            this->millis = 0;
        }
        return res;
    };

    void sendActValveOpen(int value);

    void getParsedValveOpening();
    void getHourModApertura();


private:
    int parsedAperturaValvola;
    String oraSample;    
    
    void executeCommands(String comm);
    void executeCommandByGui(String comm, String value);
};


#endif