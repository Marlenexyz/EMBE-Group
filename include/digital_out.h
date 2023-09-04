#include <stdint.h>

#ifndef DIGITAL_OUT_H
#define DIGITAL_OUT_H

class Digital_out
{
    public:
        Digital_out(int pin);
        
        void init();
        void set_hi();
        void set_lo();
        void toggle();
    
    private:
        uint8_t pinMask;

};

#endif
