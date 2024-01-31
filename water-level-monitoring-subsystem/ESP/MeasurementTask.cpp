
#include "MeasurementTask.h"

MeasurementTask::MeasurementTask(Sonar* rM) {
  #ifdef DEBUG_NOPANIC
    Serial.println("MEASUREMENTTASK");
    #endif
  this->rM = rM;
  this->frequency = 1000;
}

void MeasurementTask::setNewFreq(unsigned long frequency){
  #ifdef DEBUG_NOPANIC
    Serial.println("MEASUREMENTTASK");
    #endif
  this->frequency = frequency;
}


  
void MeasurementTask::work(void *pvParameters) {
  #ifdef DEBUG_NOPANIC
    Serial.println("MEASUREMENTTASK");
    #endif
  this->setController( ( (ControllerObserver*) (pvParameters) ) );
  double sampled = 0.0;
  while (true) {
    sampled = this->rM->getDistance();
    this->byTaskToController->setMeasurement(sampled);
    #ifdef ALIVE_TASK_DEBUG
    Serial.println("§§§§§§§§§§§§§§§§§ Measurement vivo!");
    #endif
    vTaskDelay(pdMS_TO_TICKS(this->frequency / 2));
  }
}

