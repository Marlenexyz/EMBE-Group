#include "controller.h"

Controller::Controller(double rpsMax, double kp) :
    mRpsMax(),
    mKp()
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

    return duty;
}
