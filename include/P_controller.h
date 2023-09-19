#include <stdint.h>
#include <analog_out.h>
#include <digital_out.h>

#ifndef P_CONTROLLER_H
#define P_CONTROLLER_H

class P_controller
{
    public:
        P_controller(double kp, Analog_out& m1, Digital_out& m2);
                
        void init();
        double update(double ref, double actual);
        void setSpeed(float omega);
    
    private:
        double mKp;

        static constexpr float maxOmega = 12.5; // rad/s
        Analog_out mM1;
        Digital_out mM2;

};

#endif
