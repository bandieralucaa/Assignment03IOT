#ifndef __VALVE__
#define __VALVE__

#include "./Task.h"
#include "./components/valve/Servomotor.h"
#include "./components/ioserial/OutSender.h"
#include "./components/lcd/Lcd.h"
#include "./components/valveOpener/OpeningDetection.h"
#include <Servo.h>
#include "config.h"

#define MAX_ANGLE MAX_ANGLE_SERVO
#define MIN_ANGLE MIN_ANGLE_SERVO

class Valve : public Servomotor, public Task{ 

public:
    Valve(int pin, bool isActOpen, OutSender* toSerial, Lcd* myLcd, OpeningDetection* od);
    
    int getActPos();
    
    void init();
    void tick();

private:
    OpeningDetection* od;
    OutSender* toSerial;
    Lcd* myLcd;
    Servo motor;
    //this value is saved into 0-180 scale
    int currentPos;
    //this value is saved into 0-180 scale
    int settedPos;

};

#endif