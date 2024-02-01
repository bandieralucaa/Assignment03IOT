#include "SerialManager.h"

#include <Arduino.h>

#define COMMAND_CHAR '_'
#define ARGUMENT_CHAR ':'

SerialManager::SerialManager(ExternalSources* vom){
    this->parsedAperturaValvola = START_VALVE_OP;
    this->period = IOMAN_PERIOD;
    this->vom = vom;
    MsgService.init();
    Serial.setTimeout(175);
    this->lastValveSend = -1;
    this->lastStateSend = NONE;
}

String trasdutter(char command, String value){
    return ((String)COMMAND_CHAR) + ((String)command) + ((String)ARGUMENT_CHAR) + value;
}



void SerialManager::init() {
    String toSend = "";
    int tmp = this->actValvOpening;
    toSend = trasdutter('v', ((String) tmp)); 
    MsgService.sendMsg(toSend);
    this->lastValveSend = this->actValvOpening;
    delay(10);
    String toSend2 = "";
    toSend2 = trasdutter('s', byStatusToString());
    MsgService.sendMsg(toSend2);
    this->lastStateSend = this->obs->getActState();
}

String SerialManager::byStatusToString(){
    String tmp = "";
    switch (this->obs->getActState()) {
        case AUTOMATIC_STATE:
            tmp = "A";
            break;
        
        case MANUAL_STATE:
            tmp = "M";
            break;
        
        default:
            break;
    }
    return tmp;
}

void SerialManager::tick() {
    if (MsgService.isMsgAvailable()){           
        Msg* msg = MsgService.receiveMsg();    
        if (msg->getContent().length() > 0) {
            this->executeCommands(msg->getContent());
        }
        delete msg;
    }

    if (this->lastValveSend != this->actValvOpening) {
        String toSend = "";
        int tmp = this->actValvOpening;
        toSend = trasdutter('v', ((String) tmp)); 
        MsgService.sendMsg(toSend);
        this->lastValveSend = this->actValvOpening;
    }
    if (this->lastStateSend != this->obs->getActState()){
        delay(10);
        String toSend2 = "";
        toSend2 = trasdutter('s', byStatusToString());
        MsgService.sendMsg(toSend2);
        this->lastStateSend = this->obs->getActState();
    }

}

//value is in the 1020 scale
void SerialManager::sendActValveOpen(int value){
    this->actValvOpening = map(value, 0, MAX_POT_VALUE, 0, 100);
}

int myPot(int b, int e){
    int res = 1;
    for(int i = 0; i < e; i++){
        res *= b;
    }
    return res;
}

int myStoi(String value) {
    int res = 0;
    int pos = value.length();
    for (int i = 0; i < pos; i++) {
        int exponential = pos - i - 1;
        int val = value.charAt(i) - 48;
        res += ((int) ((val) * (myPot(10, exponential))));
    }
    return res;
}

void SerialManager::executeCommandByGui(char c, String value){
    switch (c)
    {
        case 'v':
            int tmp = myStoi(value); //received a percentage value
            this->vom->setValveOpBySerial(map(tmp, 0, 100, 0, MAX_POT_VALUE)); //convert it into 1020 scale
            break;
    }
}


//serial should receive one command at a time for this method to work properly
void SerialManager::executeCommands(String comm){
    char command = comm.charAt(1);
    String value = comm.substring(3, comm.length());
    executeCommandByGui(command, value);
}

