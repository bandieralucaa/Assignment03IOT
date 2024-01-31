
#include "NetworkTask.h"

NetworkTask::NetworkTask(Light* l1, Light* l2) {
  #ifdef DEBUG_NOPANIC
    Serial.println("NETWORKTASK");
    #endif
  this->lOk = l1;
  this->lErr = l2;
}

void turnOnOff(Light* l1, Light* l2){
  #ifdef DEBUG_NOPANIC
    Serial.println("NETWORKTASK");
    #endif
  l1->switchOn();
  l2->switchOff();
}
  
void NetworkTask::work(void *pvParameters) {
  #ifdef DEBUG_NOPANIC
    Serial.println("NETWORKTASK");
    #endif
  this->setController( ( (ControllerObserver*) (pvParameters) ) );

  bool isPrevConn = false;
  turnOnOff(this->lErr, this->lOk); 
  while (true) {

    if (this->byTaskToController->isBoardConnected()) {
      if(!isPrevConn){
        #ifdef NETTASK_DEBUG
        Serial.println("Connessione presente, accendo led verde!");
        #endif
        turnOnOff(this->lOk, this->lErr); 
        isPrevConn = !isPrevConn;
        this->byTaskToController->setConnection(CONN);
      }

    } else {
      if(isPrevConn){
        #ifdef NETTASK_DEBUG
        Serial.println("Connessione assente, accendo led rosso!");
        #endif
        turnOnOff(this->lErr, this->lOk); 
        isPrevConn = !isPrevConn;
        this->byTaskToController->setConnection(NOCONN);
        this->byTaskToController->reconnectBoard();
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

