#ifndef __STATEBUTTON__
#define __STATEBUTTON__

#include <Arduino.h>
#include "./components/button/Button.h"
#include "./ControllerSchedulerObserver.h"
#include "./config.h"


class StateButtonInterupt : public Button {
    public:
        StateButtonInterupt(int pin, ControllerSchedulerObserver* obs);

        // Return the current state of the button
        StateName buttonState();

    private:
        int pin;
};

#endif