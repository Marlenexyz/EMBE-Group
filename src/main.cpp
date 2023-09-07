#include <Arduino.h>

#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <digital_in.h>
#include <digital_out.h>
#include <encoder.h>

static bool isTriggered = false;
static int counter = 0;

Digital_in c1(2);
Digital_in c2(3);
Digital_out led(5);
Encoder encoder(c1, c2, led);

int main()
{
    // --- PART 1/2 ------------------------------------------------------
    Serial.begin(9600);

    c1.init();
    c2.init();
    led.init();
    encoder.init();

    while(1)
    {
        counter = encoder.position();
        if(counter % 70 == 0 && counter != 0)
        {
            Serial.println(encoder.position());
        }
    }

    // --- PART 3 --------------------------------------------------------
    // Serial.begin(9600);

    // c2.init();

    // DDRD &= ~(1 << DDD2);
    // PORTD |= (1 << PORTD2);
    // EICRA |= (1 << ISC01) | (1 << ISC00);
    // EIMSK |= (1 << INT0);
    // sei();

    // while(1)
    // {
    //     _delay_ms(10);
    //     Serial.println(counter);
    // }
}

ISR(INT0_vect)
{
    if(c2.is_lo())
    {
        counter++;
    }
    else
    {
        counter--;
    }
}
