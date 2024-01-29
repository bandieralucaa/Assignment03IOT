#ifndef __TASK__
#define __TASK__

#include <Arduino.h>
#include "config.h"

class Task {
    public:
    virtual void init();
    virtual void tick();

    virtual void start(){
        this->isRunning = true;
    }

    virtual void stop(){
        this->isRunning = false;
        this->millis = 0;
    }

    virtual bool updateAndCheckTime(int millis){
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
};



#endif