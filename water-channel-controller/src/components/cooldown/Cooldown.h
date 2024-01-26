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

        //resetta il timer e lo fa ripartire subito 
        void reset(); 

        int percentageComplete();

        void format(unsigned long newClock); //cambia tempo massimo e fallo ripartire

    private:
        unsigned long amountTime;
        Timer t;
};

#endif