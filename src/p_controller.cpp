#include <p_controller.h>

#include <Arduino.h>

P_controller::P_controller(Analog_out &m1, Analog_out &m2) :
    mM1(m1),
    mM2(m2),
    mOmegaMax(0.0f),
    mKp(1.0f)
{

}

Controller::Type P_controller::getType()
{
    return Controller::Type::P_CONTROLLER;
}

void P_controller::init(float omegaMax, float kp, float ti)
{
    setOmegaMax(omegaMax);
    setKp(kp);
    setTi(ti);

    // initialize all pins
    mM1.init(1, 1, 0.0f);
    mM2.init(2, 1, 0.0f);
}

float P_controller::update(float ref, float actual)
{
    // calculate new speed value
    float error = ref - actual;
    float value = mKp * error;
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

void P_controller::updateSpeed(float duty)
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

void P_controller::setOmegaMax(float omegaMax)
{
    mOmegaMax = omegaMax;
}

void P_controller::setKp(float kp)
{
    mKp = kp;
}

void P_controller::setTi(float ti)
{
    // no Ti required for P_controller
}
