#include "Sonar.h"

#define TIMEOUT_SONAR (50000)

Sonar::Sonar(int trigPin, int echoPin){
    this->trigPin = trigPin ;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);  
}


double Sonar::getDistance(){
    #ifdef DEBUG_NOPANIC
    Serial.println("SONAR");
    #endif
    return this->measure();
}


double Sonar::measure(){
    #ifdef DEBUG_NOPANIC
    Serial.println("SONAR");
    #endif
    //codice ispirato da materiale di laboratorio
    float temperature = 20; 

    float vs = 331.45 + 0.62*temperature;

    /* Triggering stage: sending the impulse */
    digitalWrite(this->trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(this->trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trigPin,LOW);
    
    /* Receiving the echo */
    unsigned long m = pulseIn(this->echoPin, HIGH, TIMEOUT_SONAR);
    if (m == 0) {
        #ifdef SONAR_DEBUG
        Serial.println("@\n 999.9");
        Serial.print(" ########################## ");
        #endif
        //this->lastRead = 999.0;
        return 999.9;
    }
    float tUS = m;
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;

    #ifdef SONAR_DEBUG
    Serial.println("\n@" + (String) tUS);
    Serial.print(" ########################## ");
    Serial.println(d);
    #endif
    
    return d; //this->lastRead = d;
}
