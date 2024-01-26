#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

class Servomotor {
    public:
    virtual void setPos() = 0;
    virtual int getActPos() = 0;
};

#endif