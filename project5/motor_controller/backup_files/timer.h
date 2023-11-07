#ifndef TIMER_H
#define TIMER_H

class Timer
{
    public:
        Timer();
        virtual ~Timer();
        void init(int nr, int prescaler, long frequency);
        void set_frequency(long frequency);

    private:
        static const unsigned long cSYSTEM_FREQUENCY = 16000000;

        int mNr;
        int mPrescaler;
};

#endif // TIMER_H
