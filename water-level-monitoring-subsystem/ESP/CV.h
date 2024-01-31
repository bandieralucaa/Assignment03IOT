#ifndef __CV__
#define __CV__


class CV {
public:
    //Help the "NetworkView" to set a new frequence for the periodic sample
    virtual void setFreq(double newFreq) = 0;
};

#endif