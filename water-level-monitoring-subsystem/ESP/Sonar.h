#ifndef __SONAR__
#define __SONAR__

#include "config.h"

#include <Arduino.h>

class Sonar {
public:
    Sonar(int trigPin, int echoPin);
    double getDistance();

private:
    double measure();
    int trigPin;
    int echoPin;
    //double lastRead;
};

#endif