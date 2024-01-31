#ifndef __CO__
#define __CO__

#include "CV.h"
#include "CM.h"
#include "config.h"

//this class help to unify the two interfaces that Controller have to implement

class ControllerObserver : public CV, public CM {
  public:
};

#endif