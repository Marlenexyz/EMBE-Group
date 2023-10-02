#include <stdint.h>
#include <analog_out.h>
#include <digital_out.h>
#include <digital_in.h>

#ifndef P_CONTROLLER_H
#define P_CONTROLLER_H

class P_controller
{
public:
    P_controller(Analog_out &m1, Analog_out &m2);

    void init(float omegaMax, float kp);
    float update(float ref, float actual);
    void updateSpeed(float duty);

    void setKp(float kp);

private:
    Analog_out mM1;
    Analog_out mM2;

    float mKp;
    float mOmegaMax; // rad/s

};

#endif
