#include <digital_in.h>
#include <digital_out.h>
#include <analog_out.h>

#ifndef ENCODER_H
#define ENCODER_H

class Encoder
{
    public:
        Encoder(Digital_in& c1, Digital_in& c2);

        void init(float maxOmega);
        float getSpeed();
        unsigned long getTau();

    private:
        Digital_in mC1;
        Digital_in mC2;

        float omega;
        float mMaxOmega; // rad/s

        unsigned long lastTime;
        unsigned long crtTime;

    
};

#endif
