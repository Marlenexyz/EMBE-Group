#include "pwm.h"
#include <avr/io.h>

Pwm::Pwm()
{
    mNr = 0;
    mPrescaler = 0;
}

Pwm::~Pwm()
{
    mNr = 0;
    mPrescaler = 0;
}

void Pwm::init(int nr, int prescaler, float duty_cycle)
{
    mNr = nr;
    mPrescaler = prescaler;

    if(mNr == 0) // PD6
    {
        TCCR0A = 0;
        TCCR0B = 0;
        TCNT0 = 0;

        // Set output mode
        DDRD |= (1 << DDD6);
        // Set fast PWM mode
        TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
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
    else if(mNr == 1) // PD5
    {
        TCCR1A = 0;
        TCCR1B = 0;
        TCNT1 = 0;

        // Set output mode
        DDRD |= (1 << DDD5);
        // Set fast PWM mode
        TCCR1A |= (1 << COM1A1) | (1 << WGM10);
        TCCR1B |= (1 << WGM12);
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
}

void Pwm::set_duty_cycle(float duty_cycle)
{
    int count = duty_cycle * 255;

    if(mNr == 0)
    {
        OCR0A = count;
    }
    else if(mNr == 1)
    {
        OCR1A = count;
    }
}
