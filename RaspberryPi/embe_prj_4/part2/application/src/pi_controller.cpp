#include "pi_controller.h"

PI_Controller::PI_Controller(double rpsMax, double kp, double ti, double updateRate_us) :
    mRpsMax(rpsMax),
    mKp(kp),
    mTi(ti),
    mUpdateRateUs(updateRate_us),
    mDuty(0.0)
{

}

PI_Controller::~PI_Controller()
{

}

double PI_Controller::update(double ref, double act)
{
    static double error = 0.0;

    // calculate new speed value
    double errorNew = ref - act;

    // prevent integral windup
    if(mDuty < 1.0)
        error += errorNew;
    double value = mKp * (errorNew + 1 / mTi * error * mUpdateRateUs / 1000000.0 );
    mDuty = value / mRpsMax;

    if (mDuty > 1.0)
        mDuty = 1.0;
    else if (mDuty < -1.0)
        mDuty = -1.0;

    return mDuty;
}
