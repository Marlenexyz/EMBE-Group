#include <controller.h>
#include <analog_out.h>

#ifndef P_CONTROLLER_H
#define P_CONTROLLER_H

class P_controller :
    public Controller
{
public:
    P_controller(Analog_out &m1, Analog_out &m2);

    Controller::Type getType() override;

    void init(float omegaMax, float kp, float ti) override;
    float update(float ref, float actual) override;
    void updateSpeed(float duty) override;

    void setOmegaMax(float omegaMax) override;
    void setKp(float kp) override;
    void setTi(float ti) override;

private:
    Analog_out mM1;
    Analog_out mM2;

    float mOmegaMax; // rad/s
    float mKp;

};

#endif
