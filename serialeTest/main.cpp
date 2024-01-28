#include <Arduino.h>

const int buttonPin = 2;  // Pin a cui è collegato il pulsante
int lastButtonState = LOW; // Parti da un valore noto

void setup() {
  Serial.begin(9600);
  delay(2000);  // Attendere 2 secondi prima di iniziare
  pinMode(buttonPin, INPUT);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    delay(50);  // De-bouncing
    if (reading != lastButtonState) {
      lastButtonState = reading;

      if (reading == HIGH) {
        int randomNumber = random(1, 101);
        Serial.println(randomNumber);  // Usa println per aggiungere un carattere di nuova riga
        delay(1000);  // Attendere 1 secondo prima di consentire nuove letture
      }
    }
  }
}
