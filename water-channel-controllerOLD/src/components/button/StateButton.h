#ifndef __STATEBUTTON__
#define __STATEBUTTON__

#include "./components/button/Button.h"
#include "./task/Task.h"


class StateButton : public Button, public Task {
    public:
        StateButton(int pin);
        bool isPressed();

        void init();
        void tick();

    private:
        int pin;
        bool pushed = false;
};

#endif