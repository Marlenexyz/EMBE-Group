#include <digital_in.h>
#include <digital_out.h>
#include <analog_out.h>

#ifndef ENCODER_H
#define ENCODER_H

class Encoder
{
    public:
        Encoder(Digital_in& c1, Digital_in& c2, Analog_out& m1, Digital_out& m2);

        void init();
        int position();
        float getSpeed();
        //void setSpeed(float omega);

    private:
        Digital_in mC1;
        Digital_in mC2;

        Analog_out mM1;
        Digital_out mM2;

        float lastOmega;
        float crtOmega;

        unsigned long lastTime;
        unsigned long crtTime;

        static constexpr float maxOmega = 12.5; // rad/s
    
};

#endif
