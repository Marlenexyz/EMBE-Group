#ifndef TIMER_MSEC_H
#define TIMER_MSEC_H

class Timer_msec
{
    public:
        Timer_msec();
        void init(int nr, int period_ms);
        void init(int nr, int period_ms, float duty_cycle);
        void set_duty_cycle(float duty_cycle);

    private:
        int mNr;
};

#endif // TIMER_MSEC_H
