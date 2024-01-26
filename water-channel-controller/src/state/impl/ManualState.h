#include "./state/State.h"
#include "./components/button/Button.h"
#include "./components/lcd/Lcd.h"

class ManualState : public State{
public:
    ManualState(Button* button, Lcd* myLcd);
    void init();
    StateName changeState();

private:
    Button* button;
    Lcd* myLcd;

};

