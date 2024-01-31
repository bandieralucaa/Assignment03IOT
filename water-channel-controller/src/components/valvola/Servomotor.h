#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

class Servomotor {
    public:
        //set the position of the servomotor
        virtual void setPos(int newPos) = 0;

        //get the position of the servomotor
        virtual int getActPos() = 0;
};

#endif