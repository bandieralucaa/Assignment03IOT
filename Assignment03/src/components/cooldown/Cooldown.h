#ifndef __COOLDOWN__
#define __COOLDOWN__

#include "Timer.h"

class Cooldown {
    public:
        Cooldown(unsigned long clock);
        
        void init();
        bool isOver();
        void pause();
        void resume();
        void reset();
        int percentageComplete();
        void format(unsigned long newClock);

    private:
        unsigned long amountTime;
        Timer timer;
};

#endif