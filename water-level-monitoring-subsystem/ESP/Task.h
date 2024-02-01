#ifndef __TASK__
#define __TASK__

#include <Arduino.h>
#include "ControllerObserver.h"

class Task {
  public:
    // let other class implement the code that this task must execute
    virtual void work(void *pvParameters) = 0;

    //function to manage basic aspect of a task using "FreeRTOS" library
    void start(){
      vTaskResume(this->myHandle);
    }
    //function to manage basic aspect of a task using "FreeRTOS" library
    void pause(){
      vTaskSuspend(this->myHandle);
    }
    //function to manage basic aspect of a task using "FreeRTOS" library
    void stop(){
      vTaskDelete(this->myHandle);
    }

    //function to save variable that help management of a task
    void saveTaskHandler(xTaskHandle* handle){
      this->myHandle = *handle;
    }
  
  
  protected:
    CM* byTaskToController;

    void setController(CM* newCon){
      this->byTaskToController = newCon;
    }

    xTaskHandle myHandle;

};

#endif 