#include "digital_out.h"
#include <avr/io.h>

Digital_out::Digital_out(int pin)
{
    pinMask = (1 << pin);
}

void Digital_out::init()
{
    DDRD |= pinMask;
}

void Digital_out::set_hi()
{
    PORTD |= pinMask;
}

void Digital_out::set_lo()
{
    PORTD &= ~pinMask;
}

void Digital_out::toggle()
{
    PORTD ^= pinMask;
}
