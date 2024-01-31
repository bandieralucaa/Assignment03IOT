#ifndef __N_TASK__
#define __N_TASK__

#include "Task.h"
#include "Light.h"
#include "ControllerObserver.h"
#include <Arduino.h>

class NetworkTask : public Task {
  public:
    NetworkTask(Light* l1, Light* l2);
    void work(void *pvParameters);
  
  private:
    Light* lOk;
    Light* lErr;

};


#endif 