#include "concrete_state_initialization.h"

#include "context.h"
#include "concrete_state_operational.h"
#include <Arduino.h>

void Concrete_state_initialization::on_do()
{

}

void Concrete_state_initialization::on_entry()
{
    Serial.println("Transitioned to Initialization state.");

    // initialize all pins and controllers
    this->context_->button.init();
    this->context_->fault.init();
    this->context_->sleep.init();
    this->context_->led.init();
    this->context_->encoder.init(OMEGA_MAX);
    this->context_->controller.init(OMEGA_MAX, P_CTRL_KP);

    // set H-bridge to active state
    this->context_->sleep.set_hi();
}

void Concrete_state_initialization::on_exit()
{

}

void Concrete_state_initialization::on_event_reset()
{
}

void Concrete_state_initialization::on_event_set_operational()
{
    this->context_->transition_to(new Concrete_state_operational);
}
