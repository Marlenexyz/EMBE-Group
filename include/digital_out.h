#include <stdint.h>

class Digital_out
{
public: 
    //Konstruktor
    Digital_out(int pinNumber); //takes pin number as int argument, where the pin number refers to the pin number within a port
    void init();
    void set_hi();
    void set_lo();
    void toggle();

private:
    uint8_t pinMask;  //used in register operations
};


