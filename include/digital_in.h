#include <stdint.h>

#ifndef DIGITAL_IN_H
#define DIGITAL_IN_H

class Digital_in
{  
    public:
        Digital_in(int pin);
        void init();
        bool is_hi();
        bool is_lo();
    private:
        uint8_t _pinmask;
};

#endif