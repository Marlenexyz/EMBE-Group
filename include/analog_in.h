#include <timer_msec.h>
#include <digital_out.h>

#ifndef ANALOG_IN_H
#define ANALOG_IN_H

class Analog_in
{
    public:
        Analog_in(int pin, float ref);
        void init();
        float get_duty_cycle();

    private:
        uint8_t pinMask;
        float refVolt;

};

#endif // ANALOG_IN_H
