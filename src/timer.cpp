#include "timer.h"
#include <avr/io.h>

Timer::Timer()
{
    mNr = 0;
    mPrescaler = 0;
}

Timer::~Timer()
{
    mNr = 0;
    mPrescaler = 0;
}

void Timer::init(int nr, int prescaler, long frequency)
{
    mNr = nr;
    mPrescaler = prescaler;

    if(mNr == 0)
    {
        TCCR0A = 0;
        TCCR0B = 0;
        TCNT0 = 0;

        set_frequency(frequency);
        // Set CTC mode
        TCCR0A |= (1 << WGM01);
        // Enable interrupt
        TIMSK0 |= (1 << OCIE0A);
        // Set prescaler
        switch(mPrescaler)
        {
            case 1: TCCR0B |= (1 << CS00); break;
            case 8: TCCR0B |= (1 << CS01); break;
            case 64: TCCR0B |= (1 << CS01) | (1 << CS00); break;
            case 256: TCCR0B |= (1 << CS02); break;
            case 1024: TCCR0B |= (1 << CS02) | (1 << CS00); break;
            default: break;
        }
    }
    else if(mNr == 1)
    {
        TCCR1A = 0;
        TCCR1B = 0;
        TCNT1 = 0;

        set_frequency(frequency);
        // Set CTC mode
        TCCR1B |= (1 << WGM12);
        // Enable interrupt
        TIMSK1 |= (1 << OCIE1A);
        // Set prescaler
        switch(mPrescaler)
        {
            case 1: TCCR1B |= (1 << CS10); break;
            case 8: TCCR1B |= (1 << CS11); break;
            case 64: TCCR1B |= (1 << CS11) | (1 << CS10); break;
            case 256: TCCR1B |= (1 << CS12); break;
            case 1024: TCCR1B |= (1 << CS12) | (1 << CS10); break;
            default: break;
        }
    }
    else if(mNr == 2)
    {
        TCCR2A = 0;
        TCCR2B = 0;
        TCNT2 = 0;

        set_frequency(frequency);
        // Set CTC mode
        TCCR2A |= (1 << WGM21);
        // Enable interrupt
        TIMSK2 |= (1 << OCIE2A);
        // Set prescaler
        switch(mPrescaler)
        {
            case 1: TCCR2B |= (1 << CS20); break;
            case 8: TCCR2B |= (1 << CS21); break;
            case 64: TCCR2B |= (1 << CS21) | (1 << CS20); break;
            case 256: TCCR2B |= (1 << CS22); break;
            case 1024: TCCR2B |= (1 << CS22) | (1 << CS20); break;
            default: break;
        }
    }
}

void Timer::set_frequency(long frequency)
{
    if(mNr == 0)
    {
        OCR0A = cSYSTEM_FREQUENCY / frequency / mPrescaler - 1;
    }
    else if(mNr == 1)
    {
        OCR1A = cSYSTEM_FREQUENCY / frequency / mPrescaler - 1;
    }
    else if(mNr == 2)
    {
        OCR2A = cSYSTEM_FREQUENCY / frequency / mPrescaler - 1;
    }
}
