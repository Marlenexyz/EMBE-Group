#include <Arduino.h>
#include <state.h>
#include <context.h>
#include <concrete_state_initialization.h>
#include <concrete_state_operational.h>
#include <modbus_server.h>

Context *context;
uint8_t message[8] = {0};

ModbusServer modbus;

void setup()
{
    Serial.begin(9600);
    context = new Context(new Concrete_state_initialization);

    modbus.init(0x02, 9600);
}

void loop()
{
    // handle current state operations
    context->do_work();

    // handle server requests
    modbus.handleRequest();

    uint16_t command = 0;
    modbus.getReg(0x0000, &command);

    // you can compare the value received to a character constant, like 'r'.
    switch (command)
    {
    case 0x0001:
        // Serial.println("I received a set operational command.");
        context->event_set_operational();
        break;
    case 0x0002:
        // Serial.println("I received a set operational command.");
        context->event_set_stopped();
        break;
    case 0x0080:
        // Serial.println("I received a set pre-operational command.");
        context->event_set_pre_operational();
        break;
    case 0x0081:
        // Serial.println("I received a reset command.");
        context->event_reset();
        break;
    default:
        break;
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
