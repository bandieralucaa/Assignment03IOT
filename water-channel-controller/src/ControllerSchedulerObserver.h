#ifndef __CONTROLLER_SCHEDULER_OBSERVER__
#define __CONTROLLER_SCHEDULER_OBSERVER__

#include "config.h"

class ControllerSchedulerObserver {
    public:
        ControllerSchedulerObserver(StateName initState);
        //get the state of the system (so the type of valve management)
        StateName getActState();
        //upload the state of the machine (so set a new type of valve management)
        void setNewState(StateName newState);
    private:
        StateName myState;

};


#endif