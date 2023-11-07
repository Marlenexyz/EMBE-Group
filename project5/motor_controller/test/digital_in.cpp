#include "digital_in.h"
#include <avr/io.h>

Digital_in::Digital_in(int pin, char portType)
{
    pinMask = (1 << pin);
    if (portType == 'B'){
        portRegister = &PORTB;
        drrRegister = &DDRB;
        pinRegister = &PINB;
    }
    else if (portType == 'C'){
        portRegister = &PORTC;
        drrRegister = &DDRC;
        pinRegister = &PINC;
    }
    else if (portType == 'D'){ 
        portRegister = &PORTD;
        drrRegister = &DDRD;
        pinRegister = &PIND;
    }
}

void Digital_in::init()
{
    *drrRegister &= ~pinMask;
    *portRegister |= pinMask;
}

bool Digital_in::is_hi()
{
    return (*pinRegister & pinMask) != 0;
}

bool Digital_in::is_lo()
{
    return (*pinRegister & pinMask) == 0;
}
