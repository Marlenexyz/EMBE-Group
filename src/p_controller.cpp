#include <p_controller.h>
#include <Arduino.h>

P_controller::P_controller(Analog_out &m1, Analog_out &m2) :
    mM1(m1),
    mM2(m2),
    mKp(0.0f),
    mOmegaMax(0.0f),
    duty(0.0f)
{
}

void P_controller::init(float omegaMax, float kp)
{
    mOmegaMax = omegaMax;
    mKp = kp;

    // initialize all pins
    mM1.init(1, 1, 0.0f);
    mM2.init(2, 1, 0.0f);
}

float P_controller::update(float ref, float actual)
{
    // calculate new speed value
    float error = ref - actual;
    float value = mKp * error;
    updateSpeed(value);

    // return new speed value
    return value;
}

void P_controller::updateSpeed(float omega)
{
    duty = omega / mOmegaMax;

    if (duty >= 1.0)
    {
        duty = 1.0f;
        mM2.set_duty_cycle(0.0f);
        mM1.set_duty_cycle(0.999f);
    }
    else if (duty <= -1.0f)
    {
        duty = -1.0f;
        mM1.set_duty_cycle(0.0f);
        mM2.set_duty_cycle(0.999f);
    }
    else if (duty >= 0)
    {
        mM2.set_duty_cycle(0.0f);
        mM1.set_duty_cycle(duty);
    }
    else if (duty < 0)
    {
        mM1.set_duty_cycle(0.0f);
        mM2.set_duty_cycle(-duty);
    }
}
