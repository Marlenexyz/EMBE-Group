#include <timer_msec.h>
#include <digital_out.h>

#ifndef ANALOG_IN_H
#define ANALOG_IN_H

class Analog_in
{
    public:
        Analog_in();
        virtual ~Analog_in();
        void init(int pin, float refVolt);
        float get_duty_cycle();

    private:
        uint8_t mPinMask;
        float mRefVolt;

};

#endif // ANALOG_IN_H
