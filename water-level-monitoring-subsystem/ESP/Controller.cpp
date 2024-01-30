#include "Controller.h"

#define TOLLERANCE_PAIR 10000 //dopo 10 secondi riprovo la procedura da capo

bool startReconection = true;


Controller::Controller(){
  this->okLed = new Led(LED_O);
  this->errLed = new Led(LED_W);
  this->sonar = new Sonar(TRIG_P, ECHO_P);

  this->view = new NView();
  
  #ifdef MYDEBUG
  Serial.println("UFFA");
  #endif
  //void setObserver(CV* newObserver);
}





void Controller::setMeasurement(double measure){
  this->actMeasure = measure;
  // this->view->setObserver(this);
}

void Controller::setConnection(NetworkState newState){
  this->actNS = newState;
  if(newState == CONN) {
    taskmes->start();
    startReconection = true;
  }
}

bool Controller::isBoardConnected(){
  return this->view->isConnected();
}

void Controller::setFreq(double newFreq){
  this->actFreq = newFreq;

  #ifdef MYDEGUB
  Serial.print("Frequence received from MQTT: ");
  Serial.println(newFreq);
  #endif
  ///MODIFICA EVENTUALMENTE LA FREQUENZA DEL TASK
  taskmes->setNewFreq((unsigned long) newFreq);
  taskmes->start();
}


void handlerT1(void* vv){
  taskmes->work(vv);
}

void handlerT2(void* vv){
  tasknet->work(vv);
}

unsigned long lastTime;
void Controller::init(){
  int tmpSize = 4096; //(configMINIMAL_STACK_SIZE * 3)
  this->view->setObserver(this);

  xTaskHandle tmp;

  taskmes = new MeasurementTask(this->sonar);
  
  xTaskCreate(&handlerT1, "Measure Task", tmpSize , ((void*)(this)), tskIDLE_PRIORITY + 1, &tmp);
  taskmes->saveTaskHandler(&tmp);

  xTaskHandle tmp1; //logica a puntatori evidentemente non funziona

  tasknet = new NetworkTask(this->okLed, this->errLed);

  xTaskCreate(&handlerT2, "Network Task", tmpSize , ((void*)(this)), tskIDLE_PRIORITY + 2, &tmp1);
  taskmes->saveTaskHandler(&tmp);

  // this->taskmes = new MeasurementTask(this->sonar);
  // xTaskHandle myHandle2;
  // xTaskCreate(&blinkTask, "Blink Task", configMINIMAL_STACK_SIZE, ((void*)(myPay)), tskIDLE_PRIORITY + 2, &handle);

  //CREAZIONE e smazzamento DEI TASK
  lastTime = millis();
}


void handlerRecCon(void* vv) {
  NView* n = ((NView*) vv);
  n->reconnect();
}

void Controller::resumeConnection(){
  int tmpSize = 4096; //(configMINIMAL_STACK_SIZE * 3)
  xTaskCreate(&handlerRecCon, "Resume Connection", tmpSize, ((void*)(this->view)), tskIDLE_PRIORITY + 1, NULL);
  vTaskDelete(NULL);
}



void Controller::tick(){
  if(this->view->isConnected()){
    this->view->keepAliveFunctions();

    if( millis() > (((int) this->actFreq) + lastTime)){
      this->view->sendSample(this->actMeasure);
      lastTime = millis();
    }

  } else {
    if(startReconection){
      taskmes->pause();
      this->resumeConnection();
      startReconection = false;
    }

    if( millis() > ((TOLLERANCE_PAIR) + lastTime)) { //nel caso la rete si sia ripersa
      this->resumeConnection();
      lastTime = millis();
    }
    
  }
  
}


