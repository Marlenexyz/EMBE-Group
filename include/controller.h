#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
public:
    enum class Type : int
    {
        UNKNOWN,
        P_CONTROLLER,
        PI_CONTROLLER
    };

    virtual Controller::Type getType() = 0;

    virtual void init(float omegaMax, float kp, float ti) = 0;
    virtual float update(float ref, float actual) = 0;
    virtual void updateSpeed(float duty) = 0;

    virtual void setOmegaMax(float omegaMax) = 0;
    virtual void setKp(float kp) = 0;
    virtual void setTi(float ti) = 0;
    
};

#endif
