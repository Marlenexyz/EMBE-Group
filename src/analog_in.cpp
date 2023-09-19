#include "analog_in.h"
#include <avr/io.h>

Analog_in::Analog_in(int pin, float refVolt)
{
    mPinMask = (1 << pin);
    mRefVolt = refVolt;
}

void Analog_in::init()
{
    // Set pin as input
    DDRC &= ~mPinMask;

    // Reset register
    ADMUX = 0;
    // Select ADC channel
    ADMUX |= mPinMask;

    // Reset register
    ADCSRA = 0;
    // Enable ADC
    ADCSRA |= (1 << ADEN);
    // Set prescaler to 128
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

float Analog_in::get_duty_cycle()
{
    // Start conversion
    ADCSRA |= (1 << ADSC);
    // Wait for conversion to finish
    while(ADCSRA & (1 << ADSC));

    // Read data
    uint16_t data = ADATE;
    // Convert data to voltage
    return (static_cast<float>(data) / 1023.0f) * mRefVolt;
}
