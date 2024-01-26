#ifndef __S_M__
#define __S_M__

#include "config.h"

#include "./task/Task.h"
#include "OutSender.h"
#include "InReceiver.h"

#include "MsgService.h"

#include "./ControllerSchedulerObserver.h"

#include <Arduino.h>


class SerialManager: public Task, public OutSender, public InReceiver{
public:
    SerialManager(ControllerSchedulerObserver* ob);

    void init();
    void tick();

    bool updateAndCheckTime(int millis) { //ridefinito in quanto SerialManager non necessita di essere sospeso

        bool res = false;
        this->millis += millis;
        if (this->millis >= this->period){
            res = true;
            this->millis = 0;
        }
        return res;
    };

    void sendActValveOpen(int value);

    int getParsedValveOpening();
    int getHourModApertura();


private:
    String byStatusToString();
    int parsedAperturaValvola;
    int oraSample;    
    ControllerSchedulerObserver* ob;

    int actValvOpening;
    
    void executeCommands(String comm);
    void executeCommandByGui(String comm, String value);
};


#endif