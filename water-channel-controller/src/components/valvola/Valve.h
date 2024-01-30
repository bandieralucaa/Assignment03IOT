#ifndef __VALVE__
#define __VALVE__

#include "./Task.h"
#include "./components/valvola/Servomotor.h"
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
    void setPos(int newPos);
    int getActPos();

    void init();
    void tick();

private:
    OpeningDetection* od;
    OutSender* toSerial;
    Lcd* myLcd;
    Servo motor;
    int currentPos;
    int settedPos;

};

#endif