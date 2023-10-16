#include <timer.h>

#ifndef PWM_H
#define PWM_H

class Pwm
{
    public:
        Pwm();
        virtual ~Pwm();
        void init(int nr, int prescaler, float duty_cycle);
        void set_duty_cycle(float duty_cycle);

    private:
        int mNr;
        int mPrescaler;

};

#endif // PWM_H
