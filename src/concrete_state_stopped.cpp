#include "concrete_state_stopped.h"

#include "context.h"
#include "concrete_state_initialization.h"
#include "concrete_state_pre_operational.h"
#include "concrete_state_operational.h"
#include <Arduino.h>

void Concrete_state_stopped::on_do()
{
    delay(1000); // blinking at 2 Hz
    this->context_->led.toggle();
}

void Concrete_state_stopped::on_entry()
{
    Serial.println("Transitioned to Stopped state.");
}

void Concrete_state_stopped::on_exit()
{

}

void Concrete_state_stopped::on_event_reset()
{
    this->context_->transition_to(new Concrete_state_initialization);
}

void Concrete_state_stopped::on_event_set_pre_operational()
{
    this->context_->transition_to(new Concrete_state_pre_operational);
}

void Concrete_state_stopped::on_event_set_operational()
{
    this->context_->transition_to(new Concrete_state_operational);
}
