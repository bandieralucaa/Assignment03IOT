#ifndef __CONFIG__
#define __CONFIG__

///////////// pins
#define LED_O 23
#define LED_W 5
#define ECHO_P 2 
#define TRIG_P 4 

/////////////// debug print
#define MYDEGUB
#ifdef MYDEGUB

#define NET_DEB
//#define SONAR_DEBUG
#define NETTASK_DEBUG
//#define ALIVE_TASK_DEBUG
//#define DEBUG_NOPANIC

#endif


//connection states
enum NetworkState{
  NOCONN,
  CONN
};

#endif 