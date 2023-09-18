#include "P_controller.h"

P_controller::P_controller(double kp, Encoder& encoder)
    : mEncoder(encoder)
{
    mKp = kp;
}

void P_controller::init()
{

}

double P_controller::update(double ref, double actual)
{
    double error = ref - actual;
    mEncoder.setSpeed(actual + mKp * error); // is this right????

}
