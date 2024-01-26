#include "./state/State.h"
#include "./components/button/Button.h"
#include "./components/lcd/Lcd.h"


class AutomaticState : public State{
public:
    AutomaticState(Button* button, Lcd* myLcd);
    void init();
    StateName changeState();

private:
    Button* button;
    Lcd* myLcd;

};

