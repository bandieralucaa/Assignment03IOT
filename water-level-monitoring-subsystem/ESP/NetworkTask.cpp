
#include "NetworkTask.h"

NetworkTask::NetworkTask(Light* l1, Light* l2) {
  this->lOk = l1;
  this->lErr = l2;
}

void turnOnOff(Light* l1, Light* l2){
  l1->switchOn();
  l2->switchOff();
}
  
void NetworkTask::work(void *pvParameters) {
  this->setController( ( (ControllerObserver*) (pvParameters) ) );

  bool isPrevConn = false;
  
  while (true) {

    if (this->byTaskToController->isBoardConnected()) {
      if(!isPrevConn){
        #ifdef NETTASK_DEBUG
        Serial.print("Connessione presente, accendo led verde!");
        #endif
        turnOnOff(this->lOk, this->lErr); 
        isPrevConn = !isPrevConn;
        this->byTaskToController->setConnection(CONN);
      }

    } else {
      if(isPrevConn){
        #ifdef NETTASK_DEBUG
        Serial.print("Connessione assente, accendo led rosso!");
        #endif
        turnOnOff(this->lErr, this->lOk); 
        isPrevConn = !isPrevConn;
        this->byTaskToController->setConnection(NOCONN);
      }

    }
    // this->byTaskToController->setMeasurement(sampled);
    #ifdef ALIVE_TASK_DEBUG
    Serial.print("§§§§§§§§§§§§§§§§§ Network vivo, valGuardia: ");
    Serial.println(isPrevConn);
    #endif
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

