#ifndef __VALVE_OPENING_MANAGEMENT__
#define __VALVE_OPENING_MANAGEMENT__

#include <Arduino.h>
#include "Task.h"
#include "./components/valveOpener/OpeningDetection.h"
#include "./components/valveOpener/Potentiometer.h"
#include "./components/valveOpener/ExternalSources.h"

#include "./ControllerSchedulerObserver.h"


class ValveOpeningManagement : public Task, public OpeningDetection, public ExternalSources {
    public:
        ValveOpeningManagement(Potentiometer* p);

        int getOpeningToSet();
        
        void setValveOpBySerial(int newVal);

        void init();
        void tick();

    private:
        //check if the value is out of the tollerance
        bool isOutOfTollerance(int value);
        Potentiometer* pot;
        int lastPotVal;
        int lastParsedValue;

        bool isSerialLastInfo;
};

#endif
