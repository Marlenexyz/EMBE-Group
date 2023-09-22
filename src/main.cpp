#include <Arduino.h>

#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <digital_in.h>
#include <digital_out.h>
#include <analog_out.h>
#include <encoder.h>
#include <P_controller.h>

static unsigned long tau = 0;
static float omega = 0.0;

static float refOmega = 6.0;

Digital_in c1(2,'D');
Digital_in c2(3,'D');
Analog_out m1(4,'D');
Digital_out m2(5,'D');

Encoder encoder(c1, c2);
P_controller controller(1.0, m1, m2);

void setup()
{
    Serial.begin(9600);

    m1.init(10, 0.5f);
    m2.init();
    m2.set_lo();
    encoder.init();
    controller.init();

    // encoder.setSpeed(6);
}

void loop()
{
    // delayMicroseconds(2);

    // controller.update(refOmega, omega);
    Serial.println(omega);

    if(tau > 0)
    {
        Serial.print("Tau in µs: ");
        Serial.println(tau);
        delay(1000000);
    }
}

ISR(INT0_vect)
{
    // tau = encoder.getTau();
    omega = encoder.getSpeed();
}



ISR(TIMER1_COMPA_vect)
{
    m1.pin.set_hi();
}

ISR(TIMER1_COMPB_vect)
{
    m1.pin.set_lo();
}
