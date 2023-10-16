#include "analog_out.h"
#include <avr/io.h>

Analog_out::Analog_out(int pin, char portType): pin(pin,portType){      
}



void Analog_out::init(int nr, int period_ms, float duty_cycle)
{
    timer.init(nr, period_ms, duty_cycle);
}

void Analog_out::set_duty_cycle(float duty_cycle)
{
    timer.set_duty_cycle(duty_cycle);
}
