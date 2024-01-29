#ifndef __S_M__
#define __S_M__

#include "config.h"

#include "./Task.h"
#include "OutSender.h"
#include "MsgService.h"
#include "../valveOpener/ExternalSources.h"

#include <Arduino.h>


class SerialManager: public Task, public OutSender{
public:
    SerialManager(ExternalSources* obs);

    void init();
    void tick();

    // bool updateAndCheckTime(int millis) { //ridefinito in quanto SerialManager non necessita di essere sospeso

    //     bool res = false;
    //     this->millis += millis;
    //     if (this->millis >= this->period){
    //         res = true;
    //         this->millis = 0;
    //     }
    //     return res;
    // };

    void sendActValveOpen(int value);


private:
    String byStatusToString();
    int parsedAperturaValvola;

    ExternalSources* vom;

    int actValvOpening;
    
    void executeCommands(String comm);
    void executeCommandByGui(String comm, String value);
};


#endif