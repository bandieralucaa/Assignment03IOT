#ifndef __CV__
#define __CV__


class CV {
public:
    //Help the "NetworkView" (NView) to set a new frequence for the periodic sample
    virtual void setFreq(unsigned long newFreq) = 0;
};

#endif