#include <Arduino.h>
#include "math.h"

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.begin(9600);
}

int a = 0;
int b = 0;
void loop() {
  int d = rand();
  (d % 2 == 0) ? a++ : b++;
  Serial.println(((String)a) + " + " + ((String)b) + " = " + ((String)myFunction(a,b)));
  delay(500);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}