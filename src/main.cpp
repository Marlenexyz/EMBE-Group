#include <Arduino.h>

#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <digital_in.h>
#include <digital_out.h>
#include <encoder.h>


static unsigned int counter = 0;

int main()
{
    Digital_in c1(2);
    Digital_in c2(3);
    Digital_out led(5);
    Encoder encoder(c1, c2, led);

    c1.init();
    c2.init();
    led.init();
    encoder.init();

    // DDRD &= ~(1 << DDD2);
    // PORTD |= (1 << PORTD2);
    // EICRA |= (1 << ISC01) | (1 << ISC00);
    // EIMSK |= (1 << INT0);
    
    // DDRD &= ~(1 << DDD3);
    // PORTD |= (1 << PORTD3);
    // EICRA |= (1 << ISC11) | (1 << ISC10);
    // EIMSK |= (1 << INT1);

    // sei();

    Serial.begin(9600);

    while(1)
    {
        for(uint32_t i = 0; i < 100000; i++)
        {
            encoder.position();
            _delay_us(100);
        }
        Serial.println(encoder.position());
        // _delay_us(330);
        // Serial.println(counter);
        // _delay_ms(10000);
    }

    return 0;
}

ISR(INT0_vect)
{
    counter++;
}

ISR(INT1_vect)
{
    counter++;
}
