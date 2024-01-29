#include "ControllerSchedulerObserver.h"

ControllerSchedulerObserver::ControllerSchedulerObserver(StateName initState){
    this->myState = initState;
}


StateName ControllerSchedulerObserver::getActState(){
    return this->myState;
}

void ControllerSchedulerObserver::setNewState(StateName newState){
    this->myState = newState;
}

