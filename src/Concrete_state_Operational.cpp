#include <Concrete_state_Initialization.h>
#include <Concrete_state_Operational.h>
#include <Arduino.h>
#include <context.h>
#include <state.h>

void Concrete_state_Operational::on_do()
{
    delay(2);
    Serial.print(", w_ref: ");
    Serial.print(context_->refOmega);
    Serial.print(", w: ");
    Serial.print(context_->omega);
    context_->controller.update(context_->refOmega, context_->omega);

    // if(tau > 0)
    // {
    //     Serial.print("Tau in µs: ");
    //     Serial.println(tau);
    //     delay(1000000);
    // }
}

void Concrete_state_Operational::on_entry()
{
}

void Concrete_state_Operational::on_exit()
{
}

void Concrete_state_Operational::on_event_reset()
{
    Serial.println("Reset from Operation to Initialization");
    this->context_->transition_to(new Concrete_state_Initialization);
}

void Concrete_state_Operational::on_event_set_operational()
{
}

void Concrete_state_Operational::on_isr_int0()
{
    context_->omega = context_->encoder.getSpeed();
    // context_->tau = context_->encoder.getTau();
}

void Concrete_state_Operational::on_isr_timer1_compa()
{
    context_->m2.pin.set_hi();
}

void Concrete_state_Operational::on_isr_timer1_compb()
{
    context_->m2.pin.set_lo();
}

void Concrete_state_Operational::on_isr_timer2_compa()
{
    context_->m1.pin.set_hi();
}

void Concrete_state_Operational::on_isr_timer2_compb()
{
    context_->m1.pin.set_lo();
}