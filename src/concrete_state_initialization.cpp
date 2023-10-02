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
    this->context_->encoder.init(12.48f);
    this->context_->controller.init(12.48f, 7.0f);
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
