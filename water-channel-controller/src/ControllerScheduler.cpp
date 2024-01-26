#include "ControllerScheduler.h"

StateName actStat;
State** states;
Task** tasks;
Cooldown* scheduleCooldown;
int actAmountTask;

unsigned long bPeriod;

ControllerScheduler::ControllerScheduler() {
    
    Potentiometer* p = new PotentiometerImpl(POT_PIN);


    StateButton* button = new StateButton(BUTT_PIN);

    SerialManager* IOMan = new SerialManager();

    ValveOpeningManagement* VOM = new ValveOpeningManagement(p, IOMan);

    Valve* valv = new Valve(SERVO_MOTOR_PIN, false);
    
    //MyLcdMonitor* lcd = new MyLcdMonitor();



    int amountTask = 4;
    tasks = new Task*[amountTask]{button, valv, VOM, IOMan };
    actAmountTask = amountTask;


    State* s1 = new AutomaticState(button);
    State* s2 = new ManualState(button);
    
    states = new State*[2]{s1, s2};
    
    actStat = AUTOMATIC_STATE;
    states[actStat]->init();
}

void ControllerScheduler::init(unsigned long basePeriod) {
    bPeriod = basePeriod;
    scheduleCooldown = new Cooldown(SCHEDULE_BASE_PERIOD);
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

    StateName newState = states[actStat]->changeState();
    if (newState != NONE) {
        actStat = newState;
        for(i=0; i < actAmountTask; i++) {
            tasks[i]->stop();
        }
        states[actStat]->init();
    }
    
    return true;
}

void ControllerScheduler::execute() {
    if (scheduleCooldown->isOver()) {
        interuptAppened();
        scheduleCooldown->reset();
    }
}



