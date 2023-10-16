#include <stdint.h>

#ifndef DIGITAL_IN_H
#define DIGITAL_IN_H

class Digital_in
{
    public:
        Digital_in(int pin, char portType);
        
        void init();
        bool is_hi();
        bool is_lo();
    
    private:
        uint8_t pinMask;
        char portType;
        volatile uint8_t *portRegister;
        volatile uint8_t *drrRegister;
        volatile uint8_t *pinRegister;

};

#endif
