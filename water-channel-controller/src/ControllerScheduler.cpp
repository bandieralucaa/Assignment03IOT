#include "ControllerScheduler.h"

StateName actStat;
State** states;
Task** tasks;
Cooldown* scheduleCooldown;
int actAmountTask;

unsigned long bPeriod;

ControllerScheduler::ControllerScheduler() {

    
    Potentiometer* p = new PotentiometerImpl(POT_PIN);

    MyLcdMonitor* lcd = new MyLcdMonitor();


    StateButton* button = new StateButton(BUTT_PIN); 

    //Serial.begin(9600);
    SerialManager* IOMan = new SerialManager(((ControllerSchedulerObserver*)(this)));

    ValveOpeningManagement* VOM = new ValveOpeningManagement(p, IOMan);

    Valve* valv = new Valve(SERVO_MOTOR_PIN, false, IOMan, lcd, VOM);
    

    int amountTask = 1;
    tasks = new Task*[amountTask]{ VOM
    //, IOMan, valve, VOM, button
    //, , 
    };
    actAmountTask = amountTask;


    State* s1 = new AutomaticState(button, lcd);
    State* s2 = new ManualState(button, lcd);
    
    states = new State*[2]{s1, s2};
    
    actStat = MANUAL_STATE;
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

int amount = 10;
int counter = 0;

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

    StateName newState = states[actStat]->changeState();
    if (newState != NONE) {
        actStat = newState;
        // for (i = 0; i < actAmountTask; i++) {
        //     tasks[i]->stop();
        // }
        states[actStat]->init();
    }
    
    counter++;
    if(amount == counter){
        Serial.print("STATE: ");
        Serial.print((actStat == MANUAL_STATE) ? "M" : "A");
        counter = 0;
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

