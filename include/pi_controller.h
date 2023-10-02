#include <stdint.h>
#include <analog_out.h>
#include <digital_out.h>
#include <digital_in.h>

#ifndef PI_CONTROLLER_H
#define PI_CONTROLLER_H

class PI_controller
{
public:
    PI_controller(Analog_out &m1, Analog_out &m2);

    void init(float omegaMax, float kp, float ti);
    float update(float ref, float actual);
    void updateSpeed(float omega);

    void setKp(float kp);
    void setTi(float ti);

private:
    Analog_out mM1;
    Analog_out mM2;

    float mKp;
    float mTi;
    float mError;
    float mOmegaMax; // rad/s

public:
    float duty;

};

#endif
