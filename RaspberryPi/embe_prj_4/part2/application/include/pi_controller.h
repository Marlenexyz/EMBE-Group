#ifndef PI_CONTROLLER_H
#define PI_CONTROLLER_H

class PI_Controller
{
public:
    PI_Controller(double rpsMax, double kp, double ti, double updateRate_us);
    virtual ~PI_Controller();

    double update(double ref, double act);

private:
    double mRpsMax;
    double mKp;
    double mTi;
    double mUpdateRateUs;
    double mDuty;

};

#endif