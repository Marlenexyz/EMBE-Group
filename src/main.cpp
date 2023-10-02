#include <Arduino.h>
#include <state.h>
#include <context.h>
#include <concrete_state_initialization.h>
#include <concrete_state_operational.h>

Context *context;
int command = 0;

void setup()
{
    Serial.begin(9600);
    context = new Context(new Concrete_state_initialization);
}

void loop()
{
    
    // wait for some time
    context->do_work();

    // send data only when you receive data:
    if (Serial.available() > 0)
    {
        // read the incoming byte:
        command = Serial.read();

        // you can compare the value received to a character constant, like 'g'.
        switch (command)
        {
            case 'r':
                Serial.println("I received a reset command.");
                context->event_reset();
                break;
            case 's':
                Serial.println("I received a set operational command.");
                context->event_set_operational();
                break;
            default:
                break;
        }
    }
}

ISR(INT0_vect)
{
    context->omega = context->encoder.getSpeed();
    // tau = encoder.getTau();
    Serial.println("int0");
}



ISR(TIMER2_COMPA_vect)
{
    context->m1.pin.set_hi();
}

ISR(TIMER2_COMPB_vect)
{
    context->m1.pin.set_lo();
}

ISR(TIMER1_COMPA_vect)
{
    context->m2.pin.set_hi();
}

ISR(TIMER1_COMPB_vect)
{
    context->m2.pin.set_lo();
}
