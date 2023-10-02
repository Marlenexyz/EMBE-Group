#include <stdint.h>
#include <analog_out.h>
#include <digital_out.h>
#include <digital_in.h>

#ifndef P_CONTROLLER_H
#define P_CONTROLLER_H

class P_controller
{
    public:
        P_controller(Analog_out& m1, Analog_out& m2);
                
        void init(float maxOmega, float kp);
        float update(float ref, float actual);
        void setSpeed(float omega);
        void brake();
    
    private:
        float mKp;

        float mMaxOmega; // rad/s
        Analog_out mM1;
        Analog_out mM2;
        Digital_in button;
        Digital_out sleep;

};

#endif
