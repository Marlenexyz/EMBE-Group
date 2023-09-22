#include <P_controller.h>
#include <Arduino.h>

P_controller::P_controller(Analog_out& m1, Analog_out& m2):
    mM1(m1),
    mM2(m2)
{
}

void P_controller::init(float maxOmega, float kp)
{
    mMaxOmega = maxOmega;
    mKp = kp;

    mM1.init(2, 1, 0.5f);
    mM2.init(1, 1, 0.0f);
}

float P_controller::update(float ref, float actual)
{
    float error = ref - actual;
    float value = mKp * error;
    setSpeed(value);
    return value;
}

void P_controller::setSpeed(float omega)
{
    // max freq of f_update
    float duty = omega / mMaxOmega;
    Serial.print(", duty: ");
    Serial.println(duty);

    if(duty >= 1.0)
    {
        mM2.set_duty_cycle(0.0f);
        mM1.set_duty_cycle(0.999f);
    }
    else if (duty <= -1.0f)
    {
        mM1.set_duty_cycle(0.0f);
        mM2.set_duty_cycle(0.999f);
    }
    else if(duty >= 0)
    {
        mM2.set_duty_cycle(0.0f);
        mM1.set_duty_cycle(duty);
    }
    else if(duty < 0)
    {
        mM1.set_duty_cycle(0.0f);
        mM2.set_duty_cycle(duty);
    }
}
