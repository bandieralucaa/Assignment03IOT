/****************************
 * 
 * 
 * Progetto a cura di:
 *    Bandiera Luca
 *    Pesaresi Jacopo
 * 
 * 
******************************/


#include "Controller.h"
#include "config.h"

Controller* c;


void setup() {

  Serial.begin(115200);
  
  #ifdef DEBUG_NOPANIC
  Serial.println("ESP");
  #endif
  
  #ifdef MYDEGUB
  Serial.println("HELLO");
  #endif
  
  c = new Controller();
  c->init();
}

void loop() {
  #ifdef DEBUG_NOPANIC
  Serial.println("ESP");
  #endif
  c->tick();
}
