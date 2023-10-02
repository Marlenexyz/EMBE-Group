#include <pi_controller.h>
#include <defines.h>

PI_controller::PI_controller(Analog_out &m1, Analog_out &m2) :
    mM1(m1),
    mM2(m2),
    mKp(0.0f),
    mTi(0.0f),
    mError(0.0f),
    mOmegaMax(0.0f),
    duty(0.0f)
{
}

void PI_controller::init(float omegaMax, float kp, float ti)
{
    mOmegaMax = omegaMax;
    mKp = kp;
    mTi = ti;

    // initialize all pins
    mM1.init(1, 1, 0.0f);
    mM2.init(2, 1, 0.0f);
}

float PI_controller::update(float ref, float actual)
{
    // calculate new speed value
    float error = ref - actual;
    mError += error;
    float value = mKp * (error + 1 / mTi * mError * static_cast<float>(UPDATE_RATE) / 1000.0f );
    updateSpeed(value);

    // return new speed value
    return value;
}

void PI_controller::updateSpeed(float omega)
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

void PI_controller::setKp(float kp)
{
    mKp = kp;
}

void PI_controller::setTi(float ti)
{
    mTi = ti;
}
