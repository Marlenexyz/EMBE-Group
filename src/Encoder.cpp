#include <encoder.h>



void Encoder::init(Digital_in C1, Digital_in C2, Digital_out LED)
{
    C1 = C1;
    C2 = C2;
    LED = LED;        
    count = 0;
    currentState = false;
    lastState = false;
            // gear ratio 1:100
     //Uhrzeigersinn:  00 10 11 01
     //Gegen Uhrzeigersinn: 00 01 11 10
}

int Encoder::position(){
    currentState = C1.is_hi();
    if (lastState != currentState && currentState == true) {
        count += 1;
        // Turn on LED
        LED.set_hi();
    }
    lastState = currentState;
    return count;
}