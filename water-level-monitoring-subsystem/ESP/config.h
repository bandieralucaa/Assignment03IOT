#ifndef __CONFIG__
#define __CONFIG__




///////////// pins

#define LED_O 23
#define LED_W 5
#define ECHO_P 2               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define TRIG_P 4               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN



/////////////// debug print
#define MYDEGUB
#ifdef MYDEGUB

#define NET_DEB
#define SONAR_DEBUG
#define NETTASK_DEBUG
#define ALIVE_TASK_DEBUG

#endif











////connection states

enum NetworkState{
  NOCONN,
  CONN
};

#endif 