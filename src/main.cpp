#include <Arduino.h>

#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <digital_in.h>
#include <digital_out.h>
#include <analog_out.h>
#include <encoder.h>
#include <P_controller.h>

// static unsigned long timeLast = 0;
// static unsigned long timeCrt = 0;
static float omega = 0.0;

static float refOmega = 6.0;

Digital_in c1(2,'D');
Digital_in c2(3,'D');
Analog_out m1(4,'D');
Digital_out m2(5,'D');

Encoder encoder(c1, c2, m1, m2);
P_controller controller(1.0, encoder);

void setup()
{
    Serial.begin(9600);

    c2.init();
    m1.init(10, 0.0);
    m2.init();
    encoder.init();
    controller.init();

    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2);
    EICRA |= (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0);
    sei();

    // encoder.setSpeed(6);
}

void loop()
{
    delayMicroseconds(2);

    omega = encoder.getSpeed();
    controller.update(refOmega, omega);
    Serial.println(omega);

    // omega = 0;
}

ISR(INT0_vect)
{
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
