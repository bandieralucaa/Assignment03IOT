#include "./state/State.h"
#include "./components/button/Button.h"

class AutomaticState : public State{
public:
    AutomaticState(Button* button);
    void init();
    StateName changeState();

private:
    Button* button;

};

