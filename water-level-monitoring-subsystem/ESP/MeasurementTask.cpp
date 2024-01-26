
#include "MeasurementTask.h"

MeasurementTask::MeasurementTask(Sonar* rM) {
  // this->ControllerModel = ConMod;
  this->rM = rM;
  this->frequency = 1000;
}

void MeasurementTask::setNewFreq(unsigned long frequency){
  this->frequency = frequency;
}


  
void MeasurementTask::work(void *pvParameters) {
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

