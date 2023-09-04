#include "encoder.h"
#include <avr/delay.h>

Encoder::Encoder(Digital_in C1, Digital_in C2, Digital_out LED)
    : mC1(C1)
    , mC2(C2)
    , mLED(LED)
{    
    count = 0;
    currentState = false;
    lastState = false;
    // gear ratio 1:100
     //Uhrzeigersinn:  00 10 11 01
     //Gegen Uhrzeigersinn: 00 01 11 10
}

unsigned int Encoder::position()
{
    currentState = mC1.is_hi();
    if ((lastState != currentState) && currentState) {
        count++;
        // Turn on LED
        mLED.set_hi();
    }
    else
    {
        // Turn off LED
        mLED.set_lo();
    }
    lastState = currentState;
    return count;
}