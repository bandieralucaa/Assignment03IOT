#include "ControllerScheduler.h"


Task** tasks;
Cooldown* scheduleCooldown;
int actAmountTask;

unsigned long bPeriod;
MyLcdMonitor* lcd;
StateName lastState = START_STATE;

ControllerScheduler::ControllerScheduler() {

    ControllerSchedulerObserver* myObs = new ControllerSchedulerObserver(START_STATE);
    this->myObs = myObs;

    Potentiometer* p = new PotentiometerImpl(POT_PIN);

    lcd = new MyLcdMonitor();

    new StateButtonInterupt(BUTT_PIN, this->myObs); 

    ValveOpeningManagement* VOM = new ValveOpeningManagement(p);

    SerialManager* IOMan = new SerialManager(VOM);
    IOMan->init();

    Valve* valv = new Valve(SERVO_MOTOR_PIN, false, IOMan, lcd, VOM);
    

    int amountTask = 3;
    tasks = new Task*[amountTask]{ VOM,  valv, IOMan};
    actAmountTask = amountTask;

    for(int i=0; i < actAmountTask; i++) {
        tasks[i]->setObs(this->myObs);
    }
    
    lcd->updateState(lastState);
    lcd->updateActValv(START_VALVE_OP);
    delay(100);

    #ifdef SCHEDULER_PRINT_DEBUG
    Serial.print("done creation of Controller");
    #endif

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
        this->setNewState(this->myObs->getActState());
    }
}

StateName ControllerScheduler::getActState(){
    return lastState;
}


void ControllerScheduler::setNewState(StateName newState) {
    if(lastState == newState) {
        return;
    } 

    lastState = newState;
    this->myObs->setNewState(newState);
    switch (lastState)
    {
        case AUTOMATIC_STATE:
            #ifdef SCHEDULER_PRINT_DEBUG
            Serial.print("NEW STATE: AUTO");
            #endif
            lcd->updateState(AUTOMATIC_STATE);
            break;
        
        case MANUAL_STATE:
            #ifdef SCHEDULER_PRINT_DEBUG
            Serial.print("NEW STATE: MANUAL");
            #endif
            lcd->updateState(MANUAL_STATE);
            break;
        default:
            break;
    }
}