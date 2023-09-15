#include <Arduino.h>

#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <digital_in.h>
#include <digital_out.h>
#include <analog_out.h>
#include <encoder.h>

static unsigned long timeLast = 0;
static unsigned long timeCrt = 0;
static float omega = 0.0;

Digital_in c1(2);
Digital_in c2(3);
// Analog_out m1(4);
Analog_out m2(5);

void setup()
{
    Serial.begin(9600);

    c2.init();
    // m1.init(1, 0);
    m2.init(1, 0.9);

    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2);
    EICRA |= (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0);
    sei();
}

void loop()
{
    delay(1000);
    Serial.println(omega);
    omega = 0;
}

ISR(INT0_vect)
{
    timeCrt = micros();

    if(timeLast > 0)
    {
        unsigned long period = timeCrt - timeLast;
        omega = 2.0f * 3.1415926535f / (static_cast<float>(period) * 700.0f / 1000000.0f );
    }

    if(c2.is_hi())
    {
        omega = -omega;
    }

    timeLast = timeCrt;
}



ISR(TIMER1_COMPA_vect)
{
    m2.pin.set_hi();
}

ISR(TIMER1_COMPB_vect)
{
    m2.pin.set_lo();
}

