#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

class Servomotor {
    public:
        virtual void setPos(int newPos) = 0;
        virtual int getActPos() = 0;
};

#endif