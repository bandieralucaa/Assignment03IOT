#ifndef __SONAR__
#define __SONAR__

#include "config.h"

#include <Arduino.h>

class Sonar {
public:
    Sonar(int trigPin, int echoPin);
    
    //get a sample
    double getDistance();

private:
    //implement the measurement code
    double measure();
    int trigPin;
    int echoPin;
};

#endif