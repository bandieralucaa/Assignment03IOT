#ifndef __VALVE__
#define __VALVE__

#include "./task/Task.h"
#include "./components/valvola/Servomotor.h"
#include <Servo.h>
#include "config.h"

#define MAX_ANGLE 180
#define MIN_ANGLE 0

class Valve : public Servomotor, public Task{ 

public:
    Valve(int pin, bool isActOpen);
    void setPos();
    int getActPos();

    void init();
    void tick();

private:
    Servo motor;
    int delta;

};

#endif