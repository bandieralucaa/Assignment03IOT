#ifndef __CONTROLLER_SCHEDULER_OBSERVER__
#define __CONTROLLER_SCHEDULER_OBSERVER__


enum StateName {
    NONE = -1,
    AUTOMATIC_STATE,
    MANUAL_STATE
};

class ControllerSchedulerObserver {
    public:
        virtual StateName getActState() = 0;

};


#endif