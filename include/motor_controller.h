#include <controller.h>
#include <p_controller.h>
#include <pi_controller.h>

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

class Motor_controller :
    public Controller
{
public:
    Motor_controller(Analog_out &m1, Analog_out &m2);

    void setController(Controller::Type type);

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
    P_controller mP_controller;
    PI_controller mPI_controller;

    Controller* mController;

    float mOmegaMax; // rad/s
    float mKp;
    float mTi;

};

#endif
