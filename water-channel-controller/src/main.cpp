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
bool initCC = true;

void setup() {

  pinMode(5, OUTPUT);
  myController = new ControllerScheduler();
  
  myController->init(SCHEDULE_BASE_PERIOD);
  initCC = false;

}


void loop() {
  myController->execute();
}