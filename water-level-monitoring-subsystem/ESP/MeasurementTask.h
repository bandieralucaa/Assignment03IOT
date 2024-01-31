#ifndef __M_TASK__
#define __M_TASK__

#include "Task.h"
#include "Sonar.h"
#include "ControllerObserver.h"
#include <Arduino.h>

class MeasurementTask : public Task {
  public:
    MeasurementTask(Sonar* rM);
    void work(void *pvParameters);
    void setNewFreq(unsigned long frequency);
  
  private:
    Sonar* rM;;
    unsigned long frequency;

};


#endif 