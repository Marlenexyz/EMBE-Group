#include "concrete_state_operational.h"

#include "context.h"
#include "concrete_state_initialization.h"
#include <Arduino.h>

void Concrete_state_operational::on_do()
{

}

void Concrete_state_operational::on_entry()
{
    Serial.println("Transitioned to Operational state.");
}

void Concrete_state_operational::on_exit()
{

}

void Concrete_state_operational::on_event_reset()
{
    this->context_->transition_to(new Concrete_state_initialization);
}

void Concrete_state_operational::on_event_set_operational()
{

}
