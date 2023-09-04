#include <digital_in.h>
#include <digital_out.h>

#ifndef ENCODER_H
#define ENCODER_H

class Encoder
{
    public:
        Encoder(Digital_in& c1, Digital_in& c2, Digital_out& led);

        void init();
        unsigned int position();

    private:
        Digital_in mC1;
        Digital_in mC2;
        Digital_out mLed;

        bool mLastState;
        bool mCurrentState;
        unsigned int mCount;
    
};

#endif
