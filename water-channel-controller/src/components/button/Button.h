#ifndef __BUTTON__
#define __BUTTON__

class Button {
    public:
        virtual StateName buttonState() = 0;
};

#endif