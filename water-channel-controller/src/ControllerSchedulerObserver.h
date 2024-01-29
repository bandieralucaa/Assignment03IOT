#ifndef __CONTROLLER_SCHEDULER_OBSERVER__
#define __CONTROLLER_SCHEDULER_OBSERVER__

#include "config.h"

class ControllerSchedulerObserver {
    public:
        ControllerSchedulerObserver(StateName initState);
        StateName getActState();
        void setNewState(StateName newState);
    private:
        StateName myState;

};


#endif