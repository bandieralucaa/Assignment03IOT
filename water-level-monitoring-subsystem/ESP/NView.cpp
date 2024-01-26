#include "NView.h"

void callback(char* topic, byte* payload, unsigned int length); //definita in fondo

//https://github.com/arduino-libraries/WiFi/blob/master/src/WiFi.h

const char* ssid = "qs2d4";   // name of your WiFi network
const char* password = "12345678"; // password of the WiFi network


const char *ID = "RiverMonitor";  // Name of our device, must be unique

const char *FREQ_TOPIC = "river/freq";  // Topic to subcribe to

const char *SAMPLE_TOPIC = "river/sample";  // Topic to publish the light state to

IPAddress broker(192,168,43,132); // IP address of your MQTT broker eg. 192.168.1.50 //192.168.43.132
WiFiClient wclient;

PubSubClient client(wclient); // Setup MQTT client

ControllerObserver* observer;

// Connect to WiFi network
void setup_wifi() {
  #ifdef NET_DEB
  Serial.print("\nConnecting to ");
  Serial.println(ssid);
  #endif

  WiFi.begin(ssid, password); // Connect to network

  while (WiFi.status() != WL_CONNECTED) { // Wait for connection //https://github.com/arduino-libraries/WiFi/blob/master/src/utility/wl_definitions.h#L55C9-L55C21
    delay(500);
    #ifdef NET_DEB
    Serial.print(".");
    #endif
  }

  #ifdef NET_DEB
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  #endif
}

// Reconnect to client MQTT
void reconnectToMQTT() {
  while (!client.connected()) { // Loop until we're reconnected
    
    #ifdef NET_DEB
    Serial.print("Attempting MQTT connection...");
    #endif

    // Attempt to connect
    if(client.connect(ID)) {
      client.subscribe(FREQ_TOPIC); //con questo ricevo i messaggi dalla console

      #ifdef NET_DEB
      Serial.println("connected");
      Serial.print("Subcribed to: ");
      Serial.println(FREQ_TOPIC);
      Serial.println('\n');
      #endif

    } else {
      #ifdef NET_DEB
      Serial.println(" try again");
      #endif
      // Wait 5 seconds before retrying
      delay(100);
    }
  }
}


NView::NView() {
  //setup_wifi(); // Connect to network
  client.setServer(broker, 1883); //8883 per una connessione sicura
  client.setCallback(callback);// Initialize the callback routine

  if (!this->isConnected()) {
    this->reconnect();
  }
  
  
}

bool NView::isConnected(){
  return client.connected() && WiFi.status() == WL_CONNECTED;
}

void NView::reconnect(){
  //riconnetti tutto
  setup_wifi();
  reconnectToMQTT();
} 


void NView::sendSample(double sample) {
  char c[64] = "";
  //conversione da double a char*
  sprintf(c, "%g",sample);
  //manda risultato
  // String tmp = (String)sample;
  client.publish(SAMPLE_TOPIC,c);
}









void NView::keepAliveFunctions(){
  client.loop();
}


void NView::setObserver(ControllerObserver* newObserver){
  observer = newObserver;
}

void modifyFreq(String newVal){
  double ok = newVal.toDouble();
  // stoi(newVal);
  observer->setFreq(ok);
}


// Handle incomming messages from the broker
void callback(char* topic, byte* payload, unsigned int length) {
  String response;

  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }

  if (strcmp(topic, FREQ_TOPIC) == 0) { //topic.compare(FREQ_TOPIC) == 0){
    modifyFreq(response);
  }
  
  // Serial.print("Message arrived [");
  // Serial.print(topic);
  // Serial.print("] ");
  // Serial.println(response);
  // if(response == "on")  // Turn the light on
  // {
  //   digitalWrite(LIGHT_PIN, HIGH);
  //   client.publish(STATE_TOPIC,"on");
  // }
  // else if(response == "off")  // Turn the light off
  // {
  //   digitalWrite(LIGHT_PIN, LOW);
  //   client.publish(STATE_TOPIC,"off");
  // }
}




