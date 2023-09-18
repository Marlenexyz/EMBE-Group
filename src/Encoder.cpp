#include "encoder.h"
#include <Arduino.h>

Encoder::Encoder(Digital_in& c1, Digital_in& c2, Analog_out& m1, Digital_out& m2) :
    mC1(c1),
    mC2(c2),
    mM1(m1),
    mM2(m2)
{

}

void Encoder::init()
{
    lastOmega = 0.0;
    crtOmega = 0.0;

    lastTime = 0;
    crtTime = 0;

    mM1.set_duty_cycle(0.0);
    mM2.set_lo();


    // gear ratio 1:100
    // number of mirrors 14
    // C1C2 clockwise:        00 10 11 01
    // C1C2 counterclockwise: 00 01 11 10
}

int Encoder::position()
{
    return 0;
}

float Encoder::getSpeed()
{
    crtTime = micros();

    if(lastTime > 0)
    {
        unsigned long period = crtTime - lastTime;
        crtOmega = 2.0f * 3.1415926535f / (static_cast<float>(period) * 700.0f / 1000000.0f );


        // if(omega >= 0.63 * maxOmega)
        // {
        //     float time = micros();
        //     Serial.println(time - firstCycle);
        //     delay(100000000);
        // }
    }

    if(mC2.is_hi())
    {
        crtOmega = -crtOmega;
    }

    lastTime = crtTime;
    return crtOmega;
}

void Encoder::setSpeed(float omega)
{
    // max freq of f_update
    float duty = omega / maxOmega;
    if(duty > 1.0)
    {
        mM2.set_lo();
        mM1.set_duty_cycle(0.99); // fix this PWM duty = 1,0f
    }
    else if (duty < -1.0f)
    {
        
    }
    else if(duty >= 0)
    {
        mM2.set_lo();
        mM1.set_duty_cycle(duty);
    }
    else if(duty < 0)
    {

    }
}
