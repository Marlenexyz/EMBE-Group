#include "concrete_state_operational.h"

#include "context.h"
#include "concrete_state_initialization.h"
#include <Arduino.h>

void Concrete_state_operational::on_do()
{
    delay(2);
    Serial.print("w_ref: ");
    Serial.print(this->context_->omegaRef);
    Serial.print(", w: ");
    Serial.print(this->context_->omega);
    Serial.print(", duty: ");
    Serial.println(this->context_->controller.duty);
    this->context_->controller.update(this->context_->omegaRef, this->context_->omega);

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
    this->context_->transition_to(new Concrete_state_initialization);
}

void Concrete_state_operational::on_event_set_operational()
{

}
