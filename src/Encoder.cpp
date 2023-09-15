#include "encoder.h"

Encoder::Encoder(Digital_in& c1, Digital_in& c2) :
    mC1(c1),
    mC2(c2)
{

}

void Encoder::init()
{
    mCount = 0;
    mCrtC1 = false;
    mCrtC2 = false;
    mLastC1 = false;
    mLastC2 = false;

    // gear ratio 1:100
    // number of mirrors 14
    // C1C2 clockwise:        00 10 11 01
    // C1C2 counterclockwise: 00 01 11 10
}

int Encoder::position()
{
    // Measure current C1 and C2 state
    // mCrtC1 = mC1.is_hi();
    // mCrtC2 = mC2.is_hi();

    // if(mCrtC1 && mCrtC2)
    // {
    //     if(mLastC1 && !mLastC2)
    //     {
    //         mCount++;
    //         mLed.set_hi();
    //     }
    //     else if(!mLastC1 && mLastC2)
    //     {
    //         mCount--;
    //         mLed.set_hi();
    //     }
    // }
    // else
    // {
    //     // Turn off LED
    //     mLed.set_lo();
    // }

    // // Save new C1 and C2 state
    // mLastC1 = mCrtC1;
    // mLastC2 = mCrtC2;

    // return mCount;
    return 0;
}
