#ifndef __IN_RECEIVER__
#define __IN_RECEIVER__

class InReceiver {
    public:
        virtual int getParsedValveOpening() = 0;
        virtual int getHourModApertura() = 0;
};

#endif