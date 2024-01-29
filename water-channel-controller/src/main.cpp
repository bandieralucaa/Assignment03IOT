#include <Arduino.h>

#include "ControllerScheduler.h"
#include "config.h"

ControllerScheduler* c;

void setup() {
  c = new ControllerScheduler();
  c->init(SCHEDULE_BASE_PERIOD);
}

void loop() {
  c->execute();
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}