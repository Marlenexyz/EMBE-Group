#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
public:
    Controller(double rpsMax, double kp);
    virtual ~Controller();

    double update(double ref, double act);

private:
    double mRpsMax;
    double mKp;

};

#endif