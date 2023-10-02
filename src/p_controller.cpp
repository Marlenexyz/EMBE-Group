#include <p_controller.h>
#include <Arduino.h>

P_controller::P_controller(Analog_out &m1, Analog_out &m2, Digital_in& button, Digital_out& sleep) :
    mM1(m1),
    mM2(m2),
    mButton(button),
    mSleep(sleep)
{
}

void P_controller::init(float omegaMax, float kp)
{
    mOmegaMax = omegaMax;
    mKp = kp;

    // initialize all pins
    mM1.init(1, 1, 0.0f);
    mM2.init(2, 1, 0.0f);
    mButton.init();
    mSleep.init();

    // set H-bridge to active
    mSleep.set_hi();
}

float P_controller::update(float ref, float actual)
{
    // calculate new speed value
    float error = ref - actual;
    float value = mKp * error;
    updateSpeed(value);

    // check if emergency button is pressed
    updateBrake();

    // return new speed value
    return value;
}

void P_controller::updateSpeed(float omega)
{
    // max freq of f_update
    float duty = omega / mOmegaMax;
    Serial.print(", duty: ");
    Serial.println(duty);

    if (duty >= 1.0)
    {
        mM2.set_duty_cycle(0.0f);
        mM1.set_duty_cycle(0.999f);
    }
    else if (duty <= -1.0f)
    {
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
        mM2.set_duty_cycle(duty);
    }
}

void P_controller::updateBrake()
{
    if (mButton.is_lo())
    {
        mSleep.set_lo();
    }
}
