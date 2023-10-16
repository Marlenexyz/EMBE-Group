#include "digital_out.h"
#include <avr/io.h>

Digital_out::Digital_out(int pin, char portType){
    pinMask = (1 << pin);
    if (portType == 'B'){
        portRegister = &PORTB;
        drrRegister = &DDRB;
    }
    else if (portType == 'C'){
        portRegister = &PORTC;
        drrRegister = &DDRC;
    }
    else if (portType == 'D'){ 
        portRegister = &PORTD;
        drrRegister = &DDRD;
    }

}

void Digital_out::init()
{
    *drrRegister |= pinMask;
}

void Digital_out::set_hi()
{
    *portRegister |= pinMask;
}

void Digital_out::set_lo()
{
    *portRegister &= ~pinMask;
}

void Digital_out::toggle()
{
    *portRegister ^= pinMask;
}
