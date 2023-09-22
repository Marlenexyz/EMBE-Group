#include <P_controller.h>

P_controller::P_controller(double kp, Analog_out& m1, Digital_out& m2):
    mM1(m1),
    mM2(m2)
{
    mKp=kp;
}

void P_controller::init()
{

}

double P_controller::update(double ref, double actual)
{
    double error = ref - actual;
    setSpeed(actual + mKp * error); // is this right????
    return error;  //Was muss returned werden?
}

void P_controller::setSpeed(float omega){

    // max freq of f_update
    float duty = omega / maxOmega;
    if(duty > 1.0)
    {
        mM2.set_lo();
        mM1.set_duty_cycle(0.99); // fix this PWM duty = 1,0f
    }
    else if (duty < -1.0f)
    {
        
    }
    else if(duty >= 0)
    {
        mM2.set_lo();
        mM1.set_duty_cycle(duty);
    }
    else if(duty < 0)
    {

    }

}