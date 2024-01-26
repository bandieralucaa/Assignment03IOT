#ifndef __VALVE_OPENING_MANAGEMENT__
#define __VALVE_OPENING_MANAGEMENT__

#include "./task/Task.h"
#include "./components/valveOpener/OpeningDetection.h"
#include "./components/valveOpener/Potentiometer.h"
#include "./components/ioserial/InReceiver.h"
#include "./ControllerSchedulerObserver.h"

class ValveOpeningManagement : public Task, public OpeningDetection {
    public:
        ValveOpeningManagement(Potentiometer* p, InReceiver* receiver);

        int getOpeningToSet();

        void init();
        void tick();

    private:
        int lastPotMod;
        String datePotMod;
        Potentiometer* pot;
        InReceiver* receiver;
        ControllerSchedulerObserver* controller;
};

#endif
