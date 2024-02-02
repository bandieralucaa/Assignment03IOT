#ifndef __CONTROLLERSCHEDULER__
#define __CONTROLLERSCHEDULER__

#include "./ControllerSchedulerObserver.h"
#include "config.h"
#include "./Task.h"


#include "./components/button/StateButtonInterupt.h"
#include "./components/lcd/MyLcdMonitor.h"



#include "./components/cooldown/Cooldown.h"
#include "./components/ioserial/SerialManager.h"
#include "./components/valveOpener/ValveOpeningManagement.h"
#include "./components/valveOpener/PotentiometerImpl.h"
#include "./components/valvola/Valve.h"


class ControllerScheduler {
    public:
        ControllerScheduler();

        //init the ControllerScheduler
        void init(unsigned long basePeriod);

        //execute the ControllerScheduler
        void execute();

        //get the current state
        StateName getActState();

        //set the new state
        void setNewState(StateName newState);
        
    private:
        StateName lastState = START_STATE;
        ControllerSchedulerObserver* myObs;
        MyLcdMonitor* lcd;

};


#endif