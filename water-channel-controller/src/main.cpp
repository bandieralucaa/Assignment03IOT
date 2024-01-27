/********************
 * 
 *  Progetto a cura di:
 *  - Bandiera Luca
 *  - Pesaresi Jacopo
 * 
 * 
********************/

#include <Arduino.h>
#include "config.h"
#include "ControllerScheduler.h"

ControllerScheduler* myController;

void setup() {
  pinMode(5, OUTPUT);
  myController = new ControllerScheduler();
  myController->init(SCHEDULE_BASE_PERIOD);
}


void loop() {
  myController->execute();
}