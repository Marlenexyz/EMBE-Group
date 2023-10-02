#include "concrete_state_operational.h"

#include "context.h"
#include "concrete_state_initialization.h"
#include <Arduino.h>

void Concrete_state_operational::on_do()
{
    delay(2);
    Serial.print(", w_ref: ");
    Serial.print(this->context_->refOmega);
    Serial.print(", w: ");
    Serial.print(this->context_->omega);
    this->context_->controller.update(this->context_->refOmega, this->context_->omega);

    // if(tau > 0)
    // {
    //     Serial.print("Tau in µs: ");
    //     Serial.println(tau);
    //     delay(1000000);
    // }
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
