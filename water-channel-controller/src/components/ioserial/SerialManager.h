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

    void sendActValveOpen(int value);


    private:
        String byStatusToString();
        int parsedAperturaValvola;

        ExternalSources* vom;

        //this value is stored in 0-100 scale
        int actValvOpening;
        
        void executeCommands(String comm);
        void executeCommandByGui(char c, String value);

        StateName lastStateSend = NONE;
        int lastValveSend = -1;

};


#endif