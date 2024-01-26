#ifndef __MY_LCD_MONITOR__
#define __MY_LCD_MONITOR__

#include "config.h"
#include "Lcd.h"
#include "./task/Task.h"
#include "rgb_lcd.h"
#include "Arduino.h"

class MyLcdMonitor : public Lcd {
    public:
        MyLcdMonitor();
        void updateState();
        void updateActValv();
        void printOnLcd();

    private:
        void myPrint();
        String actString;
        rgb_lcd lcd;
};

#endif