#include <stdint.h>
#include "encoder.h"

#ifndef P_CONTROLLER_H
#define P_CONTROLLER_H

class P_controller
{
    public:
        P_controller(double kp, Encoder& encoder);
                
        void init();
        double update(double ref, double actual);
    
    private:
        double mKp;
        Encoder& mEncoder;

};

#endif
