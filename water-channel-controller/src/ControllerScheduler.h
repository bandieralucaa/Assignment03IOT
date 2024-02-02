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
#include "./components/valve/Valve.h"


class ControllerScheduler {
    public:
        ControllerScheduler();

        //init the ControllerScheduler
        void init(unsigned long basePeriod);

        //execute the ControllerScheduler
        void execute();

        //during coding, we notice that pass directly the pointer of this obj to other obj 
        //was source of error. So we reify the interface of this obj (ControllerSchedulerObserver) into a class
        //We maintains its method also in this class 
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