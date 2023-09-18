#include <timer_msec.h>
#include <digital_out.h>

#ifndef ANALOG_OUT_H
#define ANALOG_OUT_H

class Analog_out
{
    public:
        Analog_out(int pin, char portType);
        void init(int period_ms = 1000, float duty_cycle = 0.5);
        void set_duty_cycle(float duty_cycle);

    private:
        Timer_msec timer;

    public:    
        Digital_out pin;
};

#endif // ANALOG_OUT_H
