#include "analog_out.h"
#include <avr/io.h>

Analog_out::Analog_out(int pin) :
    timer(),
    pin(pin)
{

}

void Analog_out::init(int period_ms, float duty_cycle)
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

void Analog_out::set_duty_cycle(float duty_cycle)
{
    OCR1B = OCR1A * duty_cycle;
}
