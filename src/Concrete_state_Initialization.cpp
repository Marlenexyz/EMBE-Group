#include <Concrete_state_Initialization.h>
#include <Concrete_state_Operational.h>
#include <Arduino.h>
#include <context.h>
#include <state.h>

// shift + Alt + F = auto einrückung

void Concrete_state_Initialization::on_do()
{
}

void Concrete_state_Initialization::on_entry()
{
    context_->encoder.init(12.48f);
    context_->controller.init(12.48f, 7.0f);
}

void Concrete_state_Initialization::on_isr_int0()
{
}

void Concrete_state_Initialization::on_exit()
{
}

void Concrete_state_Initialization::on_event_reset()
{
}

void Concrete_state_Initialization::on_event_set_operational()
{
    Serial.println("Transition from Initialization to Operational");
    this->context_->transition_to(new Concrete_state_Operational);
}

void Concrete_state_Initialization::on_isr_timer1_compa(){

}

void Concrete_state_Initialization::on_isr_timer1_compb(){

}

void Concrete_state_Initialization::on_isr_timer2_compa(){

}

void Concrete_state_Initialization::on_isr_timer2_compb(){

}
