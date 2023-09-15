#include "timer_msec.h"
#include <avr/io.h>

Timer_msec::Timer_msec()
{

}

void Timer_msec::init(int period_ms)
{
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    OCR1A = 16000000 / 1024 * period_ms / 1000 - 1;
    TCCR1B |= (1 << WGM12);
    TIMSK1 |= (1 << OCIE1A);
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

void Timer_msec::init(int period_ms, float duty_cycle)
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

void Timer_msec::set_duty_cycle(float duty_cycle)
{
    OCR1B = OCR1A * duty_cycle;
}
