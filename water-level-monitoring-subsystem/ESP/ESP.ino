
#include "Controller.h"
#include "config.h"

Controller* c;


void setup() {
  #ifdef MYDEGUB
  Serial.begin(115200);
  Serial.println("CIAO");
  #endif
  // put your setup code here, to run once:
  c = new Controller();
  c->init();
}

void loop() {
  #ifdef MYDEGUB
  // put your main code here, to run repeatedly:
  // Serial.print("jacopo ->");
  // Serial.print(sizeof(Controller));
  // Serial.print(" / ");
  // Serial.print(sizeof(Controller*));
  // Serial.print(" / ");
  // Serial.println(configMINIMAL_STACK_SIZE + sizeof(Controller));
  #endif
  c->tick();


}
