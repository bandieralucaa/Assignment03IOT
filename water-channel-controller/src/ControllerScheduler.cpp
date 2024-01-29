#include "ControllerScheduler.h"

StateName actStat;
Task** tasks;
Cooldown* scheduleCooldown;
int actAmountTask;

unsigned long bPeriod;

ControllerScheduler::ControllerScheduler() {

    Potentiometer* p = new PotentiometerImpl(POT_PIN);

    MyLcdMonitor* lcd = new MyLcdMonitor();

    StateButtonInterupt* button = new StateButtonInterupt(BUTT_PIN, this); 

    //Serial.begin(9600);

    SerialManager* IOMan = new SerialManager();

    ValveOpeningManagement* VOM = new ValveOpeningManagement(p, IOMan);

    Valve* valv = new Valve(SERVO_MOTOR_PIN, false, IOMan, lcd, VOM);
    

    int amountTask = 0;
    tasks = new Task*[amountTask]{ //button
    //, IOMan, valve, VOM, button, VOM, 
    //, , 
    };
    actAmountTask = amountTask;

    // State* s1 = new AutomaticState(button, lcd);
    // State* s2 = new ManualState(button, lcd);
    
    // states = new State*[2]{s1, s2};
    
    actStat = START_STATE;
    // lcd->updateState(actStat);
    // lcd->updateActValv(-1);
    // delay(100);
    Serial.print("done creation of Controller");

}

void ControllerScheduler::init(unsigned long basePeriod) {
    bPeriod = basePeriod;
    scheduleCooldown = new Cooldown(basePeriod);
    scheduleCooldown->init();
}


#ifdef SCHEDULER_PERIOD_DEBUG
unsigned long t1 = 0;
#endif

bool interuptAppened() {

    #ifdef SCHEDULER_PERIOD_DEBUG
    unsigned long t2 = millis();
    unsigned long t3 = t2 - t1;
    Serial.print(" ");
    Serial.print(t3);
    Serial.print(" <-------------\n");
    t1 = t2;
    #endif

    int i;
    for(i=0; i < actAmountTask; i++) {
        // Serial.println(i);
        // Serial.println(actAmountTask);
        if (tasks[i]->updateAndCheckTime(bPeriod)){
            tasks[i]->tick();
        }
    }


    return true;
}

void ControllerScheduler::execute() {
    if (scheduleCooldown->isOver()) {
        interuptAppened();
        scheduleCooldown->reset();
    }
}

StateName ControllerScheduler::getActState(){
    return actStat;
}



void setNewState(StateName newState){
    actStat = newState;
    //states[actStat]->init();
    switch (actStat)
    {
        case AUTOMATIC_STATE:
            Serial.print("NEW STATE: AUTO");
            break;
        
        case MANUAL_STATE:
            Serial.print("NEW STATE: MANUAL");
            break;
    }
}