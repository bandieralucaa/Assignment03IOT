#include "MyLcdMonitor.h"

#include <Arduino.h>
#include "math.h"

#define AMOUNT_COLS 16
#define AMOUNT_ROWS 2

#define EMPTY_CHAR " "
#define DEFAULT_STAT "STATE: "
#define DEFAULT_VALV "VALVE OP.: "
#define AMOUNT_INFO 2

int indexMapper[AMOUNT_ROWS] = {0, (AMOUNT_ROWS/2)}; //la i-esima informazione alla i-esima riga dello schermo LCD
int sizeMapper[AMOUNT_INFO] = {7, 11}; //inizio a stampare dalla j-esima colonna della i-esima riga della i-esima informazione

MyLcdMonitor::MyLcdMonitor() {
    this->lcd.begin(AMOUNT_COLS, AMOUNT_ROWS);
    this->lcd.display();
    this->initLCD();
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
    this->actValvOp = map(newValvOp, 0, MAX_POT_VALUE, 0, 100);
    this->printOnLcd(1);
}

void MyLcdMonitor::printOnLcd(int who) {
    this->lcd.setCursor(sizeMapper[who],indexMapper[who]);
    switch (who)
    {
        case 0:
            switch (this->actState)
            {
                case AUTOMATIC_STATE:
                    this->lcd.print(LCD_AUTO_STRING);
                    break;
                case MANUAL_STATE:
                    this->lcd.print(LCD_MANUAL_STRING);
                    break;
                default:
                    this->lcd.print("ERR"); //debug choise, ma dovrebbe essere impossibile
                    break;
            }    
            this->lcd.print("   ");
            break;
        
        case 1:
            int ok = this->actValvOp; // map(tmp, MIN_ANGLE_SERVO, MAX_ANGLE_SERVO, 0, 100);//((int) ( (((tmp)*(1.0))/((MAX_ANGLE_SERVO)*(1.0))) * (100.0) ));
            this->lcd.print(ok);
            this->lcd.print("%");
            for(int i = ((int)(floor(log10(this->actValvOp * 1.0)))); i < 2 ; i++) {
                this->lcd.print(" ");
            }
    }

}

