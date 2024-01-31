#ifndef __LED__
#define __LED__

#include "Light.h"
#include <Arduino.h>

//imported class by lab resources

class Led : public Light {
public:
    Led(int pin);
    void switchOn();
    void switchOff();

protected:
    int pin;
};


#endif 