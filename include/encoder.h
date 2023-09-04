#include <digital_in.h>
#include <digital_out.h>

#ifndef ENCODER_H
#define ENCODER_H

class Encoder
{
    public:

        Encoder(Digital_in C1, Digital_in C2, Digital_out LED);
        unsigned int position();

    private:
    
        Digital_in mC1;
        Digital_in mC2;
        Digital_out mLED;

        bool lastState;
        bool currentState;
        unsigned int count;
    
};

#endif