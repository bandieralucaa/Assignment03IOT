#ifndef __COOLDOWN__
#define __COOLDOWN__

#include "Timer.h"

class Cooldown {
    public:
        Cooldown(unsigned long clock);

        //initialize the cooldown
        void init();

        //return true if the cooldown is over
        bool isOver();

        //pause the cooldown
        void pause();

        //resume the cooldown from where it was paused
        void resume();

        //reset the timer and start it again immediately
        void reset(); 

        //return the cooldown completion percentage 
        int percentageComplete();

        //change the amount of time left and restart the timer
        void format(unsigned long newClock);

    private:
        unsigned long amountTime;
        Timer t;
};

#endif