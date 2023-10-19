#include "controller.h"

Controller::Controller(double rpsMax, double kp) :
    mRpsMax(rpsMax),
    mKp(kp)
{

}

Controller::~Controller()
{

}

double Controller::update(double ref, double act)
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
