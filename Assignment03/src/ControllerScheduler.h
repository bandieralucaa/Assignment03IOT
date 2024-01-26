#ifndef __CONTROLLERSCHEDULER__
#define __CONTROLLERSCHEDULER__

#include "config.h"

#include "./task/Task.h"
#include "./state/State.h"
#include "./components/button/StateButton.h"
#include "./components/cooldown/Cooldown.h"
#include "./components/ioserial/SerialManager.h"
#include "./components/valve/ValveOpeningManagement.h"
#include "./components/lcd/Lcd.h"

class ControllerScheduler {
public:
    ControllerScheduler();
    void init();
    void execute();
    StateName getActState();
};


#endif