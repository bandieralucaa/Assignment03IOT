#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

#define MAX_VALUE_PERCENTAGE_BAR 100 //TODO: VEDERE SE LASCIARE QUESTO VALORE



class Potentiometer {
    public:
        virtual int getPercentageValue() = 0;
};

#endif