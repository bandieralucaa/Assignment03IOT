#include "ControllerScheduler.h"

StateName actStat;
Task** tasks;
Cooldown* scheduleCooldown;
int actAmountTask;

unsigned long bPeriod;
MyLcdMonitor* lcd;

ControllerScheduler::ControllerScheduler() {

    Potentiometer* p = new PotentiometerImpl(POT_PIN);

    lcd = new MyLcdMonitor();

    StateButtonInterupt* button = new StateButtonInterupt(BUTT_PIN, this); 
    
    //Serial.begin(9600);

    ValveOpeningManagement* VOM = new ValveOpeningManagement(p);

    SerialManager* IOMan = new SerialManager(VOM);

    Valve* valv = new Valve(SERVO_MOTOR_PIN, false, IOMan, lcd, VOM);
    

    int amountTask = 0;
    tasks = new Task*[amountTask]{
        // VOM, IOMan, valv
        };
    actAmountTask = amountTask;

    for(int i=0; i < actAmountTask; i++) {
        tasks[i]->setObs(this);
    }

    // State* s1 = new AutomaticState(button, lcd);
    // State* s2 = new ManualState(button, lcd);
    
    // states = new State*[2]{s1, s2};
    
    actStat = START_STATE;
    lcd->updateState(actStat);
    lcd->updateActValv(-1);
    delay(100);
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



void ControllerScheduler::setNewState(StateName newState){
    actStat = newState;
    switch (actStat)
    {
        case AUTOMATIC_STATE:
            Serial.print("NEW STATE: AUTO");
            lcd->updateState(AUTOMATIC_STATE);
            break;
        
        case MANUAL_STATE:
            Serial.print("NEW STATE: MANUAL");
            lcd->updateState(MANUAL_STATE);
            break;
    }
}