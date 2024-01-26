// #include "Sender.h"






// Sender::Sender();










// void Sender::sendSample(double value);




// /******************************************************************************
// MQTT_Light_Example.ino
// Example for controlling a light using MQTT
// by: Alex Wende, SparkFun Electronics

// This sketch connects the ESP8266 to a MQTT broker and subcribes to the topic
// room/light. When "on" is recieved, the pin LIGHT_PIN is toggled HIGH.
// When "off" is recieved, the pin LIGHT_PIN is toggled LOW.
// ******************************************************************************/

// #include <WiFi.h>
// #include <PubSubClient.h>





// // Handle incomming messages from the broker
// void callback(char* topic, byte* payload, unsigned int length) {
//   String response;

//   for (int i = 0; i < length; i++) {
//     response += (char)payload[i];
//   }
//   Serial.print("Message arrived [");
//   Serial.print(topic);
//   Serial.print("] ");
//   Serial.println(response);
//   if(response == "on")  // Turn the light on
//   {
//     digitalWrite(LIGHT_PIN, HIGH);
//     client.publish(STATE_TOPIC,"on");
//   }
//   else if(response == "off")  // Turn the light off
//   {
//     digitalWrite(LIGHT_PIN, LOW);
//     client.publish(STATE_TOPIC,"off");
//   }
// }

// // Connect to WiFi network
// void setup_wifi() {
//   Serial.print("\nConnecting to ");
//   Serial.println(ssid);

//   WiFi.begin(ssid, password); // Connect to network

//   while (WiFi.status() != WL_CONNECTED) { // Wait for connection
//     delay(500);
//     Serial.print(".");
//   }

//   Serial.println();
//   Serial.println("WiFi connected");
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());
// }

// // Reconnect to client
// void reconnect() {
//   // Loop until we're reconnected
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     // Attempt to connect
//     if(client.connect(ID)) {
//       client.subscribe(TOPIC);
//       Serial.println("connected");
//       Serial.print("Subcribed to: ");
//       Serial.println(TOPIC);
//       Serial.println('\n');

//     } else {
//       Serial.println(" try again in 1 seconds");
//       // Wait 5 seconds before retrying
//       delay(1000);
//     }
//   }
// }

// void setup() {
//   Serial.begin(115200); // Start serial communication at 115200 baud
//   pinMode(LIGHT_PIN, OUTPUT); // Configure LIGHT_PIN as an output
//   delay(100);
//   setup_wifi(); // Connect to network
//   client.setServer(broker, 1883); //8883 per una connessione sicura
//   client.setCallback(callback);// Initialize the callback routine
// }

// void loop() {
//   if (!client.connected())  // Reconnect if connection is lost
//   {
//     reconnect();
//   }
//   client.loop();
// }