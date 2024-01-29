#ifndef __CONTROLLERSCHEDULER__
#define __CONTROLLERSCHEDULER__

#include "ControllerSchedulerObserver.h"

// #include "config.h"

// #include "./task/Task.h"

// #include "./state/State.h"
// #include "./state/impl/AutomaticState.h"
// #include "./state/impl/ManualState.h"

// #include "./components/button/StateButton.h"
// #include "./components/cooldown/Cooldown.h"
// #include "./components/ioserial/SerialManager.h"
// #include "./components/valveOpener/ValveOpeningManagement.h"
// #include "./components/valveOpener/PotentiometerImpl.h"

// #include "./components/valvola/Valve.h"
// #include "./components/lcd/MyLcdMonitor.h"

class ControllerScheduler {
public:
    ControllerScheduler();
    void init(unsigned long basePeriod);
    void execute();
    StateName getActState();

};


#endif