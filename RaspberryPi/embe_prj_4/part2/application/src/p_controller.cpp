#include "p_controller.h"

P_Controller::P_Controller(double rpsMax, double kp) :
    mRpsMax(rpsMax),
    mKp(kp)
{

}

P_Controller::~P_Controller()
{

}

double P_Controller::update(double ref, double act)
{
    // calculate new speed value
    double error = ref - act;
    double value = mKp * error;
    double duty = value / mRpsMax;

    if (duty > 1.0)
        duty = 1.0;
    else if (duty < -1.0)
        duty = -1.0;

    return duty;
}
