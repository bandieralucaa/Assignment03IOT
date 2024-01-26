#ifndef __IN_RECEIVER__
#define __IN_RECEIVER__

class InReceiver {
    public:
        virtual int getParsedValveOpening() = 0;
        virtual String getHourModApertura() = 0;
};

#endif