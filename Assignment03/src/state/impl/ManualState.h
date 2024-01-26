#include "./state/State.h"
#include "./components/button/Button.h"

class ManualState : public State{
public:
    ManualState(Button* button);
    void init();
    StateName changeState();

private:
    Button* button;

};

