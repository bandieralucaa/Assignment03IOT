#ifndef __MY_LCD_MONITOR__
#define __MY_LCD_MONITOR__

#include "config.h"
#include "Lcd.h"
#include "Task.h"
#include "rgb_lcd.h"
#include "Arduino.h"

class MyLcdMonitor : public Lcd {
    public:
        MyLcdMonitor();
        
        void updateState(StateName newState);
        void updateActValv(int newValvOp);

    private:
        //initialize the lcd
        void initLCD();

        //print the parameter on the lcd
        void printOnLcd(int who);
        
        rgb_lcd lcd;

        //it is saved into 0-100 scale
        int actValvOp;
        StateName actState;
        
};

#endif