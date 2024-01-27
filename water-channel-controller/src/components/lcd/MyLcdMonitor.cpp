#include "MyLcdMonitor.h"


#include <Arduino.h>


#define AMOUNT_COLS 16
#define AMOUNT_ROWS 2

#define EMPTY_CHAR " "
#define DEFAULT_STAT "STATE: "
#define DEFAULT_VALV "VALVE OP.: "
#define AMOUNT_INFO 2

// char* infos[AMOUNT_INFO] = {DEFAULT_STAT, DEFAULT_VALV};
int indexMapper[AMOUNT_ROWS] = {0, (AMOUNT_ROWS/2)}; //la i-esima informazione alla i-esima riga dello schermo LCD
int sizeMapper[AMOUNT_INFO] = {7, 11}; //inizio a stampare dalla j-esima colonna della i-esima riga della i-esima informazione

MyLcdMonitor::MyLcdMonitor(){
    this->lcd.begin(AMOUNT_COLS, AMOUNT_ROWS);
    //initProgBar();
    this->lcd.display();
    this->initLCD();
    //this->goBackNormal();
}

void MyLcdMonitor::initLCD(){
    for (int i = 0; i < AMOUNT_INFO; i++) {
        this->lcd.setCursor(0, indexMapper[i]);
        this->lcd.print((i == 0) ? DEFAULT_STAT : DEFAULT_VALV);
    }   
}

void MyLcdMonitor::updateState(StateName newState){
    this->actState = newState;
    this->printOnLcd(0);
}

void MyLcdMonitor::updateActValv(int newValvOp){
    this->actValvOp = newValvOp;
    this->printOnLcd(1);
}

void MyLcdMonitor::printOnLcd(int who) {
    this->lcd.setCursor(1,3);//sizeMapper[who],indexMapper[who]);
    switch (who)
    {
        case 0:
            switch (this->actState)
            {
                case AUTOMATIC_STATE:
                    this->lcd.print("AUTO");
                    break;
                case MANUAL_STATE:
                    this->lcd.print("MAN");
                    break;
                default:
                    break;
            }    
            break;
        
        case 1:
            this->lcd.print(this->actValvOp);
            this->lcd.print("%");
    
        default:
            break;
    }

}


// int actValvOp;
// StateName actState;



// // void initProgBar(){
// //     int i;
// //     for (i=0; i<AMOUNT_BARS;i++){
// //       char c = EMPTY_CHAR;
// //       progressBar[i] = c;
// //     }
// // }



// void MyLcdMonitor::myPrint(){
//     int i,j;
//     for (i = 0; i<AMOUNT_ROWS; i++){
//         this->lcd.setCursor(0,i);
//         for(j=0; j<AMOUNT_COLS; j++){
//             char c = this->actString[i*(AMOUNT_COLS)+j];
//             if (c != '\0'){
//                 this->lcd.print(c);
//             } else {
//                 i=AMOUNT_ROWS;
//                 j=AMOUNT_COLS;
//             }
//         }
//     }
// }

// void MyLcdMonitor::writeOnLcd(String toWrite){
//     this->lcd.clear();
//     this->actString = toWrite;
//     this->lcd.setCursor(0,0);
//     this->myPrint();
// }

// void MyLcdMonitor::clear(){
//     this->lcd.clear();
// }

// void MyLcdMonitor::turnOn(){
//     this->lcd.display();
// }
// void MyLcdMonitor::turnOff(){
//     this->lcd.noDisplay();
// }

// void MyLcdMonitor::raiseError(){
//     this->lcd.setRGB(255,0,0); //ColorR, colorG, colorB
// }

// void MyLcdMonitor::goBackNormal(){
//     this->lcd.setRGB(0,255,0);
// }

// int lastIndex = 0;

// bool MyLcdMonitor::changeProgBar(int percentage){
//     bool res = false;
//     int amount = (int) ((percentage *1.0)  * (((AMOUNT_BARS)*1.0) / ((MAX_VALUE_PERCENTAGE_BAR)*1.0)));
//     #ifdef LCD_DEBUG
//     Serial.print(" " + (String) amount + " / ");
//     #endif
//     if (amount != lastIndex){
//         int i; 
        
//         for (i = 0; i<amount; i++){
//             progressBar[i] = FULL_CHAR;
//         }
        
//         for (i = amount; i < (AMOUNT_BARS + 0); i++){
//             progressBar[i] = EMPTY_CHAR;
//         }
//         res = true;
//     }
//     lastIndex = amount;
//     return res;
// }

// void MyLcdMonitor::printProgBar() {
//     this->lcd.setCursor(PROG_BAR_COLS + START_BAR_INDEX, PROG_BAR_ROW);
//     int i;
//     for (i=0; i<AMOUNT_BARS; i++){
//         this->lcd.print(progressBar[i]);
//     }
// }

// void MyLcdMonitor::initProgBar() {
//     this->lcd.setCursor(PROG_BAR_COLS, PROG_BAR_ROW);
//     this->lcd.print(INIT_BAR);
//     this->lcd.setCursor(AMOUNT_COLS-1, PROG_BAR_ROW);
//     this->lcd.print(FINISH_BAR);
// }

