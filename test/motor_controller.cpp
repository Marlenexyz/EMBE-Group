#include <motor_controller.h>

Motor_controller::Motor_controller(Analog_out &m1, Analog_out &m2) :
    mM1(m1),
    mM2(m2),
    mP_controller(m1, m2),
    mPI_controller(m1, m2),
    mController(nullptr),
    mOmegaMax(0.0f),
    mKp(1.0f),
    mTi(1.0f)
{

}

void Motor_controller::setController(Controller::Type type)
{
    switch(type)
    {
        case Controller::Type::P_CONTROLLER: mController = &mP_controller; break;
        case Controller::Type::PI_CONTROLLER: mController = &mPI_controller; break;
        default: mController = nullptr;
    }
}

Controller::Type Motor_controller::getType()
{
    if(mController != nullptr)
        return mController->getType();
    else
        return Controller::Type::UNKNOWN;
}

void Motor_controller::init(float omegaMax)
{
    if(mController != nullptr)
        mController->init(omegaMax);
}

void Motor_controller::reset()
{
    if(mController != nullptr)
        mController->reset();
}

float Motor_controller::update(float ref, float actual)
{
    if(mController != nullptr)
        return mController->update(ref, actual);
    else
        return 0.0f;
}

void Motor_controller::updateSpeed(float duty)
{
    if(mController != nullptr)
        mController->updateSpeed(duty);
}

void Motor_controller::setOmegaMax(float omegaMax)
{
    if(mController != nullptr)
        mController->setOmegaMax(omegaMax);
}

void Motor_controller::setKp(float kp)
{
    if(mController != nullptr)
        mController->setKp(kp);
}

void Motor_controller::setTi(float ti)
{
    if(mController != nullptr)
        mController->setTi(ti);
}
