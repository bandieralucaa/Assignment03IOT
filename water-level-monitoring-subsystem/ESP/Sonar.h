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
    //implement the code for distance measurement 
    double measure();
    int trigPin;
    int echoPin;
};

#endif