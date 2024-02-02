#ifndef __TASK__
#define __TASK__

#include <Arduino.h>
#include "config.h"
#include "ControllerSchedulerObserver.h"

class Task {
    public:

        //init the task
        virtual void init();

        //set the tick of the task
        virtual void tick();

        //start the task
        void start(){
            this->isRunning = true;
        }

        //stop the task
        void stop(){
            this->isRunning = false;
            this->millis = 0;
        }

        //update the elapsed time from last execution and check if a new execution of this thread must occur
        bool updateAndCheckTime(int millis){
            bool res = false;
            this->millis += millis;
            if (this->millis >= this->period){
                res = true;
                this->millis -= this->period;
            }
            return res;
        };

        //set the Observer
        void setObs(ControllerSchedulerObserver* obs){
            this->obs = obs;
        }

    protected:
        bool isRunning = true;
        unsigned long millis = 0;
        unsigned long period = 0; 


        ControllerSchedulerObserver* obs;
        
        

};



#endif