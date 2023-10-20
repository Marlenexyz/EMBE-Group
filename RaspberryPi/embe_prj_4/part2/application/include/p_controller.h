#ifndef P_CONTROLLER_H
#define P_CONTROLLER_H

class P_Controller
{
public:
    P_Controller(double rpsMax, double kp);
    virtual ~P_Controller();

    double update(double ref, double act);

private:
    double mRpsMax;
    double mKp;

};

#endif