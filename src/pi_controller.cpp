#include <pi_controller.h>

#include <Arduino.h>
#include <defines.h>

PI_controller::PI_controller(Analog_out &m1, Analog_out &m2) :
    mM1(m1),
    mM2(m2),
    mOmegaMax(0.0f),
    mKp(1.0f),
    mTi(1.0f)
{

}

Controller::Type PI_controller::getType()
{
    return Controller::Type::PI_CONTROLLER;
}

void PI_controller::init(float omegaMax, float kp, float ti)
{
    setOmegaMax(omegaMax);
    setKp(kp);
    setTi(ti);

    // initialize all pins
    mM1.init(1, 1, 0.0f);
    mM2.init(2, 1, 0.0f);
}

float PI_controller::update(float ref, float actual)
{
    static float error = 0.0f;

    // calculate new speed value
    float errorNew = ref - actual;
    error += errorNew;
    float value = mKp * (errorNew + 1 / mTi * error * static_cast<float>(UPDATE_RATE) / 1000.0f );
    float duty = value / mOmegaMax;
    updateSpeed(duty);

    // print values
    Serial.print("w_ref: ");
    Serial.print(ref);
    Serial.print(", w: ");
    Serial.print(actual);
    Serial.print(", duty: ");
    if (duty > 1.0f)
        Serial.println(1.0f);
    else if (duty < -1.0f)
        Serial.println(-1.0f);
    else
        Serial.println(duty);

    // return new speed value
    return value;
}

void PI_controller::updateSpeed(float duty)
{
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

void PI_controller::setOmegaMax(float omegaMax)
{
    mOmegaMax = omegaMax;
}

void PI_controller::setKp(float kp)
{
    mKp = kp;
}

void PI_controller::setTi(float ti)
{
    mTi = ti;
}
