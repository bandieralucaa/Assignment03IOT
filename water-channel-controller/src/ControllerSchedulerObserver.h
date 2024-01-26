#ifndef __CONTROLLER_SCHEDULER_OBSERVER__
#define __CONTROLLER_SCHEDULER_OBSERVER__


#include "./state/State.h"

class ControllerSchedulerObserver {
    public:
        virtual StateName getActState() = 0;

};


#endif