#include "encoder.h"

Encoder::Encoder(Digital_in& c1, Digital_in& c2, Digital_out& led) :
    mC1(c1),
    mC2(c2),
    mLed(led)
{

}

void Encoder::init()
{
    mCount = 0;
    mCurrentState = false;
    mLastState = false;

    // gear ratio 1:100
    // number of mirrors 14
    // C1C2 clockwise:        00 10 11 01
    // C1C2 counterclockwise: 00 01 11 10
}

unsigned int Encoder::position()
{
    // Measure current C1 state
    mCurrentState = mC1.is_hi();

    if ((mLastState != mCurrentState) && mCurrentState) {
        // Turn on LED
        mLed.set_hi();
        // Count + 1
        mCount++;
    }
    else
    {
        // Turn off LED
        mLed.set_lo();
    }

    // Save new C1 state
    mLastState = mCurrentState;

    return mCount;
}
