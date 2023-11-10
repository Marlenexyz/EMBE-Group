#include "encoder.h"
#include <Arduino.h>
#include <avr/io.h>

Encoder::Encoder(Digital_in &c1, Digital_in &c2) :
    mC1(c1),
    mC2(c2)
{
}

void Encoder::init(float mOmegaMax)
{
    // gear ratio 1:100
    // number of mirrors 14
    // C1C2 clockwise:        00 10 11 01
    // C1C2 counterclockwise: 00 01 11 10

    mOmega = 0.0;
    mOmegaMax = mOmegaMax;

    mLastTime = 0;
    mCrtTime = 0;

    // Initialize C2 as GPIO
    mC2.init();

    // Initialize C1 as externial trigger for rising edges
    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2);
    EICRA |= (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0);
    sei();
}

float Encoder::getSpeed()
{
    mCrtTime = micros();

    if (mLastTime > 0)
    {
        unsigned long period = mCrtTime - mLastTime;
        mOmega = 2.0f * 3.1415926535f / (static_cast<float>(period) * 700.0f / 1000000.0f);
    }

    if (mC2.is_hi())
    {
        mOmega = -mOmega;
    }

    mLastTime = mCrtTime;
    return mOmega;
}

unsigned long Encoder::getTau()
{
    static unsigned long startTime = micros();
    mCrtTime = micros();

    if (mLastTime > 0)
    {
        unsigned long period = mCrtTime - mLastTime;
        mOmega = 2.0f * 3.1415926535f / (static_cast<float>(period) * 700.0f / 1000000.0f);
        // Serial.print("rps: ");
        // Serial.print(1 / (static_cast<float>(period) * 700.0f / 1000000.0f));

        if (mOmega >= 0.63 * mOmegaMax)
        {
            return mCrtTime - startTime;
        }
    }

    mLastTime = mCrtTime;
    return 0;
}