#include <digital_in.h>
#include <digital_out.h>
#include <analog_out.h>

#ifndef ENCODER_H
#define ENCODER_H

class Encoder
{
public:
    Encoder(Digital_in &c1, Digital_in &c2);

    void init(float omegaMax);
    float getSpeed();
    unsigned long getTau();

private:
    Digital_in mC1;
    Digital_in mC2;

    float mOmega;
    float mOmegaMax; // rad/s

    unsigned long mLastTime;
    unsigned long mCrtTime;
};

#endif
