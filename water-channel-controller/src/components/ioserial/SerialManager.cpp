#include "SerialManager.h"

#include <Arduino.h>

#define COMMAND_CHAR '_'
#define ARGUMENT_CHAR ':'

SerialManager::SerialManager(){
    this->oraSample = "";
    this->parsedAperturaValvola = 0;
    MsgService.init();
    Serial.setTimeout(100);
}

String trasdutter(char command, String value){
    return ((String)COMMAND_CHAR) + ((String)command) + ((String)ARGUMENT_CHAR) + value;
}



void SerialManager::init(){
    String comm = "";
    comm += trasdutter('h', (String)this->oraSample);
    comm += trasdutter('v', (String)this->parsedAperturaValvola);
    comm += trasdutter('c', "0");
    MsgService.sendMsg(comm);
}

/*void SerialManager::tick(){
    if (MsgService.isMsgAvailable()){           
        Msg* msg = MsgService.receiveMsg();    
        if (msg->getContent().length() > 0) {

        }
        delete msg;
    }   
}

void SerialManager::sendActValveOpen(int value){

}

void SerialManager::getParsedValveOpening(){

}

void SerialManager::getHourModApertura(){

}*/


void SerialManager::executeCommandByGui(String command, String value){
    char c = command.charAt(0);
    switch (c)
    {
        case 'o':
            this->parsedAperturaValvola = value.toInt();
            break;
        
        default:
            break;
    }
}




void SerialManager::executeCommands(String comm){
    unsigned int a = comm.length();
    unsigned int i=0;
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
}

