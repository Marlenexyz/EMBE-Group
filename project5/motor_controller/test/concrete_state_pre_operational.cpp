#include "concrete_state_pre_operational.h"

#include "context.h"
#include "concrete_state_initialization.h"
#include "concrete_state_operational.h"
#include <Arduino.h>

State::Name Concrete_state_pre_operational::getStateName()
{
    return State::Name::PRE_OPERATIONAL;
}

void Concrete_state_pre_operational::on_do()
{
    delay(500); // blinking at 1 Hz
    this->context_->led.toggle();
}

void Concrete_state_pre_operational::on_entry()
{
    // Serial.println("Transitioned to Pre-Operational state.");
    // Serial.println("Bootup... ready to receive commands...");

    // Set controller
    char ctrl = 0;
    do
    {
        // Serial.println("Set controller ('p' for P or 'i' for PI): ");
        while (!(Serial.available() >= 1));
        ctrl = Serial.read();
    } while (ctrl != 'p' && ctrl != 'i');
    // Serial.print("   ...Controller set to ");
    switch(ctrl)
    {
        case 'p':
            this->context_->controller.setController(Controller::Type::P_CONTROLLER);
            // Serial.print("P");
            break;
        case 'i':
            this->context_->controller.setController(Controller::Type::PI_CONTROLLER);
            // Serial.print("PI");
            break;
        default:
            break;
    }
    // Serial.println(".");

    // Initialize controller
    this->context_->controller.init(OMEGA_MAX);

    // Set Kp value
    byte kp[4] = {0};
    float value = 0.0f;
    do
    {
        // Serial.println("Set Kp value as decimal (4 chars available): ");
        while (!(Serial.available() >= 4));
        Serial.readBytes(kp, 4);
        value = atof(reinterpret_cast<char*>(kp));
    } while (value == 0.0f);
    this->context_->controller.setKp(value);
    // Serial.print("   ...Kp value set to ");
    // Serial.print(value);
    // Serial.println(".");

    if(this->context_->controller.getType() == Controller::Type::PI_CONTROLLER)
    {
        // Set Ti value
        byte ti[4] = {0};
        value = 0.0f;
        do
        {
            // Serial.println("Set Ti value in ms (4 chars available): ");
            while (!(Serial.available() >= 4));
            Serial.readBytes(ti, 4);
            value = atof(reinterpret_cast<char*>(ti));
        } while (value == 0.0f);
        this->context_->controller.setTi(value / 1000.0f);
        // Serial.print("   ...Ti value set to ");
        // Serial.print(value);
        // Serial.println(".");
    }

    // Serial.println("Presets finished...");
}

void Concrete_state_pre_operational::on_exit()
{

}

void Concrete_state_pre_operational::on_event_reset()
{
    this->context_->controller.reset();
    this->context_->transition_to(new Concrete_state_initialization);
}

void Concrete_state_pre_operational::on_event_set_pre_operational()
{

}

void Concrete_state_pre_operational::on_event_set_operational()
{
    this->context_->transition_to(new Concrete_state_operational);
}
