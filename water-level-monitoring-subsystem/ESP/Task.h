#ifndef __TASK__
#define __TASK__

#include <Arduino.h>
#include "ControllerObserver.h"
// #include <FreeRTOS.h>

class Task {
  public:
    virtual void work(void *pvParameters) = 0;

    void start(){
      vTaskResume(this->myHandle);
    }
    
    void pause(){
      vTaskSuspend(this->myHandle);
    }

    void stop(){
      //gestiscimi
    }

    void saveTaskHandler(xTaskHandle* handle){
      this->myHandle = *handle;
    }
  
  
  protected:
    ControllerObserver* byTaskToController;

    void setController(ControllerObserver* newCon){
      this->byTaskToController = newCon;
    }

    xTaskHandle myHandle;

};

#endif 