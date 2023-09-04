#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <digital_out.h>
#include <digital_in.h>
#include <encoder.h>

#include <Arduino.h>


int main()
{
    Serial.begin(9600);

    // Digital_in C1(0);
    // Digital_in C2(4);
    // Digital_out LED(5);
    // Encoder encoder(C1, C2, LED);

    // C1.init();
    // C2.init();
    // LED.init();

    DDRD &= ~(1 << DDD3);
    PORTD |= (1 << PORTD3);
    EICRA |= (1 << ISC11) | (1 << ISC10);
    EIMSK |= (1 << INT1);
    sei();

    while(1)
    {
        // _delay_us(330);
        // Serial.println(encoder.position());
    }

    return 0;
}

ISR(INT1_vect)
{
    static unsigned int counter = 0;
    counter ++;
    Serial.println(counter);
}