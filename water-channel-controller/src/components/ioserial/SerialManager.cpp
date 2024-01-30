#include "SerialManager.h"

#include <Arduino.h>

#define COMMAND_CHAR '_'
#define ARGUMENT_CHAR ':'
//#define JOINER 'e'

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



void SerialManager::init(){
    String toSend = "";
    int tmp = this->actValvOpening;//map(this->actValvOpening, MIN_ANGLE_SERVO, MAX_ANGLE_SERVO, 0, 100);
    toSend = trasdutter('v', ((String) tmp)); //this->actValvOpening
    MsgService.sendMsg(toSend);
    this->lastValveSend = this->actValvOpening;
    delay(10);//TODO da controllare se ce n'è bisogno
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
        int tmp = this->actValvOpening;//map(this->actValvOpening, MIN_ANGLE_SERVO, MAX_ANGLE_SERVO, 0, 100);
        toSend = trasdutter('v', ((String) tmp)); //this->actValvOpening
        MsgService.sendMsg(toSend);
        this->lastValveSend = this->actValvOpening;
    }
    if (this->lastStateSend != this->obs->getActState()){
        delay(10);//TODO da controllare se ce n'è bisogno
        String toSend2 = "";
        toSend2 = trasdutter('s', byStatusToString());
        MsgService.sendMsg(toSend2);
        this->lastStateSend = this->obs->getActState();
    }

}

//value è nella scala 1020
void SerialManager::sendActValveOpen(int value){
    //this->actValvOpening = value;
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
            int tmp = myStoi(value); //ricevuto un valore percentuale
            this->vom->setValveOpBySerial(map(tmp, 0, 100, 0, MAX_POT_VALUE)); //lo immetto nella scala 1020
            break;
    }
}


// int* findAmountCommands(String comm){
//     int i = 0;
//     int amount = 0;
//     while (comm.charAt(i) != '\0') {
//         if (comm.charAt(i) == COMMAND_CHAR){
//             amount++;
//         }
//         i++;
//     }
//     int* res = nullptr;
//     int j = 0; i = 0;
//     if (amount > 0){
//         res = (int*)calloc(amount + 1, sizeof(int));
//         while (comm.charAt(i) != '\0') {
//             if (comm.charAt(i) == COMMAND_CHAR){
//                 res[j] = i;
//                 j++;
//             }
//             i++;
//         }
//         res[amount] = comm.length();
//     }
//     return res;
    
// }



void SerialManager::executeCommands(String comm){
    char command = comm.charAt(1);
    String value = comm.substring(3, comm.length());
    executeCommandByGui(command, value);
    
    //String remains = comm;
    //bool myFlag = true;
    

    // while (myFlag)
    // {
    //     int initIndex = remains.find(COMMAND_CHAR);
    //     myFlag = initIndex > 0;
    //     if (myFlag) {
    //         char command = comm.charAt(initIndex + 1);
    //         remains = remains.substring(initIndex + 2);
    //         int lastIndex = remains.find(COMMAND_CHAR);
    //         if (lastIndex < 0) {
    //             lastIndex = remains.length();
    //         }
    //         String value = comm.substring(remains.find(ARGUMENT_CHAR), lastIndex);
    //         executeCommandByGui(command, value);
    //         remains.substring(lastIndex);
    //     }
    //     /* code */
    // }
    
    //Serial.println("DIR_RECEVEID: " + comm);
    // unsigned int a = comm.length();
    // unsigned int i = 0;
    // String command = "";
    // String argument = "";
    // bool parsingCommand = true;
    // #ifdef DEBUG_IOMAN_WITHOUT_CONSOLE
    // Serial.print(comm); 
    // #endif
    // while(i<a || comm.charAt(i) != '\n') {
    //     char c = comm.charAt(i);
    //     switch (c)
    //     {
    //     case COMMAND_CHAR:
    //         if(command.length() > 0){
    //             //executeCommandByGui(command, argument);
    //             Serial.println(command + " : " + argument);
    //         }
    //         command = "";
    //         argument = "";
    //         parsingCommand = true;
    //         break;
        
    //     case ARGUMENT_CHAR:
    //         parsingCommand = false;
    //         break;

    //     default:
    //         parsingCommand ? command += c : argument += c;
    //         break;
    //     }
    //     i++;
    // }
    // Serial.println("LAST ONE: " + command + " : " + argument);
    // //executeCommandByGui(command, argument); //TODO: forse era un bug

}

