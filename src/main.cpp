#include <Arduino.h>
#include <state.h>
#include <context.h>
#include <concrete_state_initialization.h>
#include <concrete_state_operational.h>

// #include <avr/delay.h>
// #include <avr/io.h>
// #include <avr/interrupt.h>

// #include <digital_in.h>
// #include <digital_out.h>
// #include <analog_out.h>
// #include <encoder.h>
// #include <P_controller.h>

// static unsigned long tau = 0;
// static float omega = 0.0f;
// static float refOmega = 8.0f;

// Digital_in c1(2,'D');
// Digital_in c2(3,'D');
// Analog_out m1(4,'D');
// Analog_out m2(5,'D');

// Encoder encoder(c1, c2);
// P_controller controller(m1, m2);

Context *context;
int command = 0;

void setup()
{
    Serial.begin(9600);
    context = new Context(new Concrete_state_initialization);

    // encoder.init(12.48f);
    // controller.init(12.48f, 7.0f);
}

void loop()
{
    // delay(2);
    // Serial.print(", w_ref: ");
    // Serial.print(refOmega);
    // Serial.print(", w: ");
    // Serial.print(omega);
    // controller.update(refOmega, omega);

    // if(tau > 0)
    // {
    //     Serial.print("Tau in µs: ");
    //     Serial.println(tau);
    //     delay(1000000);
    // }
    
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
    // omega = encoder.getSpeed();
    // tau = encoder.getTau();
}



ISR(TIMER2_COMPA_vect)
{
    // m1.pin.set_hi();
}

ISR(TIMER2_COMPB_vect)
{
    // m1.pin.set_lo();
}

ISR(TIMER1_COMPA_vect)
{
    // m2.pin.set_hi();
}

ISR(TIMER1_COMPB_vect)
{
    // m2.pin.set_lo();
}
