#include <digital_in.h>
#include <digital_out.h>

#ifndef ENCODER_H
#define ENCODER_H

class Encoder
{
    public:
        Encoder(Digital_in& c1, Digital_in& c2);

        void init();
        int position();

    private:
        Digital_in mC1;
        Digital_in mC2;

        bool mLastC1;
        bool mLastC2;
        bool mCrtC1;
        bool mCrtC2;
        int mCount;
    
};

#endif
