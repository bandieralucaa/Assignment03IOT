#ifndef __CONFS__
#define __CONFS__

enum StateName {
    NONE = -1,
    AUTOMATIC_STATE,
    MANUAL_STATE
};

#define START_STATE AUTOMATIC_STATE
#define START_VALVE_OP 50


/* ### WIRING CONFIGS ### */

#define BUTT_PIN 2

#define SERVO_MOTOR_PIN 9

#define POT_PIN A0



/* ### ### ### ### ### ### ### ### */


/* ### TASK VARIABLE ### */

//#define IDEALLY_TIME (150)

#define SCHEDULE_BASE_PERIOD (200)

#define VALVE_OPENER_PERIOD 600 //1000
#define IOMAN_PERIOD 600 //2000
#define SERVO_MOTOR_PERIOD 400
//#define BUTTON_PERIOD 300

/* ### ### ### ### ### ### ### ### */


/* ### DEBUGGING VARIABLE ### */

#define DEBUG
#ifdef DEBUG

//#define SCHEDULER_INIT_PHASE

// #define SCHEDULER_PERIOD_DEBUG 



// #define LCD_DEBUG

//#define BUTTON_DEBUG

// #define DEBUG_IOMAN_WITHOUT_CONSOLE

// #define SONAR_DEBUG_LEFTING
#define POT_DEBUG

// #define STATE_CHANGE_DEBUG //TODO, quasi

// #define S_DEGUB

#endif


/* ### ### ### ### ### ### ### */


#endif
