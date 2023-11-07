#include <Arduino.h>
#include <state.h>
#include <context.h>
#include <concrete_state_initialization.h>
#include <concrete_state_operational.h>

Context *context;
uint8_t message[8] = {0};

void setup()
{
    Serial.begin(115200);
    context = new Context(new Concrete_state_initialization);
}

void loop()
{
    // handle current state operations
    context->do_work();

    // send data only when you receive data:
    if (Serial.available() > 0)
    {
        // read the incoming byte:
		Serial.readBytes(message, 8);
        // debug print
		Serial.println((char*)message);

        int command = 0;
        // modbus receive
        /*
        modbus.receive();
        command = modbus.readRegister();
        */

        // you can compare the value received to a character constant, like 'r'.
        switch (command)
        {
        case 'r':
            Serial.println("I received a reset command.");
            context->event_reset();
            break;
        case 'p':
            Serial.println("I received a set pre-operational command.");
            context->event_set_pre_operational();
            break;
        case 'o':
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
    // context->tau = context->encoder.getTau();
}

ISR(TIMER1_COMPA_vect)
{
    context->m1.pin.set_hi();
}

ISR(TIMER1_COMPB_vect)
{
    context->m1.pin.set_lo();
}

ISR(TIMER2_COMPA_vect)
{
    context->m2.pin.set_hi();
}

ISR(TIMER2_COMPB_vect)
{
    context->m2.pin.set_lo();
}
