#ifndef __CONFS__
#define __CONFS__

/* ### WIRING CONFIGS ### */

#define BUTT_PIN 4

#define POT_PIN 100

#define SERVO_MOTOR_PIN 9

/* ### ### ### ### ### ### ### ### */


/* ### TASK VARIABLE ### */

#define IDEALLY_TIME (150)

#define SCHEDULE_BASE_PERIOD (150)

#define PIR_PERIOD 150
#define LED_BLINKING_PERIOD 150
#define SERVO_MOTOR_PERIOD 300
#define BUTTON_PERIOD 150
#define SONAR_PERIOD 450
#define TEMP_PERIOD 150
#define IOMAN_PERIOD 1050

#define BLINK_DELTA_1 (BLINK_DELTA_2*5)
#define BLINK_DELTA_2 (30)

/* ### ### ### ### ### ### ### ### */

/* ### REQUEST VARIABLE ### */

#define N1_TIME 3000
#define N2_TIME 3000
#define N3_TIME 9000
#define N4_TIME 3000

/* ### ### ### ### ### ### ### ### */



/* ### STRING TO LCD ### */

#define WELCOME_STRING "Welcome"
#define PRE_ENTERING_STRING "Proceed to the Washing Area"
#define WAITING_STRING "Ready to Wash"
#define PRE_WASHING_DONE_STRING "Washing complete, you can leave the area"
#define ERROR_STRING "Detected a Problem - Please Wait"

/* ### ### ### ### ### ### ### ### */

/* ### STRING TO GUI ### */

#define STATE1 "1"
#define STATE2 "2"
#define STATE3 "3"
#define STATE4 "4"
#define STATE5 "5"
#define STATE6 "6"

/* ### ### ### ### ### ### ### ### */


/* ### DEBUGGING VARIABLE ### */

//#define DEBUG
#ifdef DEBUG

//#define SCHEDULER_INIT_PHASE
//#define SCHEDULER_PERIOD_DEBUG 

//#define PIR_DEBUG //valuta se eliminarmi
//#define SERVO_MOTOR_DEBUG
//#define SONAR_DEBUG
//#define TEMP_DEBUG
//#define LCD_DEBUG

//#define DEBUG_IOMAN_WITHOUT_CONSOLE

//#define SONAR_DEBUG_LEFTING

//#define STATE_CHANGE_DEBUG //TODO, quasi

//#define S_DEGUB

#endif


/* ### ### ### ### ### ### ### */


#endif
