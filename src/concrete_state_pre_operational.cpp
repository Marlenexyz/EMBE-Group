#include "concrete_state_pre_operational.h"

#include "context.h"
#include "concrete_state_initialization.h"
#include "concrete_state_operational.h"
#include <Arduino.h>

void Concrete_state_pre_operational::on_do()
{
    delay(500); // blinking at 1 Hz
    this->context_->led.toggle();
}

void Concrete_state_pre_operational::on_entry()
{
    Serial.println("Transitioned to Pre-Operational state.");
    Serial.println("Bootup... ready to receive commands...");

    byte data[4];
    Serial.print("Set Kp value: ");
    while (!(Serial.available() >= 4));
    Serial.readBytes(data, 4);
    float value = atof(reinterpret_cast<char*>(data));
    this->context_->controller.setKp(value);
    Serial.print("Kp value set to ");
    Serial.print(value);
    Serial.println(".");
}

void Concrete_state_pre_operational::on_exit()
{

}

void Concrete_state_pre_operational::on_event_reset()
{
    this->context_->transition_to(new Concrete_state_initialization);
}

void Concrete_state_pre_operational::on_event_set_pre_operational()
{

}

void Concrete_state_pre_operational::on_event_set_operational()
{
    this->context_->transition_to(new Concrete_state_operational);
}
