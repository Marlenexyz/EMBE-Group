#include <digital_in.h>
#include <avr/io.h>        



Digital_in::Digital_in(int pin) 
{
    _pinmask = (1 << pin);
}


void Digital_in::init()
{  
    //DDRB |= pinMask;
    PORTB |= _pinmask;

    DDRB &= ~_pinmask;
}

bool Digital_in::is_hi()
{
    return (PINB & _pinmask) != 0;
}

bool Digital_in::is_lo()
{
   return (PINB & _pinmask) == 0;
}