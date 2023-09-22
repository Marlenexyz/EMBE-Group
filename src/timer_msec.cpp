#include "timer_msec.h"
#include <avr/io.h>

Timer_msec::Timer_msec()
{

}

void Timer_msec::init(int nr, int period_ms)
{
    mNr = nr;

    if(mNr == 2)
    {
        TCCR2A = 0;
        TCCR2B = 0;
        TCNT2 = 0;

        OCR2A = 16000000 / 1024 * period_ms / 1000 - 1;
        TCCR2A |= (1 << WGM21);
        TIMSK2 |= (1 << OCIE2A);
        TCCR2B |= (1 << CS22) | (1 << CS20);
    }
    else if(mNr == 1)
    {
        TCCR1A = 0;
        TCCR1B = 0;
        TCNT1 = 0;

        OCR1A = 16000000 / 1024 * period_ms / 1000 - 1;
        TCCR1B |= (1 << WGM12);
        TIMSK1 |= (1 << OCIE1A);
        TCCR1B |= (1 << CS12) | (1 << CS10);
    }
}

void Timer_msec::init(int nr, int period_ms, float duty_cycle)
{
    mNr = nr;

    if(mNr == 2)
    {
        TCCR2A = 0;
        TCCR2B = 0;
        TCNT2 = 0;

        OCR2A = 16000000 / 1024 * period_ms / 1000 - 1;
        OCR2B = OCR2A * duty_cycle;
        TCCR2A |= (1 << WGM21);
        TIMSK2 |= (1 << OCIE2A);
        TIMSK2 |= (1 << OCIE2B);
        TCCR2B |= (1 << CS22) | (1 << CS20);
    }
    else if(mNr == 1)
    {
        TCCR1A = 0;
        TCCR1B = 0;
        TCNT1 = 0;

        OCR1A = 16000000 / 1024 * period_ms / 1000 - 1;
        OCR1B = OCR1A * duty_cycle;
        TCCR1B |= (1 << WGM12);
        TIMSK1 |= (1 << OCIE1A);
        TIMSK1 |= (1 << OCIE1B);
        TCCR1B |= (1 << CS12) | (1 << CS10);
    }
}

void Timer_msec::set_duty_cycle(float duty_cycle)
{
    if(mNr == 2)
    {
        OCR2B = OCR2A * duty_cycle;
    }
    else if(mNr == 1)
    {
        OCR1B = OCR1A * duty_cycle;
    }
}
