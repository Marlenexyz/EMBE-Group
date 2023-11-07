#include "concrete_state_operational.h"

#include "context.h"
#include "concrete_state_initialization.h"
#include "concrete_state_pre_operational.h"
#include "concrete_state_stopped.h"
#include <Arduino.h>

State::Name Concrete_state_operational::getStateName()
{
    return State::Name::OPERATIONAL;
}

void Concrete_state_operational::on_do()
{
    delay(UPDATE_RATE);
    this->context_->controller.update(this->context_->omegaRef, this->context_->omega);
    
    if (this->context_->button.is_lo() || this->context_->fault.is_lo())
    {
        this->context_->sleep.set_lo();
        this->context_->transition_to(new Concrete_state_stopped);
    }

    // if(this->context_->tau > 0)
    // {
    //     Serial.print("Tau in µs: ");
    //     Serial.println(this->context_->tau);
    //     delay(1000000);
    // }
}

void Concrete_state_operational::on_entry()
{
    Serial.println("Transitioned to Operational state.");
    this->context_->led.set_hi();
}

void Concrete_state_operational::on_exit()
{
    this->context_->led.set_lo();
}

void Concrete_state_operational::on_event_reset()
{
    this->context_->controller.reset();
    this->context_->transition_to(new Concrete_state_initialization);
}

void Concrete_state_operational::on_event_set_pre_operational()
{
    this->context_->transition_to(new Concrete_state_pre_operational);
}

void Concrete_state_operational::on_event_set_operational()
{

}
