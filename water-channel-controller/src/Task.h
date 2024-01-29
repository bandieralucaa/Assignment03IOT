#ifndef __TASK__
#define __TASK__

#include <Arduino.h>
#include "config.h"
#include "ControllerSchedulerObserver.h"

class Task {
    public:
        virtual void init();
        virtual void tick();

        void start(){
            this->isRunning = true;
        }

        void stop(){
            this->isRunning = false;
            this->millis = 0;
        }

        bool updateAndCheckTime(int millis){
            bool res = false;
            if (!this->isRunning){
                return res;
            }
            this->millis += millis;
            if (this->millis >= this->period){
                res = true;
                this->millis -= this->period;
            }
            return res;
        };

    protected:
        bool isRunning = true;
        unsigned long millis = 0;
        unsigned long period = 0; 


        ControllerSchedulerObserver* obs;
        
        void setObs(ControllerSchedulerObserver* obs){
            this->obs = obs;
        }

};



#endif