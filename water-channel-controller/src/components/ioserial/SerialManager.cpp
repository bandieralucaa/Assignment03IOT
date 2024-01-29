#include "SerialManager.h"

#include <Arduino.h>

#define COMMAND_CHAR '_'
#define ARGUMENT_CHAR ':'
//#define JOINER 'e'

SerialManager::SerialManager(ExternalSources* vom){
    this->parsedAperturaValvola = 50;
    this->period = IOMAN_PERIOD;
    this->vom = vom;
    MsgService.init();
    Serial.setTimeout(100);
}

String trasdutter(char command, String value){
    return ((String)COMMAND_CHAR) + ((String)command) + ((String)ARGUMENT_CHAR) + value;
}



void SerialManager::init(){
    String comm = "";
   // comm += trasdutter('h', (String)this->oraSample);
    comm += trasdutter('v', (String)this->parsedAperturaValvola);
    comm += trasdutter('c', "0");
    MsgService.sendMsg(comm);
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

    String toSend = "";
    toSend = trasdutter('v', ((String) this->actValvOpening)); //this->actValvOpening
    MsgService.sendMsg(toSend);
    
    delay(10);//TODO da controllare se ce n'è bisogno
    String toSend2 = "";
    toSend2 = trasdutter('s', byStatusToString());
    MsgService.sendMsg(toSend2);

    // MsgService.sendMsg(toSend);
}

void SerialManager::sendActValveOpen(int value){
    this->actValvOpening = value;
}



void SerialManager::executeCommandByGui(String command, String value){
    char c = command.charAt(0);
    switch (c)
    {
        case 'v':
            Serial.println(command + " / " + value);
            //this->vom->setValveOpBySerial(40);
            
            // int val = 145; //TODO da String a Int // 145;// (value.substring(0, value.lastIndexOf(JOINER))).toInt();
            // //int d = 999;//(value.substring(value.lastIndexOf(JOINER, value.length()))).toInt(); //TODO DA CONTROLLARE INDICI
            // this->parsedAperturaValvola = val;
            // //this->oraSample = d;
            break;
    }
}




void SerialManager::executeCommands(String comm){
    unsigned int a = comm.length();
    unsigned int i = 0;
    String command = "";
    String argument = "";
    bool parsingCommand = true;
    #ifdef DEBUG_IOMAN_WITHOUT_CONSOLE
    Serial.print(comm); 
    #endif
    while(i<a || comm.charAt(i) != '\n') {
        char c = comm.charAt(i);
        switch (c)
        {
        case COMMAND_CHAR:
            if(command.length() > 0){
                executeCommandByGui(command, argument);
            }
            command = "";
            argument = "";
            parsingCommand = true;
            break;
        
        case ARGUMENT_CHAR:
            parsingCommand = false;
            break;

        default:
            parsingCommand ? command += c : argument += c;
            break;
        }
        i++;
    }
    executeCommandByGui(command, argument); //TODO: forse era un bug

}

