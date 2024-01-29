#ifndef __VALVE_OPENING_MANAGEMENT__
#define __VALVE_OPENING_MANAGEMENT__

#include <Arduino.h>
#include "Task.h"
#include "./components/valveOpener/OpeningDetection.h"
#include "./components/valveOpener/Potentiometer.h"
#include "./ControllerSchedulerObserver.h"

class ValveOpeningManagement : public Task, public OpeningDetection {
    public:
        ValveOpeningManagement(Potentiometer* p);

        int getOpeningToSet();

        void init();
        void tick();

    private:
        int lastPotMod;
        String datePotMod;
        Potentiometer* pot;
        ControllerSchedulerObserver* controller;
};

#endif
