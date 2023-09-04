#include <Arduino.h>

#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <digital_in.h>
#include <digital_out.h>
#include <encoder.h>

int main()
{
    // Digital_in c1(2);
    // Digital_in c2(3);
    // Digital_out led(5);
    // Encoder encoder(c1, c2, led);

    // c1.init();
    // c2.init();
    // led.init();
    // encoder.init();

    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2);
    EICRA |= (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0);
    sei();

    Serial.begin(9600);

    while(1)
    {
        // Serial.println(encoder.position());
        // _delay_us(330);
    }

    return 0;
}

ISR(INT0_vect)
{
    static unsigned int counter = 0;
    counter++;
    Serial.println(counter);
}
