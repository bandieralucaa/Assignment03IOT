#ifndef __CONTROLLER_SCHEDULER_OBSERVER__
#define __CONTROLLER_SCHEDULER_OBSERVER__


class ControllerSchedulerObserver {
    public:
        virtual StateName getActState() = 0;
        virtual void setNewState(StateName newState) = 0;

};


#endif