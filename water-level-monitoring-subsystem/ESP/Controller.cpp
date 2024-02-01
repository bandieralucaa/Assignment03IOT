#include "Controller.h"

Controller::Controller(){
  #ifdef DEBUG_NOPANIC
  Serial.println("CONTROLLER A");
  #endif
  this->okLed = new Led(LED_O);
  this->errLed = new Led(LED_W);
  this->sonar = new Sonar(TRIG_P, ECHO_P);

  this->view = new NView();
  
}


void Controller::setMeasurement(double measure){
  #ifdef DEBUG_NOPANIC
  Serial.println("CONTROLLER B");
  #endif
  this->actMeasure = measure;
}

void Controller::setConnection(NetworkState newState){
  #ifdef DEBUG_NOPANIC
  Serial.println("CONTROLLE R C");
  #endif

  this->actNS = newState;
  if(newState == CONN) {
    taskmes->start();
  } else {
    taskmes->pause();
  }
}

bool Controller::isBoardConnected(){
  #ifdef DEBUG_NOPANIC
    Serial.println("CONTROLLER D");
    #endif
  return this->view->isConnected();
}

void Controller::setFreq(unsigned long newFreq){
  #ifdef DEBUG_NOPANIC
  Serial.println("CONTROLLER E");
  #endif
  this->actFreq = newFreq;

  #ifdef CONTR_D
  Serial.print("Frequence received from MQTT: ");
  Serial.println(newFreq);
  #endif
  taskmes->setNewFreq((unsigned long) newFreq);
}



void Controller::reconnectBoard(){
  this->view->reconnect();
}





void handlerT1(void* vv) {
  #ifdef DEBUG_NOPANIC
  Serial.println("CONTROLLER F");
  #endif
  taskmes->work(vv);
}

void handlerT2(void* vv) {
  #ifdef DEBUG_NOPANIC
  Serial.println("CONTROLLER G");
  #endif
  tasknet->work(vv);
}


void Controller::init(){
  #ifdef DEBUG_NOPANIC
  Serial.println("CONTROLLER H");
  #endif
  int tmpSize = 4096; //(configMINIMAL_STACK_SIZE * 3)
  this->view->setObserver(this);

  xTaskHandle tmp;
  taskmes = new MeasurementTask(this->sonar);
  xTaskCreate(&handlerT1, "Measure Task", tmpSize , ((void*)(this)), tskIDLE_PRIORITY + 1, &tmp);
  taskmes->saveTaskHandler(&tmp);

  xTaskHandle tmp1;
  tasknet = new NetworkTask(this->okLed, this->errLed);
  xTaskCreate(&handlerT2, "Network Task", tmpSize , ((void*)(this)), tskIDLE_PRIORITY + 2, &tmp1);
  taskmes->saveTaskHandler(&tmp);

  this->lastTime = millis();
}


void Controller::tick(){
  #ifdef DEBUG_NOPANIC
  Serial.println("CONTROLLER K");
  #endif
  this->view->keepAliveFunctions();
  if(this->view->isConnected()){
    if( (millis() > ((this->actFreq) + this->lastTime))){
      this->view->sendSample(this->actMeasure);
      this->lastTime = millis();
    }
  }
  
}



