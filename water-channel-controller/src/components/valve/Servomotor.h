#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

class Servomotor {
    public:
        //get the position of the servomotor
        virtual int getActPos() = 0;
};

#endif